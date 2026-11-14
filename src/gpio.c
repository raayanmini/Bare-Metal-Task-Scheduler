#include "stm32f401rbt6.h"
#include "gpio.h"

void gpio_init(uint8_t port)
{
    uint32_t clockMask;

    /* Select the RCC AHB1 peripheral-clock bit for the requested GPIO port. */
    switch (port)
    {
        case 'A':
            clockMask = BIT(0);
            break;

        case 'B':
            clockMask = BIT(1);
            break;

        case 'C':
            clockMask = BIT(2);
            break;

        default:
            /* Unsupported port: leave the clock configuration unchanged. */
            return;
    }

    RCC->AHB1ENR |= clockMask;

    /*
     * Read the register back so the clock-enable write completes before a
     * GPIO register belonging to that peripheral is accessed.
     */
    (void)RCC->AHB1ENR;
}

void gpio_config(uint8_t port, uint8_t pin, uint8_t mode)
{
    uint32_t shift;
    uint32_t modeBits;
    uint32_t modeMask;

    if (pin > 15U)
    {
        /* STM32 GPIO ports contain pins 0 through 15 only. */
        return;
    }

    /* Convert the public mode value into the two-bit STM32 MODER encoding. */
    switch (mode)
    {
        case INPUT:
            modeBits = 0x00U;
            break;

        case OUTPUT:
            modeBits = 0x01U;
            break;

        case ALTERNATE:
            modeBits = 0x02U;
            break;

        case ANALOG:
            modeBits = 0x03U;
            break;

        default:
            /* Invalid mode: do not modify the peripheral registers. */
            return;
    }

    shift = ((uint32_t)pin * 2U);
    modeMask = (0x03U << shift);

    /*
     * Clear the existing two-bit field before writing the new mode. Using
     * OR alone would fail when a pin is reconfigured from a non-zero mode.
     * Pull-up and pull-down configuration is intentionally separate from the
     * pin mode and is not changed by this function.
     */
    switch (port)
    {
        case 'A':
            GPIOA->MODER = (GPIOA->MODER & ~modeMask) |
                           (modeBits << shift);
            break;

        case 'B':
            GPIOB->MODER = (GPIOB->MODER & ~modeMask) |
                           (modeBits << shift);
            break;

        case 'C':
            GPIOC->MODER = (GPIOC->MODER & ~modeMask) |
                           (modeBits << shift);
            break;

        default:
            /* Unsupported port: do not modify any GPIO peripheral. */
            break;
    }
}
