/**
 * @file  stm32f4xx_it.c
 * @brief Interrupt Service Routines for STM32F4-Discovery.
 *
 * The Cortex-M4 NVIC routes all interrupts to the handlers declared in
 * the vector table (startup/stm32f4xx_startup.s).  This file provides
 * the C-level implementations for the fault handlers and any
 * peripheral IRQs that need application-level attention.
 */

#include "stm32f4xx_it.h"

/* ------------------------------------------------------------------ */
/*  Cortex-M4 fault handlers — defined in port.c (naked asm wrappers) */
/* ------------------------------------------------------------------ */

extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

/* ------------------------------------------------------------------ */
/*  Peripheral IRQ handlers — weak defaults (no-op)                    */
/* ------------------------------------------------------------------ */

void WWDG_IRQHandler(void)              { while (1); }
void PVD_IRQHandler(void)               { while (1); }
void TAMP_STAMP_IRQHandler(void)        { while (1); }
void RTC_WKUP_IRQHandler(void)          { while (1); }
void RCC_IRQHandler(void)               { while (1); }
void EXTI0_IRQHandler(void)             { while (1); }
void EXTI1_IRQHandler(void)             { while (1); }
void EXTI2_IRQHandler(void)             { while (1); }
void EXTI3_IRQHandler(void)             { while (1); }
void EXTI4_IRQHandler(void)             { while (1); }
void DMA1_Stream0_IRQHandler(void)      { while (1); }
void DMA1_Stream1_IRQHandler(void)      { while (1); }
void DMA1_Stream2_IRQHandler(void)      { while (1); }
void DMA1_Stream3_IRQHandler(void)      { while (1); }
void DMA1_Stream4_IRQHandler(void)      { while (1); }
void DMA1_Stream5_IRQHandler(void)      { while (1); }
void DMA1_Stream6_IRQHandler(void)      { while (1); }
void ADC_IRQHandler(void)               { while (1); }
void EXTI9_5_IRQHandler(void)           { while (1); }
void TIM1_BRK_TIM9_IRQHandler(void)     { while (1); }
void TIM1_UP_TIM10_IRQHandler(void)     { while (1); }
void TIM1_TRG_COM_TIM11_IRQHandler(void){ while (1); }
void TIM1_CC_IRQHandler(void)           { while (1); }
void TIM2_IRQHandler(void)              { while (1); }
void TIM3_IRQHandler(void)              { while (1); }
void TIM4_IRQHandler(void)              { while (1); }
void I2C1_EV_IRQHandler(void)           { while (1); }
void I2C1_ER_IRQHandler(void)           { while (1); }
void I2C2_EV_IRQHandler(void)           { while (1); }
void I2C2_ER_IRQHandler(void)           { while (1); }
void SPI1_IRQHandler(void)              { while (1); }
void SPI2_IRQHandler(void)              { while (1); }
void USART1_IRQHandler(void)            { while (1); }
void USART2_IRQHandler(void)            { while (1); }
void USART3_IRQHandler(void)            { while (1); }
void EXTI15_10_IRQHandler(void)         { while (1); }
void RTC_Alarm_IRQHandler(void)         { while (1); }
void OTG_FS_WKUP_IRQHandler(void)       { while (1); }
void DMA1_Stream7_IRQHandler(void)      { while (1); }
void SDIO_IRQHandler(void)              { while (1); }
void TIM5_IRQHandler(void)              { while (1); }
void SPI3_IRQHandler(void)              { while (1); }
void DMA2_Stream0_IRQHandler(void)      { while (1); }
void DMA2_Stream1_IRQHandler(void)      { while (1); }
void DMA2_Stream2_IRQHandler(void)      { while (1); }
void DMA2_Stream3_IRQHandler(void)      { while (1); }
void DMA2_Stream4_IRQHandler(void)      { while (1); }
void OTG_FS_IRQHandler(void)            { while (1); }
void DMA2_Stream5_IRQHandler(void)      { while (1); }
void DMA2_Stream6_IRQHandler(void)      { while (1); }
void DMA2_Stream7_IRQHandler(void)      { while (1); }
void USART6_IRQHandler(void)            { while (1); }
void I2C3_EV_IRQHandler(void)           { while (1); }
void I2C3_ER_IRQHandler(void)           { while (1); }
void FPU_IRQHandler(void)               { while (1); }
