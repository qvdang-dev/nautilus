/**
 * @file  mcu_stm32f4_impl.h
 * @brief STM32F4 MCU implementation function declarations.
 *
 * This header declares the STM32F4-specific implementations of the
 * mcu_t vtable functions.  It is included by mcu_stm32f4.c to
 * populate the vtable, and by the implementation files to ensure
 * consistent signatures.
 */

#ifndef MCU_STM32F4_IMPL_H
#define MCU_STM32F4_IMPL_H

#include "mcu.h"

/* GPIO */
void mcu_stm32f4_gpio_mode(mcu_gpio_port_t port, uint16_t pin, uint32_t mode);
void mcu_stm32f4_gpio_write(mcu_gpio_port_t port, uint16_t pin, uint32_t value);
uint32_t mcu_stm32f4_gpio_read(mcu_gpio_port_t port, uint16_t pin);
void mcu_stm32f4_gpio_toggle(mcu_gpio_port_t port, uint16_t pin);

/* UART */
void mcu_stm32f4_uart_init(mcu_uart_t uart, uint32_t baud);
void mcu_stm32f4_uart_putc(mcu_uart_t uart, char c);
void mcu_stm32f4_uart_puts(mcu_uart_t uart, const char *s);
char mcu_stm32f4_uart_getc(mcu_uart_t uart);

/* System */
void mcu_stm32f4_delay_ms(uint32_t ms);
uint32_t mcu_stm32f4_get_sysclk(void);

#endif /* MCU_STM32F4_IMPL_H */