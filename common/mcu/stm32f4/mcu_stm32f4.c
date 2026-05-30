/**
 * @file  mcu_stm32f4.c
 * @brief STM32F4 MCU vtable — ties together GPIO, UART, and system implementations.
 *
 * This file provides the `mcu_t` vtable for STM32F4xx MCUs.  The actual
 * implementations are split into separate files for maintainability:
 *   - mcu_stm32f4_gpio.c  — GPIO mode/write/read/toggle
 *   - mcu_stm32f4_uart.c  — UART init/putc/puts/getc
 *   - mcu_stm32f4_system.c — System functions (delay, clock)
 */

#include "mcu.h"
#include "mcu_stm32f4_impl.h"

/* ------------------------------------------------------------------ */
/*  MCU vtable                                                          */
/* ------------------------------------------------------------------ */

static const mcu_t g_mcu_stm32f4 = {
    .name       = "STM32F407VG",

    /* GPIO */
    .gpio_mode   = mcu_stm32f4_gpio_mode,
    .gpio_write  = mcu_stm32f4_gpio_write,
    .gpio_read   = mcu_stm32f4_gpio_read,
    .gpio_toggle = mcu_stm32f4_gpio_toggle,

    /* UART */
    .uart_init   = mcu_stm32f4_uart_init,
    .uart_putc   = mcu_stm32f4_uart_putc,
    .uart_puts   = mcu_stm32f4_uart_puts,
    .uart_getc   = mcu_stm32f4_uart_getc,

    /* System */
    .delay_ms    = mcu_stm32f4_delay_ms,
    .get_sysclk  = mcu_stm32f4_get_sysclk,
};

/* ------------------------------------------------------------------ */
/*  Public accessor                                                     */
/* ------------------------------------------------------------------ */

const mcu_t *mcu_get(void)
{
    return &g_mcu_stm32f4;
}