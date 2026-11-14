#include "stm32f401rbt6.h"
#include "systick_timer.h"
#include "gpio.h"
#include "scheduler.h"
#include "tasks.h"

/*
 * RaayanMini LEDs are connected as active-low outputs:
 * writing 1 turns an LED OFF, and writing 0 turns it ON.
 */
#define RED_LED_PIN       13U
#define GREEN_LED_PIN     14U

/*
 * The dispatcher calls each task as an ordinary C function. It does not save
 * the task's program counter, registers, or stack. Each task therefore keeps
 * its own logical progress explicitly in a state variable.
 */
typedef enum
{
    LED_STATE_OFF = 0,
    LED_STATE_ON
} led_state_t;

/*
 * Tasks update their own future dispatch period to demonstrate a cooperative,
 * non-blocking delay. The scheduler owns the table; the tasks only change the
 * period field associated with their fixed table entry.
 */
extern tcb_t taskList[MAX_TASKS];

int main(void)
{
    /* Configure the two LED pins before starting the scheduler time base. */
    gpio_init(PORTB);
    gpio_config(PORTB, RED_LED_PIN, OUTPUT);
    gpio_config(PORTB, GREEN_LED_PIN, OUTPUT);

    /* Start with both active-low LEDs switched OFF. */
    GPIOB->ODR |= BIT(RED_LED_PIN);
    GPIOB->ODR |= BIT(GREEN_LED_PIN);

    /* Configure SysTick to generate the 1 ms scheduler time base. */
    systickInit();

    /*
     * startScheduler() contains the cooperative dispatch loop and normally
     * never returns. Every scheduled task must finish quickly and return.
     */
    startScheduler();

    /* Defensive fallback: execution should never reach this loop. */
    while (1)
    {
    }
}

void task1_redLedBlink(void)
{
    static led_state_t state = LED_STATE_OFF;

    /*
     * Every dispatch enters this function at its first statement. The static
     * variable remembers the logical step completed during the previous call.
     */
    switch (state)
    {
        case LED_STATE_OFF:
            /* Active-low output: clear the bit to switch the LED ON. */
            GPIOB->ODR &= ~BIT(RED_LED_PIN);
            state = LED_STATE_ON;
            break;

        case LED_STATE_ON:
            /* Active-low output: set the bit to switch the LED OFF. */
            GPIOB->ODR |= BIT(RED_LED_PIN);
            state = LED_STATE_OFF;
            break;

        default:
            /* Recover to a known state if the state value is corrupted. */
            GPIOB->ODR |= BIT(RED_LED_PIN);
            state = LED_STATE_OFF;
            break;
    }

    /* Defer the next call without holding the CPU in a busy-wait loop. */
    taskList[0].period = 1000U;
    return;
}

void task2_greenLedBlink(void)
{
    static led_state_t state = LED_STATE_OFF;

    /*
     * The table contains an initial period of 250 ms. During the forced startup
     * call, this task changes its future period to 1000 ms and returns. This is
     * intentional and demonstrates runtime rescheduling without a busy-wait.
     * The static state supplies the logical continuation on the next call.
     */
    switch (state)
    {
        case LED_STATE_OFF:
            GPIOB->ODR &= ~BIT(GREEN_LED_PIN);
            state = LED_STATE_ON;
            break;

        case LED_STATE_ON:
            GPIOB->ODR |= BIT(GREEN_LED_PIN);
            state = LED_STATE_OFF;
            break;

        default:
            GPIOB->ODR |= BIT(GREEN_LED_PIN);
            state = LED_STATE_OFF;
            break;
    }

    taskList[1].period = 1000U;
    return;
}
