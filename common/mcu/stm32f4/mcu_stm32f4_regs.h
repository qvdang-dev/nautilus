/**
 * @file  mcu_stm32f4_regs.h
 * @brief STM32F4xx register definitions — internal to MCU implementation.
 *
 * This header is used only by the STM32F4 MCU implementation files.
 * It is NOT included by the portable mcu.h interface.
 *
 * Provides both low-level BASE addresses and user-friendly port/handle macros
 * for use in board definition files.
 */

#ifndef MCU_STM32F4_REGS_H
#define MCU_STM32F4_REGS_H

#include <stdint.h>

/* ====================================================================== */
/*  STM32F4 register base addresses (low-level)                             */
/* ====================================================================== */

#define MCU_RCC_BASE       (0x40023800UL)
#define MCU_GPIOA_BASE     (0x40020000UL)
#define MCU_GPIOB_BASE     (0x40020400UL)
#define MCU_GPIOC_BASE     (0x40020800UL)
#define MCU_GPIOD_BASE     (0x40020C00UL)
#define MCU_GPIOE_BASE     (0x40021000UL)
#define MCU_GPIOF_BASE     (0x40021400UL)
#define MCU_GPIOG_BASE     (0x40021800UL)
#define MCU_GPIOH_BASE     (0x40021C00UL)
#define MCU_GPIOI_BASE     (0x40022000UL)

/* USART base addresses */
#define MCU_USART1_BASE     (0x40011000UL)  /* APB2 */
#define MCU_USART2_BASE     (0x40004400UL)  /* APB1 */
#define MCU_USART3_BASE     (0x40004800UL)  /* APB1 */
#define MCU_UART4_BASE      (0x40005000UL)  /* APB1 */
#define MCU_UART5_BASE      (0x40005400UL)  /* APB1 */
#define MCU_USART6_BASE     (0x40011400UL)  /* APB2 */

/* ====================================================================== */
/*  User-friendly GPIO port handles (for board definitions)               */
/* ====================================================================== */

#define MCU_GPIO_PORT_A     ((mcu_gpio_port_t)MCU_GPIOA_BASE)
#define MCU_GPIO_PORT_B     ((mcu_gpio_port_t)MCU_GPIOB_BASE)
#define MCU_GPIO_PORT_C     ((mcu_gpio_port_t)MCU_GPIOC_BASE)
#define MCU_GPIO_PORT_D     ((mcu_gpio_port_t)MCU_GPIOD_BASE)
#define MCU_GPIO_PORT_E     ((mcu_gpio_port_t)MCU_GPIOE_BASE)
#define MCU_GPIO_PORT_F     ((mcu_gpio_port_t)MCU_GPIOF_BASE)
#define MCU_GPIO_PORT_G     ((mcu_gpio_port_t)MCU_GPIOG_BASE)
#define MCU_GPIO_PORT_H     ((mcu_gpio_port_t)MCU_GPIOH_BASE)
#define MCU_GPIO_PORT_I     ((mcu_gpio_port_t)MCU_GPIOI_BASE)

/* ====================================================================== */
/*  User-friendly USART handles (for board definitions)                     */
/* ====================================================================== */

#define MCU_USART1          ((mcu_uart_t)MCU_USART1_BASE)
#define MCU_USART2          ((mcu_uart_t)MCU_USART2_BASE)
#define MCU_USART3          ((mcu_uart_t)MCU_USART3_BASE)
#define MCU_UART4           ((mcu_uart_t)MCU_UART4_BASE)
#define MCU_UART5           ((mcu_uart_t)MCU_UART5_BASE)
#define MCU_USART6          ((mcu_uart_t)MCU_USART6_BASE)

/* ====================================================================== */
/*  Register access macros                                                 */
/* ====================================================================== */

#define MCU_REG32(addr)    (*((volatile uint32_t *)(addr)))

/* RCC */
#define MCU_RCC_AHB1ENR    MCU_REG32(MCU_RCC_BASE  + 0x30)
#define MCU_RCC_APB1ENR    MCU_REG32(MCU_RCC_BASE  + 0x40)
#define MCU_RCC_APB2ENR    MCU_REG32(MCU_RCC_BASE  + 0x44)

/* GPIO */
#define MCU_GPIO_MODER(p)  MCU_REG32((p) + 0x00)
#define MCU_GPIO_OTYPER(p) MCU_REG32((p) + 0x04)
#define MCU_GPIO_BSRR(p)   MCU_REG32((p) + 0x18)
#define MCU_GPIO_IDR(p)    MCU_REG32((p) + 0x10)

/* USART */
#define MCU_USART_SR(b)    MCU_REG32((b) + 0x00)
#define MCU_USART_DR(b)    MCU_REG32((b) + 0x04)
#define MCU_USART_BRR(b)   MCU_REG32((b) + 0x08)
#define MCU_USART_CR1(b)   MCU_REG32((b) + 0x0C)

/* ====================================================================== */
/*  Bit definitions                                                        */
/* ====================================================================== */

/* GPIO mode */
#define MCU_GPIO_MODE_INPUT     (0x0U)
#define MCU_GPIO_MODE_OUTPUT    (0x1U)
#define MCU_GPIO_MODE_AF        (0x2U)
#define MCU_GPIO_MODE_ANALOG    (0x3U)

/* RCC bits */
#define MCU_RCC_AHB1ENR_GPIOAEN  (1U << 0)
#define MCU_RCC_AHB1ENR_GPIOBEN  (1U << 1)
#define MCU_RCC_AHB1ENR_GPIOCEN  (1U << 2)
#define MCU_RCC_AHB1ENR_GPIODEN  (1U << 3)
#define MCU_RCC_AHB1ENR_GPIOEEN  (1U << 4)
#define MCU_RCC_AHB1ENR_GPIOFEN  (1U << 5)
#define MCU_RCC_AHB1ENR_GPIOGEN  (1U << 6)
#define MCU_RCC_AHB1ENR_GPIOHEN  (1U << 7)
#define MCU_RCC_AHB1ENR_GPIOIEN  (1U << 8)

#define MCU_RCC_APB1ENR_USART2EN (1U << 17)
#define MCU_RCC_APB1ENR_USART3EN (1U << 18)
#define MCU_RCC_APB1ENR_UART4EN  (1U << 19)
#define MCU_RCC_APB1ENR_UART5EN  (1U << 20)

#define MCU_RCC_APB2ENR_USART1EN (1U << 4)
#define MCU_RCC_APB2ENR_USART6EN (1U << 5)

/* USART bits */
#define MCU_USART_SR_TXE   (1U << 7)
#define MCU_USART_SR_RXNE  (1U << 5)
#define MCU_USART_CR1_UE   (1U << 13)
#define MCU_USART_CR1_TE   (1U << 3)
#define MCU_USART_CR1_RE   (1U << 2)

#endif /* MCU_STM32F4_REGS_H */