/**
 * @file  port.c
 * @brief FreeRTOS Cortex-M4 port layer for the STM32F4-Discovery.
 *
 * Implements the low-level context-switch and tick interrupt routines
 * required by the FreeRTOS kernel on ARM Cortex-M4.
 *
 * This file is intentionally minimal — in a production build it would
 * contain the full PendSV / SysTick handlers from the official
 * FreeRTOS port (port.c / portmacro.h for Cortex-M4).
 */

#include "FreeRTOS.h"
#include "task.h"

/* ------------------------------------------------------------------ */
/*  PendSV handler — performs the actual context switch              */
/* ------------------------------------------------------------------ */

__attribute__((naked)) void PendSV_Handler(void)
{
    __asm volatile (
        "   .syntax unified                         \n"
        "   mrs   r0, psp                           \n"
        "   mov   r1, lr                            \n"
        "   bl    vTaskSwitchContext                 \n"
        "   bl    vPortSetStackPointer               \n"
        "   bx    r14                                \n"
    );
}

/* ------------------------------------------------------------------ */
/*  SysTick handler — calls the FreeRTOS tick handler                 */
/* ------------------------------------------------------------------ */

void SysTick_Handler(void)
{
    if (xTaskIncrementTick() != pdFALSE) {
        portYIELD_FROM_ISR(pdTRUE);
    }
}

/* ------------------------------------------------------------------ */
/*  SVC handler — required for FreeRTOS API calls from thread mode    */
/* ------------------------------------------------------------------ */

void SVC_Handler(void)
{
    /* Handled by the FreeRTOS kernel; no application-level action needed. */
}

/* ------------------------------------------------------------------ */
/*  HardFault / MemManage / BusFault / UsageFault handlers            */
/* ------------------------------------------------------------------ */

void HardFault_Handler(void) __attribute__((naked));
void HardFault_Handler(void)
{
    __asm volatile (
        "   tst   lr, #4          \n"
        "   ite   eq              \n"
        "   mrseq r0, msp         \n"
        "   mrsne r0, psp         \n"
        "   b     HardFault_Handler_C \n"
    );
}

void HardFault_Handler_C(uint32_t *hardfault_args)
{
    (void)hardfault_args;
    /* TODO: log fault registers, blink red LED, halt. */
    for (;;) { __asm volatile ("nop"); }
}

void MemManage_Handler(void) __attribute__((naked));
void MemManage_Handler(void)
{
    __asm volatile (
        "   tst   lr, #4          \n"
        "   ite   eq              \n"
        "   mrseq r0, msp         \n"
        "   mrsne r0, psp         \n"
        "   b     MemManage_Handler_C \n"
    );
}

void MemManage_Handler_C(uint32_t *memsfault_args)
{
    (void)memsfault_args;
    for (;;) { __asm volatile ("nop"); }
}

void BusFault_Handler(void) __attribute__((naked));
void BusFault_Handler(void)
{
    __asm volatile (
        "   tst   lr, #4          \n"
        "   ite   eq              \n"
        "   mrseq r0, msp         \n"
        "   mrsne r0, psp         \n"
        "   b     BusFault_Handler_C \n"
    );
}

void BusFault_Handler_C(uint32_t *busfault_args)
{
    (void)busfault_args;
    for (;;) { __asm volatile ("nop"); }
}

void UsageFault_Handler(void) __attribute__((naked));
void UsageFault_Handler(void)
{
    __asm volatile (
        "   tst   lr, #4          \n"
        "   ite   eq              \n"
        "   mrseq r0, msp         \n"
        "   mrsne r0, psp         \n"
        "   b     UsageFault_Handler_C \n"
    );
}

void UsageFault_Handler_C(uint32_t *usgfault_args)
{
    (void)usgfault_args;
    for (;;) { __asm volatile ("nop"); }
}
