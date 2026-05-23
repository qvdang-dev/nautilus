/**
 * @file  mcu.h
 * @brief MCU abstraction layer — hardware-agnostic interface.
 *
 * Every MCU family (STM32F4, STM32F1, nRF52, …) provides its own
 * implementation of the `mcu_t` vtable.  All drivers in `common/src/`
 * go through this interface so that switching MCUs requires only
 * linking a different `mcu_*.c` file — no driver code changes.
 *
 * Usage:
 *   const mcu_t *mcu = mcu_get();   // returns the active MCU vtable
 *   mcu->gpio_write(port, pin, 1);  // set pin high
 */

#ifndef MCU_H
#define MCU_H

#include <stdint.h>

/* ------------------------------------------------------------------ */
/*  Forward declarations                                               */
/* ------------------------------------------------------------------ */

typedef struct mcu_s mcu_t;

/* ------------------------------------------------------------------ */
/*  GPIO                                                               */
/* ------------------------------------------------------------------ */

/** GPIO port identifier — opaque, MCU-specific. */
typedef void *mcu_gpio_port_t;

/** Configure a GPIO pin as input, output, alternate-function, or analog. */
typedef void (*mcu_gpio_mode_fn)(mcu_gpio_port_t port, uint16_t pin, uint32_t mode);

/** Write a logic level to a GPIO output pin. */
typedef void (*mcu_gpio_write_fn)(mcu_gpio_port_t port, uint16_t pin, uint32_t value);

/** Read the current level of a GPIO input pin. Returns 0 or 1. */
typedef uint32_t (*mcu_gpio_read_fn)(mcu_gpio_port_t port, uint16_t pin);

/** Toggle a GPIO output pin. */
typedef void (*mcu_gpio_toggle_fn)(mcu_gpio_port_t port, uint16_t pin);

/* ------------------------------------------------------------------ */
/*  UART                                                               */
/* ------------------------------------------------------------------ */

typedef void *mcu_uart_t;

typedef void (*mcu_uart_init_fn)(mcu_uart_t uart, uint32_t baud);
typedef void (*mcu_uart_putc_fn)(mcu_uart_t uart, char c);
typedef void (*mcu_uart_puts_fn)(mcu_uart_t uart, const char *s);
typedef char  (*mcu_uart_getc_fn)(mcu_uart_t uart);

/* ------------------------------------------------------------------ */
/*  System / delay                                                     */
/* ------------------------------------------------------------------ */

/** Blocking millisecond delay. Not RTOS-safe. */
typedef void (*mcu_delay_ms_fn)(uint32_t ms);

/** Return the current system core clock in Hz. */
typedef uint32_t (*mcu_get_sysclk_fn)(void);

/* ------------------------------------------------------------------ */
/*  MCU vtable                                                         */
/* ------------------------------------------------------------------ */

struct mcu_s {
    const char *name;            /* e.g. "STM32F407VG" */

    /* GPIO */
    mcu_gpio_mode_fn   gpio_mode;
    mcu_gpio_write_fn  gpio_write;
    mcu_gpio_read_fn   gpio_read;
    mcu_gpio_toggle_fn gpio_toggle;

    /* UART */
    mcu_uart_init_fn   uart_init;
    mcu_uart_putc_fn   uart_putc;
    mcu_uart_puts_fn   uart_puts;
    mcu_uart_getc_fn   uart_getc;

    /* System */
    mcu_delay_ms_fn    delay_ms;
    mcu_get_sysclk_fn  get_sysclk;
};

/* ------------------------------------------------------------------ */
/*  Global accessor                                                    */
/* ------------------------------------------------------------------ */

/**
 * @brief Return the active MCU vtable.
 *
 * The implementation is provided by the MCU-specific file (e.g.
 * mcu_stm32f4.c).  Exactly one MCU file must be linked into the build.
 */
const mcu_t *mcu_get(void);

#endif /* MCU_H */
