/*
 * SysTick time-base driver for the cooperative task dispatcher.
 *
 * The reload calculation below assumes the processor is running at 16 MHz.
 * Update SYSTICK_INPUT_CLOCK_HZ if the application changes the core clock.
 */

#include "systick_timer.h"
#include "stm32f401rbt6.h"
#include "scheduler.h"

#define SYSTICK_INPUT_CLOCK_HZ    16000000U
#define SYSTICK_TICK_HZ               1000U

/* 32-bit millisecond counter shared by the ISR and foreground scheduler. */
volatile tick_t jiffy = 0U;

void KM_mdelay(uint32_t ms)
{
    tick_t start = jiffy;

    /*
     * Busy-wait delay.
     *
     * Do not call this function from a scheduled task: because the dispatcher
     * is cooperative, a busy-waiting task prevents every other task from
     * running until the delay finishes. It is retained to demonstrate this
     * limitation of the bare-metal design.
     */
    while ((tick_t)(jiffy - start) < (tick_t)ms)
    {
    }
}

void systickInit(void)
{
    uint32_t reloadValue;

    /* Generate one interrupt every millisecond. */
    reloadValue = (SYSTICK_INPUT_CLOCK_HZ / SYSTICK_TICK_HZ) - 1U;

    /* Stop SysTick while its registers are configured. */
    SYSTICK->CTRL = 0U;
    SYSTICK->LOAD = reloadValue;
    SYSTICK->VAL = 0U;

    /*
     * CTRL bit 2: processor clock is the SysTick clock source.
     * CTRL bit 1: enable the SysTick exception.
     * CTRL bit 0: start the counter.
     */
    SYSTICK->CTRL = BIT(2) | BIT(1) | BIT(0);
}

void SysTick_Handler(void)
{
    /* Keep the ISR short: record elapsed time and return immediately. */
    jiffy++;
}
