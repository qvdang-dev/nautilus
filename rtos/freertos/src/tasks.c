/**
 * @file  tasks.c
 * @brief FreeRTOS demo tasks for the STM32F4-Discovery board.
 *
 * Five concurrent tasks demonstrate the core FreeRTOS primitives:
 *   - LED Blink       — vTaskDelay() periodic wake-up
 *   - UART Console    — Mutex-protected UART output
 *   - Button Handler  — GPIO polling with debounce
 *   - IPC Sender      — Queue send
 *   - IPC Receiver    — Queue receive + LED toggle
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "led.h"
#include "uart.h"
#include "boards.h"
#include "utils.h"

/* ------------------------------------------------------------------ */
/*  Task handles                                                       */
/* ------------------------------------------------------------------ */

static TaskHandle_t xLedTaskHandle    = NULL;
static TaskHandle_t xUartTaskHandle   = NULL;
static TaskHandle_t xButtonTaskHandle = NULL;
static TaskHandle_t xIpcSenderHandle  = NULL;
static TaskHandle_t xIpcReceiverHandle = NULL;

/* ------------------------------------------------------------------ */
/*  IPC objects                                                         */
/* ------------------------------------------------------------------ */

#define IPC_QUEUE_LEN    (5)
#define IPC_ITEM_SIZE    (sizeof(uint32_t))

static QueueHandle_t xIpcQueue = NULL;
static SemaphoreHandle_t xUartMutex = NULL;

/* ------------------------------------------------------------------ */
/*  Task 1 — LED Blink (priority 1)                                    */
/* ------------------------------------------------------------------ */

static void vLedTask(void *pvParameters)
{
    (void)pvParameters;
    const TickType_t xDelay = pdMS_TO_TICKS(1000);

    for (;;) {
        led_toggle("LED_GREEN");
        vTaskDelay(xDelay);
    }
}

/* ------------------------------------------------------------------ */
/*  Task 2 — UART Console (priority 2)                                  */
/* ------------------------------------------------------------------ */

static void vUartTask(void *pvParameters)
{
    (void)pvParameters;
    const TickType_t xDelay = pdMS_TO_TICKS(2000);
    const char *msg = "[nautilus] FreeRTOS running — tick: ";

    for (;;) {
        if (xSemaphoreTake(xUartMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
            uart_puts(msg);
            /* Print tick count as hex */
            {
                char buf[16];
                unsigned long tick = xTaskGetTickCount();
                char *p = buf + sizeof(buf);
                *--p = '\0';
                do { *--p = "0123456789ABCDEF"[tick % 16]; tick /= 16; } while (tick);
                uart_puts(p);
            }
            uart_puts("\r\n");
            xSemaphoreGive(xUartMutex);
        }
        vTaskDelay(xDelay);
    }
}

/* ------------------------------------------------------------------ */
/*  Task 3 — Button Handler (priority 3)                                */
/* ------------------------------------------------------------------ */

static void vButtonTask(void *pvParameters)
{
    (void)pvParameters;
    const TickType_t xDebounce = pdMS_TO_TICKS(50);

    for (;;) {
        /* Active-low button on PA0 */
        if (/* BTN_USER_PORT->IDR & (1U << BTN_USER_PIN) */ 0) {
            led_on("LED_RED");
            vTaskDelay(xDebounce);
            led_off("LED_RED");
            /* Wait for release */
            while (/* (BTN_USER_PORT->IDR & (1U << BTN_USER_PIN)) == 0 */ 0) {
                vTaskDelay(xDebounce);
            }
        }
        vTaskDelay(xDebounce);
    }
}

/* ------------------------------------------------------------------ */
/*  Task 4 — IPC Sender (priority 2)                                    */
/* ------------------------------------------------------------------ */

static void vIpcSenderTask(void *pvParameters)
{
    (void)pvParameters;
    uint32_t counter = 0;
    const TickType_t xDelay = pdMS_TO_TICKS(500);

    for (;;) {
        if (xQueueSend(xIpcQueue, &counter, 0) == pdPASS) {
            counter++;
        }
        vTaskDelay(xDelay);
    }
}

/* ------------------------------------------------------------------ */
/*  Task 5 — IPC Receiver (priority 2)                                  */
/* ------------------------------------------------------------------ */

static void vIpcReceiverTask(void *pvParameters)
{
    (void)pvParameters;
    uint32_t value;

    for (;;) {
        if (xQueueReceive(xIpcQueue, &value, portMAX_DELAY) == pdPASS) {
            if (xSemaphoreTake(xUartMutex, pdMS_TO_TICKS(100)) == pdTRUE) {
                /* Toggle blue LED to signal IPC activity */
                led_toggle("LED_BLUE");
                xSemaphoreGive(xUartMutex);
            }
            (void)value;
        }
    }
}

/* ------------------------------------------------------------------ */
/*  Public API — called from main()                                    */
/* ------------------------------------------------------------------ */

void freertos_demo_init(void)
{
    /* Create IPC objects first */
    xIpcQueue   = xQueueCreate(IPC_QUEUE_LEN, IPC_ITEM_SIZE);
    xUartMutex  = xSemaphoreCreateMutex();

    configASSERT(xIpcQueue  != NULL);
    configASSERT(xUartMutex != NULL);

    /* Create tasks — stack size in words (not bytes) */
    xTaskCreate(vLedTask,    "LED",    128, NULL, 1, &xLedTaskHandle);
    xTaskCreate(vUartTask,   "UART",   256, NULL, 2, &xUartTaskHandle);
    xTaskCreate(vButtonTask, "BTN",    128, NULL, 3, &xButtonTaskHandle);
    xTaskCreate(vIpcSenderTask,  "IPC_S", 128, NULL, 2, &xIpcSenderHandle);
    xTaskCreate(vIpcReceiverTask, "IPC_R", 128, NULL, 2, &xIpcReceiverHandle);

    /* Start the scheduler — never returns */
    vTaskStartScheduler();

    /* Should never reach here */
    for (;;) { __asm volatile ("nop"); }
}
