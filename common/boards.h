/**
 * @file  boards.h
 * @brief Board abstraction layer — hardware-agnostic board descriptors.
 *
 * Each supported board has a `board_t` definition that maps logical
 * peripherals (LEDs, buttons, UART instances) to MCU-level GPIO ports
 * and pins.  Adding a new board requires only a new `board_t` instance
 * — no changes to driver code.
 *
 * The active board is selected at compile time via the `BOARD` macro
 * (set by the Makefile).  Exactly one board file must be linked.
 */

#ifndef BOARDS_H
#define BOARDS_H

#include <stdint.h>
#include "mcu.h"

/* ------------------------------------------------------------------ */
/*  LED descriptor                                                     */
/* ------------------------------------------------------------------ */

typedef struct {
    const char    *name;        /* e.g. "LED_GREEN" */
    mcu_gpio_port_t port;       /* MCU GPIO port */
    uint16_t        pin;         /* MCU GPIO pin  */
    uint32_t        active_level;/* 1 = active-high, 0 = active-low */
} board_led_t;

/* ------------------------------------------------------------------ */
/*  Button descriptor                                                  */
/* ------------------------------------------------------------------ */

typedef struct {
    const char    *name;        /* e.g. "BTN_USER" */
    mcu_gpio_port_t port;
    uint16_t        pin;
    uint32_t        active_level;/* 1 = active-high, 0 = active-low */
} board_btn_t;

/* ------------------------------------------------------------------ */
/*  UART descriptor                                                    */
/* ------------------------------------------------------------------ */

typedef struct {
    const char  *name;          /* e.g. "UART_CONSOLE" */
    mcu_uart_t   uart;          /* MCU UART instance */
    uint32_t     baud;          /* Default baud rate */
} board_uart_t;

/* ------------------------------------------------------------------ */
/*  Board descriptor                                                   */
/* ------------------------------------------------------------------ */

typedef struct {
    const char     *name;       /* e.g. "STM32F4-Discovery" */
    const char     *mcu_name;   /* e.g. "STM32F407VG" — must match an mcu_t */

    uint8_t         led_count;
    const board_led_t *leds;

    uint8_t         btn_count;
    const board_btn_t *btns;

    uint8_t         uart_count;
    const board_uart_t *uarts;
} board_t;

/* ------------------------------------------------------------------ */
/*  Global accessor                                                    */
/* ------------------------------------------------------------------ */

/**
 * @brief Return the active board descriptor.
 *
 * The implementation is provided by the board-specific file (e.g.
 * board_stm32f4_discovery.c).  Exactly one board file must be linked.
 */
const board_t *board_get(void);

#endif /* BOARDS_H */
