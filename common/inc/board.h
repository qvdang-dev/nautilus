/**
 * @file  board.h
 * @brief Board-level definitions for the STM32F4-Discovery board.
 *
 * Provides symbolic names for on-board peripherals (LEDs, user button)
 * so that application code remains portable across revisions.
 */

#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

/* --------------------------------------------------------------------------
 * On-board LEDs  (STM32F4-Discovery)
 * -------------------------------------------------------------------------- */

#define LED_GREEN_PIN       (13U)   /* PG13 — Green LED  */
#define LED_RED_PIN         (14U)   /* PG14 — Red LED    */
#define LED_ORANGE_PIN      (0U)    /* PA0  — Orange LED */
#define LED_BLUE_PIN        (1U)    /* PA1  — Blue LED   */

#define LED_GREEN_PORT      GPIOG
#define LED_RED_PORT        GPIOG
#define LED_ORANGE_PORT     GPIOA
#define LED_BLUE_PORT       GPIOA

/* --------------------------------------------------------------------------
 * User button  (STM32F4-Discovery)
 * -------------------------------------------------------------------------- */

#define BTN_USER_PIN        (0U)    /* PA0 — User button */
#define BTN_USER_PORT       GPIOA
#define BTN_USER_PRESSED    (0U)    /* Active-low */

#endif /* BOARD_H */
