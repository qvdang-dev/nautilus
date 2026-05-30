/**
 * @file  mcu_stm32f4_gpio.c
 * @brief STM32F4 GPIO implementation for the MCU abstraction layer.
 */

#include "mcu_stm32f4_impl.h"
#include "mcu_stm32f4_regs.h"

/* ------------------------------------------------------------------ */
/*  GPIO port to RCC enable bit mapping                                 */
/* ------------------------------------------------------------------ */

static uint32_t mcu_stm32f4_gpio_rcc_en_bit(mcu_gpio_port_t port)
{
    if (port == (void *)MCU_GPIOA_BASE) {
        return MCU_RCC_AHB1ENR_GPIOAEN;
    }
    if (port == (void *)MCU_GPIOB_BASE) {
        return MCU_RCC_AHB1ENR_GPIOBEN;
    }
    if (port == (void *)MCU_GPIOC_BASE) {
        return MCU_RCC_AHB1ENR_GPIOCEN;
    }
    if (port == (void *)MCU_GPIOD_BASE) {
        return MCU_RCC_AHB1ENR_GPIODEN;
    }
    if (port == (void *)MCU_GPIOE_BASE) {
        return MCU_RCC_AHB1ENR_GPIOEEN;
    }
    if (port == (void *)MCU_GPIOF_BASE) {
        return MCU_RCC_AHB1ENR_GPIOFEN;
    }
    if (port == (void *)MCU_GPIOG_BASE) {
        return MCU_RCC_AHB1ENR_GPIOGEN;
    }
    if (port == (void *)MCU_GPIOH_BASE) {
        return MCU_RCC_AHB1ENR_GPIOHEN;
    }
    if (port == (void *)MCU_GPIOI_BASE) {
        return MCU_RCC_AHB1ENR_GPIOIEN;
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/*  Public GPIO functions                                             */
/* ------------------------------------------------------------------ */

void mcu_stm32f4_gpio_mode(mcu_gpio_port_t port, uint16_t pin, uint32_t mode)
{
    uint32_t rcc_bit = mcu_stm32f4_gpio_rcc_en_bit(port);
    if (rcc_bit) {
        MCU_RCC_AHB1ENR |= rcc_bit;
    }

    uint32_t reg = MCU_GPIO_MODER(port);
    reg &= ~(0x3U << (pin * 2));
    reg |=  (mode  << (pin * 2));
    MCU_GPIO_MODER(port) = reg;
}

void mcu_stm32f4_gpio_write(mcu_gpio_port_t port, uint16_t pin, uint32_t value)
{
    if (value) {
        MCU_GPIO_BSRR(port) = (1U << pin);
    } else {
        MCU_GPIO_BSRR(port) = (1U << (pin + 16));
    }
}

uint32_t mcu_stm32f4_gpio_read(mcu_gpio_port_t port, uint16_t pin)
{
    return (MCU_GPIO_IDR(port) >> pin) & 1U;
}

void mcu_stm32f4_gpio_toggle(mcu_gpio_port_t port, uint16_t pin)
{
    MCU_GPIO_BSRR(port) = (1U << (pin + 16));
}