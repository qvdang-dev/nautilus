/**
 * @file  board_stm32f4_discovery.c
 * @brief Board descriptor for the STM32F4-Discovery (MB1047B).
 *
 * Maps the board's on-board peripherals to the STM32F4 MCU GPIO ports
 * and pins.  To add a new board, create a new file following this
 * pattern and link it conditionally via the Makefile.
 */

#include "boards.h"
#include "mcu.h"
#include "mcu_stm32f4_regs.h"

/* ====================================================================== */
/*  STM32F4-Discovery peripheral map                                      */
/* ====================================================================== */
/*
 *  LED_GREEN  → PG13  (active-high)
 *  LED_RED    → PG14  (active-high)
 *  LED_ORANGE → PA0   (active-high)
 *  LED_BLUE   → PA1   (active-high)
 *
 *  BTN_USER   → PA0   (active-low, same pin as LED_ORANGE — avoid conflict)
 *
 *  UART_CONSOLE → USART2 (PA2=TX, PA3=RX, 115200 8N1)
 */

/* ====================================================================== */
/*  LED array                                                               */
/* ====================================================================== */

static const board_led_t s_leds[] = {
    { "LED_GREEN",  MCU_GPIO_PORT_G, 13, 1 },
    { "LED_RED",    MCU_GPIO_PORT_G, 14, 1 },
    { "LED_ORANGE", MCU_GPIO_PORT_A,  0, 1 },
    { "LED_BLUE",   MCU_GPIO_PORT_A,  1, 1 },
};

/* ====================================================================== */
/*  Button array                                                           */
/* ====================================================================== */

static const board_btn_t s_btns[] = {
    { "BTN_USER", MCU_GPIO_PORT_A, 0, 0 },   /* active-low */
};

/* ====================================================================== */
/*  UART array                                                             */
/* ====================================================================== */

static const board_uart_t s_uarts[] = {
    { "UART_CONSOLE", MCU_USART2, 115200 },
};

/* ====================================================================== */
/*  Board descriptor                                                       */
/* ====================================================================== */

const board_t g_board_stm32f4_discovery = {
    .name       = "STM32F4-Discovery",
    .mcu_name   = "STM32F407VG",

    .led_count  = (uint8_t)(sizeof(s_leds)  / sizeof(s_leds[0])),
    .leds       = s_leds,

    .btn_count  = (uint8_t)(sizeof(s_btns)  / sizeof(s_btns[0])),
    .btns       = s_btns,

    .uart_count = (uint8_t)(sizeof(s_uarts) / sizeof(s_uarts[0])),
    .uarts      = s_uarts,
};

/* ====================================================================== */
/*  Public accessor                                                        */
/* ====================================================================== */

const board_t *board_get(void)
{
    return &g_board_stm32f4_discovery;
}