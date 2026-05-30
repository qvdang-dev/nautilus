# Architecture

## Directory Layout

```
nautilus/
├── README.md
├── Makefile
├── .gitignore
├── common/
│   ├── mcu/                          # MCU abstraction layer
│   │   ├── mcu.h                     # mcu_t vtable (portable interface)
│   │   └── stm32f4/                  # STM32F4-specific files
│   │       ├── mcu_stm32f4.c         # MCU vtable (ties implementations together)
│   │       ├── mcu_stm32f4_regs.h     # STM32F4 register definitions
│   │       ├── mcu_stm32f4_gpio.c    # GPIO implementation
│   │       ├── mcu_stm32f4_uart.c    # UART implementation
│   │       ├── mcu_stm32f4_system.c  # System (delay, clock) implementation
│   │       ├── ld/
│   │       │   └── stm32f4.ld        # STM32F4 linker script
│   │       ├── startup/
│   │       │   └── stm32f4xx_startup.s
│   │       └── system/
│   │           ├── stm32f4xx_hal_conf.h
│   │           ├── stm32f4xx_it.c
│   │           └── system_stm32f4xx.c
│   ├── boards/                       # Board abstraction layer
│   │   ├── boards.h
│   │   └── board_stm32f4_discovery.c
│   ├── inc/                          # Driver headers
│   │   ├── led.h
│   │   ├── uart.h
│   │   └── utils.h
│   └── src/                          # Driver implementations
│       ├── led.c
│       ├── uart.c
│       └── utils.c
├── rtos/
│   └── freertos/
│       ├── FreeRTOSConfig.h
│       ├── port/
│       │   └── port.c
│       └── src/
│           └── tasks.c
└── docs/
    ├── architecture.md
    ├── build-guide.md
    ├── rtos-comparison.md
    └── FILE_INDEX.md
```

## System Overview

`nautilus` uses a three-layer hardware abstraction so that the same
application code runs on any supported board and MCU without changes.

```
┌──────────────────────────────────────────────────────────────────┐
│  rtos/freertos/src/tasks.c   (demo application — board-agnostic) │
├──────────────────────────────────────────────────────────────────┤
│  common/src/                 (led, uart, utils — MCU-agnostic)   │
├──────────────────────────────────────────────────────────────────┤
│  common/boards/              (board_t — maps board → MCU pins)   │
│  common/mcu/                 (mcu_t   — maps MCU → registers)    │
│    └── <mcu>/                (MCU-specific: impl, startup, ld)   │
├──────────────────────────────────────────────────────────────────┤
│  rtos/freertos/port/port.c   (Cortex-M4 port layer)              │
│  FreeRTOS kernel (portable)                                       │
└──────────────────────────────────────────────────────────────────┘
```

## Layer Responsibilities

| Layer | Directory | Responsibility | Extend by… |
|---|---|---|---|
| **Application** | `rtos/freertos/src/` | Demo tasks; uses `common/` drivers only | Write new task files |
| **Drivers** | `common/src/` | LED, UART, delay — no register knowledge | Write new driver files |
| **Board** | `common/boards/` | Maps board peripherals to MCU GPIO ports/pins | Add a `board_*.c` file |
| **MCU** | `common/mcu/<mcu>/` | MCU register implementation, startup, linker script | Add a new `<mcu>` subdirectory |
| **Kernel** | `rtos/freertos/` | FreeRTOS scheduler, IPC, timers | — |

## MCU Implementation Structure

Each MCU family has its own subdirectory under `common/mcu/<mcu>/` with:

| File | Purpose |
|---|---|
| `mcu_<mcu>.c` | MCU vtable — ties all implementations together |
| `mcu_<mcu>_impl.h` | Implementation function declarations |
| `mcu_<mcu>_regs.h` | Register definitions (internal header) |
| `mcu_<mcu>_gpio.c` | GPIO implementation |
| `mcu_<mcu>_uart.c` | UART implementation |
| `mcu_<mcu>_system.c` | System functions (delay, clock) |
| `ld/<mcu>.ld` | Linker script |
| `startup/` | Vector table and reset handler |
| `system/` | Clock init, IRQ handlers, HAL config |

## Adding a New Board (same MCU family)

To support a new board on an existing MCU (e.g. a custom STM32F4 board):

1. **Create `common/boards/board_<name>.c`**
   Populate a `board_t` struct with the board's LED GPIO ports/pins,
   button descriptors, and UART instances.

2. **Build** with `make BOARD=<name> MCU=stm32f4`.

No changes to drivers, MCU code, or the RTOS layer are needed.

## Adding a New MCU

To support a new MCU family (e.g. STM32F1 Blue Pill):

1. **Create `common/mcu/<mcu>/` — a new MCU subdirectory containing:**
   - `mcu_<mcu>.c` — the `mcu_t` vtable (ties implementations together)
   - `mcu_<mcu>_regs.h` — register definitions
   - `mcu_<mcu>_gpio.c` — GPIO implementation
   - `mcu_<mcu>_uart.c` — UART implementation
   - `mcu_<mcu>_system.c` — system functions
   - `ld/<mcu>.ld` — linker script
   - `startup/` — vector table and reset handler
   - `system/` — clock init, IRQ handlers, HAL config

2. **Create `common/boards/board_<name>.c`**
   Populate a `board_t` struct mapping the board's peripherals to the
   new MCU's GPIO ports and pins.

3. **Build** with `make BOARD=<name> MCU=<mcu>`.

No changes to `common/src/led.c`, `common/src/uart.c`, or
`rtos/freertos/src/tasks.c` are needed.

## Memory Map (STM32F407VG)

| Region | Start | End | Purpose |
|---|---|---|---|
| Flash | `0x0800_0000` | `0x080F_FFFF` | Firmware image (1 MB) |
| SRAM | `0x2000_0000` | `0x2001_FFFF` | .data, .bss, heap, stacks (128 KB) |
| CCM SRAM | `0x1000_0000` | `0x1000_7FFF` | Core-Coupled Memory (32 KB) |

## FreeRTOS Heap

The kernel heap is defined in `FreeRTOSConfig.h` via `configTOTAL_HEAP_SIZE`.
The default is left to the application; a typical value for this project is
`(20 * 1024)` (20 KB).

## Thread Model

| Task | Priority | Stack (words) | Notes |
|---|---|---|---|
| LED Blink | 1 (Low) | 128 | `vTaskDelay()` periodic |
| UART Console | 2 (Low-Med) | 256 | Protected by `xUartMutex` |
| Button Handler | 3 (Med) | 128 | GPIO polling + debounce |
| IPC Sender | 2 | 128 | Queue → IPC Receiver |
| IPC Receiver | 2 | 128 | Queue ← IPC Sender |
| Timer Service | 2 | 256 | FreeRTOS software timers |