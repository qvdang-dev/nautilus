/**
 * @file  led.c
 * @brief Board-agnostic LED driver — uses the MCU + board abstraction.
 *
 * This driver knows nothing about specific GPIO registers or pin numbers.
 * It obtains the LED descriptors from board_get() and performs GPIO
 * operations through mcu_get().
 *
 * To add LED support on a new board:
 *   1. Add LED entries to the board_t descriptor in the board file.
 *   2. Ensure the MCU implementation supports gpio_write / gpio_toggle.
 */

#include "led.h"
#include "boards.h"
#include "mcu.h"

/* ------------------------------------------------------------------ */
/*  Find an LED by name                                                */
/* ------------------------------------------------------------------ */

static const board_led_t *find_led(const char *name)
{
    const board_t *board = board_get();
    for (int i = 0; i < board->led_count; i++) {
        if (__builtin_strcmp(board->leds[i].name, name) == 0) {
            return &board->leds[i];
        }
    }
    return NULL;
}

/* ------------------------------------------------------------------ */
/*  Public API                                                         */
/* ------------------------------------------------------------------ */

void led_init(void)
{
    const board_t *board = board_get();
    const mcu_t   *mcu   = mcu_get();

    for (int i = 0; i < board->led_count; i++) {
        const board_led_t *led = &board->leds[i];
        /* Configure as general-purpose output (mode 1 on STM32) */
        mcu->gpio_mode(led->port, led->pin, 0x1U);
        mcu->gpio_write(led->port, led->pin, led->active_level ? 0 : 1);
    }
}

void led_on(const char *name)
{
    const board_led_t *led = find_led(name);
    if (led) {
        mcu_get()->gpio_write(led->port, led->pin, led->active_level);
    }
}

void led_off(const char *name)
{
    const board_led_t *led = find_led(name);
    if (led) {
        mcu_get()->gpio_write(led->port, led->pin, led->active_level ? 0 : 1);
    }
}

void led_toggle(const char *name)
{
    const board_led_t *led = find_led(name);
    if (led) {
        mcu_get()->gpio_toggle(led->port, led->pin);
    }
}
