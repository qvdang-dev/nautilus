/**
 * @file  mcu_stm32f4.c
 * @brief MCU abstraction implementation for the STM32F4xx family.
 *
 * Implements the `mcu_t` vtable using register-level access to the
 * STM32F4 peripheral registers.  This file is the only place that
 * knows about STM32F4-specific register addresses — all higher-level
 * code goes through the `mcu_t` interface.
 *
 * To port to a different MCU family, create a new file (e.g.
 * mcu_stm32f1.c) that populates the same `mcu_t` struct with the
 * register addresses and bit masks for that MCU.
 */

#include "mcu.h"
#include <stdint.h>

/* ====================================================================== */
/*  STM32F4 register base addresses                                        */
/* ====================================================================== */

#define RCC_BASE       (0x40023800UL)
#define GPIOA_BASE     (0x40020000UL)
#define GPIOB_BASE     (0x40020400UL)
#define GPIOC_BASE     (0x40020800UL)
#define GPIOD_BASE     (0x40020C00UL)
#define GPIOE_BASE     (0x40021000UL)
#define GPIOF_BASE     (0x40021400UL)
#define GPIOG_BASE     (0x40021800UL)
#define GPIOH_BASE     (0x40021C00UL)
#define GPIOI_BASE     (0x40022000UL)
#define USART2_BASE    (0x40004400UL)

/* ====================================================================== */
/*  Register access helpers                                                */
/* ====================================================================== */

#define REG32(addr)    (*((volatile uint32_t *)(addr)))

#define RCC_AHB1ENR    REG32(RCC_BASE  + 0x30)   /* GPIO clock enable  */
#define RCC_APB1ENR    REG32(RCC_BASE  + 0x40)   /* USART clock enable */

#define GPIO_MODER(p)  REG32((p) + 0x00)
#define GPIO_OTYPER(p) REG32((p) + 0x04)
#define GPIO_BSRR(p)   REG32((p) + 0x18)
#define GPIO_IDR(p)    REG32((p) + 0x10)

#define USART_SR(b)    REG32((b) + 0x00)
#define USART_DR(b)    REG32((b) + 0x04)
#define USART_BRR(b)   REG32((b) + 0x08)
#define USART_CR1(b)   REG32((b) + 0x0C)

#define USART_SR_TXE   (1U << 7)
#define USART_SR_RXNE  (1U << 5)
#define USART_CR1_UE   (1U << 13)
#define USART_CR1_TE   (1U << 3)
#define USART_CR1_RE   (1U << 2)

#define RCC_AHB1ENR_GPIOAEN  (1U << 0)
#define RCC_AHB1ENR_GPIOBEN  (1U << 1)
#define RCC_AHB1ENR_GPIOCEN  (1U << 2)
#define RCC_AHB1ENR_GPIODEN  (1U << 3)
#define RCC_AHB1ENR_GPIOEEN  (1U << 4)
#define RCC_AHB1ENR_GPIOFEN  (1U << 5)
#define RCC_AHB1ENR_GPIOGEN  (1U << 6)
#define RCC_AHB1ENR_GPIOHEN  (1U << 7)
#define RCC_AHB1ENR_GPIOIEN  (1U << 8)

#define RCC_APB1ENR_USART2EN (1U << 17)

/* ====================================================================== */
/*  GPIO helpers                                                           */
/* ====================================================================== */

static inline uint32_t gpio_rcc_en_bit(mcu_gpio_port_t port)
{
    if      (port == (void *)GPIOA_BASE) return RCC_AHB1ENR_GPIOAEN;
    else if (port == (void *)GPIOB_BASE) return RCC_AHB1ENR_GPIOBEN;
    else if (port == (void *)GPIOC_BASE) return RCC_AHB1ENR_GPIOCEN;
    else if (port == (void *)GPIOD_BASE) return RCC_AHB1ENR_GPIODEN;
    else if (port == (void *)GPIOE_BASE) return RCC_AHB1ENR_GPIOEEN;
    else if (port == (void *)GPIOF_BASE) return RCC_AHB1ENR_GPIOFEN;
    else if (port == (void *)GPIOG_BASE) return RCC_AHB1ENR_GPIOGEN;
    else if (port == (void *)GPIOH_BASE) return RCC_AHB1ENR_GPIOHEN;
    else if (port == (void *)GPIOI_BASE) return RCC_AHB1ENR_GPIOIEN;
    return 0;
}

static void stm32f4_gpio_mode(mcu_gpio_port_t port, uint16_t pin, uint32_t mode)
{
    uint32_t rcc_bit = gpio_rcc_en_bit(port);
    if (rcc_bit) RCC_AHB1ENR |= rcc_bit;          /* enable GPIO clock */

    uint32_t reg = GPIO_MODER(port);
    reg &= ~(0x3U << (pin * 2));
    reg |=  (mode  << (pin * 2));
    GPIO_MODER(port) = reg;
}

static void stm32f4_gpio_write(mcu_gpio_port_t port, uint16_t pin, uint32_t value)
{
    if (value) {
        GPIO_BSRR(port) = (1U << pin);
    } else {
        GPIO_BSRR(port) = (1U << (pin + 16));
    }
}

static uint32_t stm32f4_gpio_read(mcu_gpio_port_t port, uint16_t pin)
{
    return (GPIO_IDR(port) >> pin) & 1U;
}

static void stm32f4_gpio_toggle(mcu_gpio_port_t port, uint16_t pin)
{
    GPIO_BSRR(port) = (1U << (pin + 16));   /* reset bit toggles */
}

/* ====================================================================== */
/*  UART helpers                                                           */
/* ====================================================================== */

#define GPIO_MODE_AF   (0x2U)
#define GPIO_AF7_USART2 (0x7U)

static void stm32f4_uart_init(mcu_uart_t uart, uint32_t baud)
{
    (void)uart;
    uint32_t base = USART2_BASE;

    /* Enable USART2 and GPIOA clocks */
    RCC_APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* PA2 = USART2_TX, PA3 = USART2_RX — alternate function 7 */
    stm32f4_gpio_mode((mcu_gpio_port_t)GPIOA_BASE, 2, GPIO_MODE_AF);
    stm32f4_gpio_mode((mcu_gpio_port_t)GPIOA_BASE, 3, GPIO_MODE_AF);

    /* BRR: APB1 @ 42 MHz, 115200 baud → 0x16D */
    USART_BRR(base) = 0x16D;
    USART_CR1(base) = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

static void stm32f4_uart_putc(mcu_uart_t uart, char c)
{
    (void)uart;
    uint32_t base = USART2_BASE;
    while ((USART_SR(base) & USART_SR_TXE) == 0) { __asm volatile ("nop"); }
    USART_DR(base) = (uint32_t)(unsigned char)c;
}

static void stm32f4_uart_puts(mcu_uart_t uart, const char *s)
{
    (void)uart;
    while (*s) stm32f4_uart_putc(NULL, *s++);
}

static char stm32f4_uart_getc(mcu_uart_t uart)
{
    (void)uart;
    uint32_t base = USART2_BASE;
    while ((USART_SR(base) & USART_SR_RXNE) == 0) { __asm volatile ("nop"); }
    return (char)(USART_DR(base) & 0xFFU);
}

/* ====================================================================== */
/*  System helpers                                                        */
/* ====================================================================== */

extern uint32_t SystemCoreClock;   /* defined in system_stm32f4xx.c */

static void stm32f4_delay_ms(uint32_t ms)
{
    const uint32_t cycles_per_ms = SystemCoreClock / 1000U;
    while (ms--) {
        for (volatile uint32_t i = 0; i < cycles_per_ms; i++) {
            __asm volatile ("nop");
        }
    }
}

static uint32_t stm32f4_get_sysclk(void)
{
    return SystemCoreClock;
}

/* ====================================================================== */
/*  MCU vtable — the single object that represents "this MCU"             */
/* ====================================================================== */

static const mcu_t g_mcu_stm32f4 = {
    .name       = "STM32F407VG",

    /* GPIO */
    .gpio_mode   = stm32f4_gpio_mode,
    .gpio_write  = stm32f4_gpio_write,
    .gpio_read   = stm32f4_gpio_read,
    .gpio_toggle = stm32f4_gpio_toggle,

    /* UART */
    .uart_init   = stm32f4_uart_init,
    .uart_putc   = stm32f4_uart_putc,
    .uart_puts   = stm32f4_uart_puts,
    .uart_getc   = stm32f4_uart_getc,

    /* System */
    .delay_ms    = stm32f4_delay_ms,
    .get_sysclk  = stm32f4_get_sysclk,
};

/* ====================================================================== */
/*  Public accessor                                                       */
/* ====================================================================== */

const mcu_t *mcu_get(void)
{
    return &g_mcu_stm32f4;
}
