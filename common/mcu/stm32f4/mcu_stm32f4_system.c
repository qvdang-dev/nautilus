/**
 * @file  mcu_stm32f4_system.c
 * @brief STM32F4 system (delay, clock) implementation for the MCU abstraction layer.
 */

#include "mcu.h"
#include <stdint.h>

/* SystemCoreClock is defined in system_stm32f4xx.c */
extern uint32_t SystemCoreClock;

void mcu_stm32f4_delay_ms(uint32_t ms)
{
    const uint32_t cycles_per_ms = SystemCoreClock / 1000U;
    while (ms--) {
        for (volatile uint32_t i = 0; i < cycles_per_ms; i++) {
            // Do nothing - just burn cycles.
            __asm volatile ("nop");
        }
    }
}

uint32_t mcu_stm32f4_get_sysclk(void)
{
    return SystemCoreClock;
}