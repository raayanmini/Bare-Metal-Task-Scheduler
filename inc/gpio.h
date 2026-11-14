#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* Supported GPIO ports. */
#define PORTA           'A'
#define PORTB           'B'
#define PORTC           'C'

/* STM32 GPIO MODER encodings. */
#define INPUT           0U
#define OUTPUT          1U
#define ALTERNATE       2U
#define ANALOG          3U

#define PIN_0           0U
#define PIN_1           1U
#define PIN_2           2U
#define PIN_3           3U
#define PIN_4           4U
#define PIN_5           5U
#define PIN_6           6U
#define PIN_7           7U
#define PIN_8           8U
#define PIN_9           9U
#define PIN_10          10U
#define PIN_11          11U
#define PIN_12          12U
#define PIN_13          13U
#define PIN_14          14U
#define PIN_15          15U

/** Enable the peripheral clock for GPIO port A, B, or C. */
void gpio_init(uint8_t port);

/** Configure one GPIO pin in the requested STM32 GPIO mode. */
void gpio_config(uint8_t port, uint8_t pin, uint8_t mode);

#endif /* GPIO_H */
