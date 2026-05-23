/**
 * @file  uart.h
 * @brief UART / console driver for debug output over USART.
 */

#ifndef UART_H
#define UART_H

#include <stdint.h>

/**
 * @brief Initialise the debug UART (USART2, 115200 baud, 8N1).
 */
void uart_init(void);

/**
 * @brief Transmit a single character over UART.
 * @param c  Character to send.
 */
void uart_putc(char c);

/**
 * @brief Transmit a null-terminated string over UART.
 * @param s  Pointer to the string.
 */
void uart_puts(const char *s);

/**
 * @brief Receive a single character from UART (blocking).
 * @return Received character.
 */
char uart_getc(void);

#endif /* UART_H */
