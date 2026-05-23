/**
 * @file  utils.h
 * @brief Utility macros and helpers for the nautilus firmware.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * @brief Perform a simple blocking delay.
 * @param ms  Delay in milliseconds.
 *
 * Uses a simple loop-based delay; for RTOS-aware delays use
 * vTaskDelay() (FreeRTOS) instead.
 */
void delay_ms(uint32_t ms);

/**
 * @brief Count leading zeros in a 32-bit word.
 * @param x  Input value.
 * @return   Number of leading zero bits.
 */
static inline uint32_t clz32(uint32_t x)
{
    uint32_t n = 0;
    if (x == 0) return 32;
    while ((x & 0x80000000U) == 0) { x <<= 1; n++; }
    return n;
}

#endif /* UTILS_H */
