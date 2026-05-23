/**
 * @file  led.h
 * @brief Board-agnostic LED driver — uses the MCU + board abstraction.
 *
 * LEDs are identified by their board-level name (e.g. "LED_GREEN")
 * rather than raw GPIO pin numbers, making this driver portable across
 * any board that provides a board_t descriptor.
 */

#ifndef LED_H
#define LED_H

#include <stdint.h>

/**
 * @brief Initialise all LEDs defined in the active board descriptor.
 *
 * Configures each LED GPIO as a push-pull output and sets the initial
 * level to "off" (inverse of active_level).
 */
void led_init(void);

/**
 * @brief Turn an LED on by board-level name.
 * @param name  LED name as defined in the board descriptor
 *              (e.g. "LED_GREEN", "LED_RED").
 *              Passing NULL is a no-op.
 */
void led_on(const char *name);

/**
 * @brief Turn an LED off by board-level name.
 * @param name  LED name as defined in the board descriptor.
 *              Passing NULL is a no-op.
 */
void led_off(const char *name);

/**
 * @brief Toggle an LED by board-level name.
 * @param name  LED name as defined in the board descriptor.
 *              Passing NULL is a no-op.
 */
void led_toggle(const char *name);

#endif /* LED_H */
