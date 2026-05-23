/**
 * @file  utils.c
 * @brief Utility helpers — uses the MCU abstraction for timing.
 */

#include "utils.h"
#include "mcu.h"

void delay_ms(uint32_t ms)
{
    mcu_get()->delay_ms(ms);
}
