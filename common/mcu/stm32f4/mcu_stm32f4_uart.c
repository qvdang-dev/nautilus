/**
 * @file  mcu_stm32f4_uart.c
 * @brief STM32F4 UART implementation for the MCU abstraction layer.
 *
 * Supports multiple USART instances.  The mcu_uart_t handle is the USART
 * base address (e.g. MCU_USART2_BASE).
 */

#include "mcu_stm32f4_impl.h"
#include "mcu_stm32f4_regs.h"

/* ------------------------------------------------------------------ */
/*  USART to GPIO pin mapping (TX, RX) for supported instances          */
/* ------------------------------------------------------------------ */

typedef struct {
    uint32_t base;
    mcu_gpio_port_t tx_port;
    uint16_t tx_pin;
    mcu_gpio_port_t rx_port;
    uint16_t rx_pin;
    uint32_t rcc_usart_bit;
    uint32_t rcc_gpio_bit;
} usart_config_t;

static const usart_config_t s_usart_configs[] = {
    { MCU_USART2_BASE, (mcu_gpio_port_t)MCU_GPIOA_BASE, 2, (mcu_gpio_port_t)MCU_GPIOA_BASE, 3,
      MCU_RCC_APB1ENR_USART2EN, MCU_RCC_AHB1ENR_GPIOAEN },
    /* USART1: PA9/PA10 (AF7) - APB2 */
    { MCU_USART1_BASE, (mcu_gpio_port_t)MCU_GPIOA_BASE, 9, (mcu_gpio_port_t)MCU_GPIOA_BASE, 10,
      MCU_RCC_APB2ENR_USART1EN, MCU_RCC_AHB1ENR_GPIOAEN },
    /* USART6: PA11/PA12 (AF8) - APB2 */
    { MCU_USART6_BASE, (mcu_gpio_port_t)MCU_GPIOA_BASE, 11, (mcu_gpio_port_t)MCU_GPIOA_BASE, 12,
      MCU_RCC_APB2ENR_USART6EN, MCU_RCC_AHB1ENR_GPIOAEN },
};

static const usart_config_t *find_usart_config(mcu_uart_t uart)
{
    for (int i = 0; i < (int)(sizeof(s_usart_configs) / sizeof(s_usart_configs[0])); i++) {
        if ((void *)(uintptr_t)s_usart_configs[i].base == uart) {
            return &s_usart_configs[i];
        }
    }
    return NULL;
}

/* ------------------------------------------------------------------ */
/*  UART implementation                                                 */
/* ------------------------------------------------------------------ */

void mcu_stm32f4_uart_init(mcu_uart_t uart, uint32_t baud)
{
    const usart_config_t *cfg = find_usart_config(uart);
    if (!cfg) {
        /* Invalid UART handle - silently return */
        return;
    }

    /* Enable USART and GPIO clocks */
    MCU_RCC_AHB1ENR |= cfg->rcc_gpio_bit;
    if (cfg->base == MCU_USART2_BASE || cfg->base == MCU_USART3_BASE ||
        cfg->base == MCU_UART4_BASE || cfg->base == MCU_UART5_BASE) {
        MCU_RCC_APB1ENR |= cfg->rcc_usart_bit;
    } else {
        MCU_RCC_APB2ENR |= cfg->rcc_usart_bit;
    }

    /* Configure TX and RX pins as alternate function */
    mcu_stm32f4_gpio_mode(cfg->tx_port, cfg->tx_pin, MCU_GPIO_MODE_AF);
    mcu_stm32f4_gpio_mode(cfg->rx_port, cfg->rx_pin, MCU_GPIO_MODE_AF);

    /* BRR: APB1 @ 42 MHz, APB2 @ 84 MHz; for 115200 baud:
     * APB1: 0x16D, APB2: 0x2D8 (approx) */
    uint32_t brr = (cfg->base == MCU_USART2_BASE) ? 0x16D : 0x2D8;
    MCU_USART_BRR(cfg->base) = brr;
    MCU_USART_CR1(cfg->base) = MCU_USART_CR1_UE | MCU_USART_CR1_TE | MCU_USART_CR1_RE;
}

void mcu_stm32f4_uart_putc(mcu_uart_t uart, char c)
{
    const usart_config_t *cfg = find_usart_config(uart);
    if (!cfg) {
        /* Invalid UART handle - silently return */
        return;
    }
    uint32_t base = cfg->base;
    /* Wait for TX ready with timeout to prevent infinite loop */
    for (volatile int timeout = 1000000; timeout > 0; timeout--) {
        if (MCU_USART_SR(base) & MCU_USART_SR_TXE) break;
    }
    MCU_USART_DR(base) = (uint32_t)(unsigned char)c;
}

void mcu_stm32f4_uart_puts(mcu_uart_t uart, const char *s)
{
    while (*s) mcu_stm32f4_uart_putc(uart, *s++);
}

char mcu_stm32f4_uart_getc(mcu_uart_t uart)
{
    const usart_config_t *cfg = find_usart_config(uart);
    if (!cfg) {
        /* Invalid UART handle - return null character */
        return '\0';
    }
    uint32_t base = cfg->base;
    /* Wait for RX ready with timeout to prevent infinite loop */
    for (volatile int timeout = 1000000; timeout > 0; timeout--) {
        if (MCU_USART_SR(base) & MCU_USART_SR_RXNE) break;
    }
    return (char)(MCU_USART_DR(base) & 0xFFU);
}