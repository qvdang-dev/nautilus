/**
 * @file  stm32f4xx_startup.s
 * @brief Cortex-M4 vector table and reset handler for STM32F407VG.
 *
 * The vector table maps all interrupt and exception vectors to their
 * respective C handlers.  The Reset_Handler initialises .data and .bss
 * then calls main().
 */

    .syntax unified
    .cpu    cortex-m4
    .fpu    fpv4-sp-d16
    .thumb

    .section .isr_vector, "a", %progbits
    .word   _estack                        /* MSP initial value          */
    .word   Reset_Handler                  /* Reset                      */
    .word   NMI_Handler                    /* NMI                        */
    .word   HardFault_Handler              /* HardFault                  */
    .word   MemManage_Handler              /* MemManage                  */
    .word   BusFault_Handler               /* BusFault                   */
    .word   UsageFault_Handler             /* UsageFault                 */
    .word   0                              /* Reserved                   */
    .word   0                              /* Reserved                   */
    .word   0                              /* Reserved                   */
    .word   0                              /* Reserved                   */
    .word   SVC_Handler                    /* SVCall                      */
    .word   DebugMon_Handler               /* DebugMonitor               */
    .word   0                              /* Reserved                   */
    .word   PendSV_Handler                 /* PendSV                     */
    .word   SysTick_Handler                /* SysTick                    */

    /* External interrupts (IRQ 0 … 95) */
    .word   WWDG_IRQHandler                /*  0: Window Watchdog        */
    .word   PVD_IRQHandler                 /*  1: PVD through EXTI       */
    .word   TAMP_STAMP_IRQHandler          /*  2: Tamper / Timestamp     */
    .word   RTC_WKUP_IRQHandler            /*  3: RTC Wakeup            */
    .word   0                              /*  4: Reserved               */
    .word   RCC_IRQHandler                 /*  5: RCC                    */
    .word   EXTI0_IRQHandler               /*  6: EXTI Line 0            */
    .word   EXTI1_IRQHandler               /*  7: EXTI Line 1            */
    .word   EXTI2_IRQHandler               /*  8: EXTI Line 2            */
    .word   EXTI3_IRQHandler               /*  9: EXTI Line 3            */
    .word   EXTI4_IRQHandler               /* 10: EXTI Line 4            */
    .word   DMA1_Stream0_IRQHandler        /* 11: DMA1 Stream 0          */
    .word   DMA1_Stream1_IRQHandler        /* 12: DMA1 Stream 1          */
    .word   DMA1_Stream2_IRQHandler        /* 13: DMA1 Stream 2          */
    .word   DMA1_Stream3_IRQHandler        /* 14: DMA1 Stream 3          */
    .word   DMA1_Stream4_IRQHandler        /* 15: DMA1 Stream 4          */
    .word   DMA1_Stream5_IRQHandler        /* 16: DMA1 Stream 5          */
    .word   DMA1_Stream6_IRQHandler        /* 17: DMA1 Stream 6          */
    .word   ADC_IRQHandler                 /* 18: ADC1, ADC2, ADC3       */
    .word   0                              /* 19: Reserved               */
    .word   0                              /* 20: Reserved               */
    .word   0                              /* 21: Reserved               */
    .word   0                              /* 22: Reserved               */
    .word   EXTI9_5_IRQHandler             /* 23: EXTI Line[9:5]         */
    .word   TIM1_BRK_TIM9_IRQHandler       /* 24: TIM1 Break / TIM9      */
    .word   TIM1_UP_TIM10_IRQHandler       /* 25: TIM1 Update / TIM10    */
    .word   TIM1_TRG_COM_TIM11_IRQHandler  /* 26: TIM1 Trig/Comm / TIM11 */
    .word   TIM1_CC_IRQHandler             /* 27: TIM1 Capture Compare   */
    .word   TIM2_IRQHandler                /* 28: TIM2                   */
    .word   TIM3_IRQHandler                /* 29: TIM3                   */
    .word   TIM4_IRQHandler                /* 30: TIM4                   */
    .word   I2C1_EV_IRQHandler             /* 31: I2C1 Event             */
    .word   I2C1_ER_IRQHandler             /* 32: I2C1 Error             */
    .word   I2C2_EV_IRQHandler             /* 33: I2C2 Event             */
    .word   I2C2_ER_IRQHandler             /* 34: I2C2 Error             */
    .word   SPI1_IRQHandler                /* 35: SPI1                   */
    .word   SPI2_IRQHandler                /* 36: SPI2                   */
    .word   USART1_IRQHandler              /* 37: USART1                 */
    .word   USART2_IRQHandler              /* 38: USART2                 */
    .word   USART3_IRQHandler              /* 39: USART3                 */
    .word   EXTI15_10_IRQHandler           /* 40: EXTI Line[15:10]       */
    .word   RTC_Alarm_IRQHandler           /* 41: RTC Alarm              */
    .word   OTG_FS_WKUP_IRQHandler         /* 42: USB FS Wakeup          */
    .word   0                              /* 43: Reserved               */
    .word   0                              /* 44: Reserved               */
    .word   0                              /* 45: Reserved               */
    .word   0                              /* 46: Reserved               */
    .word   DMA1_Stream7_IRQHandler        /* 47: DMA1 Stream 7          */
    .word   0                              /* 48: Reserved               */
    .word   SDIO_IRQHandler                /* 49: SDIO                   */
    .word   TIM5_IRQHandler                /* 50: TIM5                   */
    .word   SPI3_IRQHandler                /* 51: SPI3                   */
    .word   0                              /* 52: Reserved               */
    .word   0                              /* 53: Reserved               */
    .word   0                              /* 54: Reserved               */
    .word   0                              /* 55: Reserved               */
    .word   DMA2_Stream0_IRQHandler        /* 56: DMA2 Stream 0          */
    .word   DMA2_Stream1_IRQHandler        /* 57: DMA2 Stream 1          */
    .word   DMA2_Stream2_IRQHandler        /* 58: DMA2 Stream 2          */
    .word   DMA2_Stream3_IRQHandler        /* 59: DMA2 Stream 3          */
    .word   DMA2_Stream4_IRQHandler        /* 60: DMA2 Stream 4          */
    .word   0                              /* 61: Reserved               */
    .word   0                              /* 62: Reserved               */
    .word   0                              /* 63: Reserved               */
    .word   0                              /* 64: Reserved               */
    .word   0                              /* 65: Reserved               */
    .word   0                              /* 66: Reserved               */
    .word   OTG_FS_IRQHandler              /* 67: USB FS                 */
    .word   DMA2_Stream5_IRQHandler        /* 68: DMA2 Stream 5          */
    .word   DMA2_Stream6_IRQHandler        /* 69: DMA2 Stream 6          */
    .word   DMA2_Stream7_IRQHandler        /* 70: DMA2 Stream 7          */
    .word   USART6_IRQHandler              /* 71: USART6                 */
    .word   I2C3_EV_IRQHandler             /* 72: I2C3 Event             */
    .word   I2C3_ER_IRQHandler             /* 73: I2C3 Error             */
    .word   0                              /* 74: Reserved               */
    .word   0                              /* 75: Reserved               */
    .word   0                              /* 76: Reserved               */
    .word   0                              /* 77: Reserved               */
    .word   0                              /* 78: Reserved               */
    .word   0                              /* 79: Reserved               */
    .word   FPU_IRQHandler                 /* 81: FPU                    */
    .word   0                              /* 82: Reserved               */
    .word   0                              /* 83: Reserved               */
    .word   0                              /* 84: Reserved               */
    .word   0                              /* 85: Reserved               */
    .word   0                              /* 86: Reserved               */
    .word   0                              /* 87: Reserved               */
    .word   0                              /* 88: Reserved               */
    .word   0                              /* 89: Reserved               */
    .word   0                              /* 90: Reserved               */
    .word   0                              /* 91: Reserved               */
    .word   0                              /* 92: Reserved               */
    .word   0                              /* 93: Reserved               */
    .word   0                              /* 94: Reserved               */
    .word   0                              /* 95: Reserved               */

    .size   __isr_vector, . - __isr_vector

/* ------------------------------------------------------------------ */
/*  Reset handler                                                      */
/* ------------------------------------------------------------------ */

    .section .text.Reset_Handler, "ax", %progbits
    .type   Reset_Handler, %function
Reset_Handler:
    /* Copy .data section from flash to SRAM */
    ldr   r0, =_sdata
    ldr   r1, =_edata
    ldr   r2, =_sidata
copy_data:
    cmp   r0, r1
    ittt  lo
    ldrlo r3, [r2], #4
    strlo r3, [r0], #4
    blo   copy_data

    /* Zero .bss section */
    ldr   r1, =_sbss
    ldr   r2, =_ebss
zero_bss:
    cmp   r1, r2
    ittt  lo
    movlo r3, #0
    strlo r3, [r1], #4
    blo   zero_bss

    /* Call main() — never returns */
    bl    main

hang:
    b     hang

    .size   Reset_Handler, . - Reset_Handler

/* ------------------------------------------------------------------ */
/*  Default weak interrupt handlers                                    */
/* ------------------------------------------------------------------ */

    .section .text.Default_Handler, "ax", %progbits
    .weak  WWDG_IRQHandler
    .thumb_set WWDG_IRQHandler, Default_Handler
    .weak  PVD_IRQHandler
    .thumb_set PVD_IRQHandler, Default_Handler
    .weak  TAMP_STAMP_IRQHandler
    .thumb_set TAMP_STAMP_IRQHandler, Default_Handler
    .weak  RTC_WKUP_IRQHandler
    .thumb_set RTC_WKUP_IRQHandler, Default_Handler
    .weak  RCC_IRQHandler
    .thumb_set RCC_IRQHandler, Default_Handler
    .weak  EXTI0_IRQHandler
    .thumb_set EXTI0_IRQHandler, Default_Handler
    .weak  EXTI1_IRQHandler
    .thumb_set EXTI1_IRQHandler, Default_Handler
    .weak  EXTI2_IRQHandler
    .thumb_set EXTI2_IRQHandler, Default_Handler
    .weak  EXTI3_IRQHandler
    .thumb_set EXTI3_IRQHandler, Default_Handler
    .weak  EXTI4_IRQHandler
    .thumb_set EXTI4_IRQHandler, Default_Handler
    .weak  DMA1_Stream0_IRQHandler
    .thumb_set DMA1_Stream0_IRQHandler, Default_Handler
    .weak  DMA1_Stream1_IRQHandler
    .thumb_set DMA1_Stream1_IRQHandler, Default_Handler
    .weak  DMA1_Stream2_IRQHandler
    .thumb_set DMA1_Stream2_IRQHandler, Default_Handler
    .weak  DMA1_Stream3_IRQHandler
    .thumb_set DMA1_Stream3_IRQHandler, Default_Handler
    .weak  DMA1_Stream4_IRQHandler
    .thumb_set DMA1_Stream4_IRQHandler, Default_Handler
    .weak  DMA1_Stream5_IRQHandler
    .thumb_set DMA1_Stream5_IRQHandler, Default_Handler
    .weak  DMA1_Stream6_IRQHandler
    .thumb_set DMA1_Stream6_IRQHandler, Default_Handler
    .weak  ADC_IRQHandler
    .thumb_set ADC_IRQHandler, Default_Handler
    .weak  EXTI9_5_IRQHandler
    .thumb_set EXTI9_5_IRQHandler, Default_Handler
    .weak  TIM1_BRK_TIM9_IRQHandler
    .thumb_set TIM1_BRK_TIM9_IRQHandler, Default_Handler
    .weak  TIM1_UP_TIM10_IRQHandler
    .thumb_set TIM1_UP_TIM10_IRQHandler, Default_Handler
    .weak  TIM1_TRG_COM_TIM11_IRQHandler
    .thumb_set TIM1_TRG_COM_TIM11_IRQHandler, Default_Handler
    .weak  TIM1_CC_IRQHandler
    .thumb_set TIM1_CC_IRQHandler, Default_Handler
    .weak  TIM2_IRQHandler
    .thumb_set TIM2_IRQHandler, Default_Handler
    .weak  TIM3_IRQHandler
    .thumb_set TIM3_IRQHandler, Default_Handler
    .weak  TIM4_IRQHandler
    .thumb_set TIM4_IRQHandler, Default_Handler
    .weak  I2C1_EV_IRQHandler
    .thumb_set I2C1_EV_IRQHandler, Default_Handler
    .weak  I2C1_ER_IRQHandler
    .thumb_set I2C1_ER_IRQHandler, Default_Handler
    .weak  I2C2_EV_IRQHandler
    .thumb_set I2C2_EV_IRQHandler, Default_Handler
    .weak  I2C2_ER_IRQHandler
    .thumb_set I2C2_ER_IRQHandler, Default_Handler
    .weak  SPI1_IRQHandler
    .thumb_set SPI1_IRQHandler, Default_Handler
    .weak  SPI2_IRQHandler
    .thumb_set SPI2_IRQHandler, Default_Handler
    .weak  USART1_IRQHandler
    .thumb_set USART1_IRQHandler, Default_Handler
    .weak  USART2_IRQHandler
    .thumb_set USART2_IRQHandler, Default_Handler
    .weak  USART3_IRQHandler
    .thumb_set USART3_IRQHandler, Default_Handler
    .weak  EXTI15_10_IRQHandler
    .thumb_set EXTI15_10_IRQHandler, Default_Handler
    .weak  RTC_Alarm_IRQHandler
    .thumb_set RTC_Alarm_IRQHandler, Default_Handler
    .weak  OTG_FS_WKUP_IRQHandler
    .thumb_set OTG_FS_WKUP_IRQHandler, Default_Handler
    .weak  DMA1_Stream7_IRQHandler
    .thumb_set DMA1_Stream7_IRQHandler, Default_Handler
    .weak  SDIO_IRQHandler
    .thumb_set SDIO_IRQHandler, Default_Handler
    .weak  TIM5_IRQHandler
    .thumb_set TIM5_IRQHandler, Default_Handler
    .weak  SPI3_IRQHandler
    .thumb_set SPI3_IRQHandler, Default_Handler
    .weak  DMA2_Stream0_IRQHandler
    .thumb_set DMA2_Stream0_IRQHandler, Default_Handler
    .weak  DMA2_Stream1_IRQHandler
    .thumb_set DMA2_Stream1_IRQHandler, Default_Handler
    .weak  DMA2_Stream2_IRQHandler
    .thumb_set DMA2_Stream2_IRQHandler, Default_Handler
    .weak  DMA2_Stream3_IRQHandler
    .thumb_set DMA2_Stream3_IRQHandler, Default_Handler
    .weak  DMA2_Stream4_IRQHandler
    .thumb_set DMA2_Stream4_IRQHandler, Default_Handler
    .weak  OTG_FS_IRQHandler
    .thumb_set OTG_FS_IRQHandler, Default_Handler
    .weak  DMA2_Stream5_IRQHandler
    .thumb_set DMA2_Stream5_IRQHandler, Default_Handler
    .weak  DMA2_Stream6_IRQHandler
    .thumb_set DMA2_Stream6_IRQHandler, Default_Handler
    .weak  DMA2_Stream7_IRQHandler
    .thumb_set DMA2_Stream7_IRQHandler, Default_Handler
    .weak  USART6_IRQHandler
    .thumb_set USART6_IRQHandler, Default_Handler
    .weak  I2C3_EV_IRQHandler
    .thumb_set I2C3_EV_IRQHandler, Default_Handler
    .weak  I2C3_ER_IRQHandler
    .thumb_set I2C3_ER_IRQHandler, Default_Handler
    .weak  FPU_IRQHandler
    .thumb_set FPU_IRQHandler, Default_Handler

Default_Handler:
    b .

    .size   Default_Handler, . - Default_Handler
