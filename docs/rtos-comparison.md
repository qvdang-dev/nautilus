# FreeRTOS Overview

This document summarises the FreeRTOS configuration used in `nautilus`.

## Kernel Features

| Feature | Setting |
|---|---|
| Preemptive scheduling | ✅ Enabled (`configUSE_PREEMPTION = 1`) |
| Time slicing | ✅ Enabled (`configUSE_TIME_SLICING = 1`) |
| Co-operative scheduling | ✅ Available (disable preemption) |
| Tickless idle | ❌ Disabled (`configUSE_TICKLESS_IDLE = 0`) |
| Static allocation | ✅ Enabled (`configSUPPORT_STATIC_ALLOCATION = 1`) |
| FPU support | ✅ Enabled (`configENABLE_FPU_SUPPORT = 1`) |
| MPU support | ❌ Disabled (`configENABLE_MPU = 0`) |

## Synchronisation Primitives

| Primitive | Status |
|---|---|
| Mutexes | ✅ Enabled |
| Recursive mutexes | ✅ Enabled |
| Counting semaphores | ✅ Enabled |
| Binary semaphores | ✅ Enabled (via semphr.h) |
| Queues | ✅ Enabled |
| Queue sets | ✅ Enabled |
| Task notifications | ✅ Enabled |
| Software timers | ✅ Enabled |

## Configuration Summary

| Parameter | Value |
|---|---|
| SysTick frequency | 1 kHz (`configTICK_RATE_HZ = 1000`) |
| Maximum priorities | 7 |
| Minimal stack size | 128 words (512 bytes) |
| Max task name length | 16 chars |
| Tick type width | 32-bit (`configUSE_16_BIT_TICKS = 0`) |
| Stack overflow check | Level 2 (high water mark + assert) |

## Memory Footprint (typical, STM32F4-Discovery)

| Component | Flash | RAM |
|---|---|---|
| FreeRTOS kernel (portable) | ~6 KB | ~1 KB |
| Demo application | ~4 KB | ~3 KB |
| Heap (20 KB) | — | 20 KB |
| **Total** | **~10 KB** | **~24 KB** |

## Future RTOS Ports

The following RTOSes are under consideration for future ports:

- **ThreadX** — Azure RTOS, small footprint, preemptive
- **Zephyr** — Linux Foundation, scalable, modular
- **ChibiOS/RT** — GPL / commercial, mature STM32 support
- **RT-Thread** — Apache 2.0, component-based, POSIX-like API
