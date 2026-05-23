/**
 * @file  uart.c
 * @brief Board-agnostic UART driver — uses the MCU + board abstraction.
 *
 * The console UART is obtained from the active board descriptor, so
 * the same driver code works on any board that defines a UART entry.
 */

#include "uart.h"
#include "boards.h"
#include "mcu.h"

/* ------------------------------------------------------------------ */
/*  Find the console UART in the board descriptor                      */
/* ------------------------------------------------------------------ */

static const board_uart_t *find_console_uart(void)
{
    const board_t *board = board_get();
    for (int i = 0; i < board->uart_count; i++) {
        if (__builtin_strcmp(board->uarts[i].name, "UART_CONSOLE") == 0) {
            return &board->uarts[i];
        }
    }
    return NULL;
}

/* ------------------------------------------------------------------ */
/*  Public API                                                         */
/* ------------------------------------------------------------------ */

void uart_init(void)
{
    const board_uart_t *uart = find_console_uart();
    if (uart) {
        mcu_get()->uart_init(uart->uart, uart->baud);
    }
}

void uart_putc(char c)
{
    const board_uart_t *uart = find_console_uart();
    if (uart) {
        mcu_get()->uart_putc(uart->uart, c);
    }
}

void uart_puts(const char *s)
{
    const board_uart_t *uart = find_console_uart();
    if (uart) {
        mcu_get()->uart_puts(uart->uart, s);
    }
}

char uart_getc(void)
{
    const board_uart_t *uart = find_console_uart();
    if (uart) {
        return mcu_get()->uart_getc(uart->uart);
    }
    return 0;
}
