/**
 * @file  FreeRTOSConfig.h
 * @brief FreeRTOS configuration for the STM32F4-Discovery (Cortex-M4).
 *
 * Generated against FreeRTOS Kernel V10.x.
 * Adjust configUSE_IDLE_HOOK / configUSE_TICK_HOOK as needed.
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application-specific definitions.
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
  #include <stdint.h>
  extern uint32_t SystemCoreClock;
#endif

#define configUSE_PREEMPTION                      (1)
#define configUSE_TIME_SLICING                    (1)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION   (1)
#define configUSE_TICKLESS_IDLE                   (0)
#define configTICK_RATE_HZ                       ((TickType_t)1000)
#define configMAX_PRIORITIES                     (7)
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)
#define configMAX_TASK_NAME_LEN                  (16)
#define configUSE_16_BIT_TICKS                   (0)
#define configIDLE_SHOULD_YIELD                  (1)
#define configUSE_MUTEXES                        (1)
#define configUSE_RECURSIVE_MUTEXES              (1)
#define configUSE_COUNTING_SEMAPHORES            (1)
#define configUSE_QUEUE_SETS                     (1)
#define configUSE_TASK_NOTIFICATIONS             (1)
#define configSUPPORT_STATIC_ALLOCATION          (1)

/* Hook function support */
#define configUSE_IDLE_HOOK                      (0)
#define configUSE_TICK_HOOK                      (0)
#define configCHECK_FOR_STACK_OVERFLOW           (2)
#define configUSE_TRACE_FACILITY                 (1)
#define configUSE_STATS_FORMATTING_FUNCTIONS     (1)

/* Co-routine definitions — disabled */
#define configUSE_CO_ROUTINES                    (0)
#define configMAX_CO_ROUTINE_PRIORITIES          (2)

/* Software timer definitions */
#define configUSE_TIMERS                         (1)
#define configTIMER_TASK_PRIORITY                (2)
#define configTIMER_QUEUE_LENGTH                 (10)
#define configTIMER_TASK_STACK_DEPTH             (configMINIMAL_STACK_SIZE * 2)

/* Set the following definitions to 1 to include the API function, or zero
 * to exclude the API function. */
#define INCLUDE_vTaskPrioritySet             (1)
#define INCLUDE_uxTaskPriorityGet            (1)
#define INCLUDE_vTaskDelete                  (1)
#define INCLUDE_vTaskCleanUpResources        (1)
#define INCLUDE_vTaskSuspend                 (1)
#define INCLUDE_vTaskDelayUntil              (1)
#define INCLUDE_vTaskDelay                   (1)
#define INCLUDE_xQueueGetMutexHolder         (1)
#define INCLUDE_xSemaphoreGetMutexHolder     (1)
#define INCLUDE_xTaskGetSchedulerState       (1)
#define INCLUDE_eTaskGetState                (1)

/* Cortex-M specific optimisations */
#define configENABLE_FPU_SUPPORT             (1)
#define configENABLE_MPU                     (0)

/* Interrupt nesting behaviour configuration */
#define configPRIO_BITS                      (__NVIC_PRIO_BITS)  /* 4 on Cortex-M4 */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   0xf
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5
#define configKERNEL_INTERRUPT_PRIORITY   (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* Normal assert() semantics without relying on the provision of an assert.h
 * header file. */
#define configASSERT(x)                      \
    do { if ((x) == 0) { taskDISABLE_INTERRUPTS(); for(;;); } } while (0)

/* The lowest interrupt priority that can be used in a call to a
 * FreeRTOS API function. */
#define configMAX_LOWEST_INTERRUPT_PRIORITY  (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

#endif /* FREERTOS_CONFIG_H */
