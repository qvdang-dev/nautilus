# File Index

A complete inventory of every file and directory in the `nautilus` repository.

---

## Root

| Path | Description |
|---|---|
| [`README.md`](README.md) | Project overview, supported RTOS, hardware, build instructions |
| [`Makefile`](Makefile) | Top-level build system — `make`, `make flash`, `make clean`; supports `BOARD=` and `MCU=` selection |
| [`.gitignore`](.gitignore) | Git ignore rules for build artefacts, IDE files, OS junk |

---

## [`common/`](common/) — Hardware abstraction & shared drivers

### [`common/mcu/`](common/mcu/) — MCU abstraction layer

All MCU-specific files are grouped under a per-MCU subdirectory
(`common/mcu/<mcu>/`).  The portable `mcu_t` vtable header lives at
`common/mcu/mcu.h`.

| Path | Description |
|---|---|
| [`common/mcu.h`](common/mcu.h) | `mcu_t` vtable definition: `gpio_mode/write/read/toggle`, `uart_init/putc/puts/getc`, `delay_ms`, `get_sysclk`; `mcu_get()` accessor |
| [`common/mcu/stm32f4/mcu_stm32f4.c`](common/mcu/stm32f4/mcu_stm32f4.c) | STM32F4 vtable — ties GPIO, UART, system implementations together |
| [`common/mcu/stm32f4/mcu_stm32f4_impl.h`](common/mcu/stm32f4/mcu_stm32f4_impl.h) | STM32F4 implementation function declarations |
| [`common/mcu/stm32f4/mcu_stm32f4_regs.h`](common/mcu/stm32f4/mcu_stm32f4_regs.h) | STM32F4 register definitions (internal header) |
| [`common/mcu/stm32f4/mcu_stm32f4_gpio.c`](common/mcu/stm32f4/mcu_stm32f4_gpio.c) | STM32F4 GPIO implementation |
| [`common/mcu/stm32f4/mcu_stm32f4_uart.c`](common/mcu/stm32f4/mcu_stm32f4_uart.c) | STM32F4 UART implementation |
| [`common/mcu/stm32f4/mcu_stm32f4_system.c`](common/mcu/stm32f4/mcu_stm32f4_system.c) | STM32F4 system functions (delay, clock) |
| [`common/mcu/stm32f4/ld/stm32f4.ld`](common/mcu/stm32f4/ld/stm32f4.ld) | GNU LD linker script for STM32F407VG (Flash 1 MB, SRAM 128 KB) |
| [`common/mcu/stm32f4/startup/stm32f4xx_startup.s`](common/mcu/stm32f4/startup/stm32f4xx_startup.s) | Vector table (96 IRQs + 16 exceptions), Reset handler, weak defaults |
| [`common/mcu/stm32f4/system/system_stm32f4xx.c`](common/mcu/stm32f4/system/system_stm32f4xx.c) | PLL clock init → 168 MHz, FPU enable, `SystemCoreClock` |
| [`common/mcu/stm32f4/system/stm32f4xx_it.c`](common/mcu/stm32f4/system/stm32f4xx_it.c) | C-level IRQ handler stubs (all peripheral IRQs) |
| [`common/mcu/stm32f4/system/stm32f4xx_hal_conf.h`](common/mcu/stm32f4/system/stm32f4xx_hal_conf.h) | HAL driver config — GPIO, RCC, UART |

### [`common/boards/`](common/boards/) — Board abstraction layer

| Path | Description |
|---|---|
| [`common/boards.h`](common/boards.h) | `board_t`, `board_led_t`, `board_btn_t`, `board_uart_t` structs; `board_get()` accessor |
| [`common/boards/board_stm32f4_discovery.c`](common/boards/board_stm32f4_discovery.c) | STM32F4-Discovery: 4 LEDs (PG13/PG14/PA0/PA1), 1 button (PA0), 1 UART (USART2) |

### [`common/inc/`](common/inc/) — Driver headers

| Path | Description |
|---|---|
| [`common/inc/led.h`](common/inc/led.h) | Board-agnostic LED API: `led_init()`, `led_on/off/toggle(name)` |
| [`common/inc/uart.h`](common/inc/uart.h) | Board-agnostic UART API: `uart_init()`, `uart_putc/puts/getc()` |
| [`common/inc/utils.h`](common/inc/utils.h) | `delay_ms()`, `clz32()` — delegates timing to `mcu_t` |

### [`common/src/`](common/src/) — Driver implementations

| Path | Description |
|---|---|
| [`common/src/led.c`](common/src/led.c) | Iterates `board_t.leds[]`, calls `mcu_t.gpio_*` — no register knowledge |
| [`common/src/uart.c`](common/src/uart.c) | Finds `"UART_CONSOLE"` in `board_t.uarts[]`, calls `mcu_t.uart_*` |
| [`common/src/utils.c`](common/src/utils.c) | Delegates `delay_ms()` to `mcu_t.delay_ms()` |

---

## [`rtos/freertos/`](rtos/freertos/) — FreeRTOS port

| Path | Description |
|---|---|
| [`rtos/freertos/FreeRTOSConfig.h`](rtos/freertos/FreeRTOSConfig.h) | Kernel config: preemptive, 7 priorities, FPU, mutexes, queues, timers, static allocation |
| [`rtos/freertos/port/port.c`](rtos/freertos/port/port.c) | Cortex-M4 port: PendSV context-switch, SysTick tick, SVC, fault handlers |
| [`rtos/freertos/src/tasks.c`](rtos/freertos/src/tasks.c) | Five demo tasks: LED Blink, UART Console, Button Handler, IPC Sender, IPC Receiver |

---

## [`docs/`](docs/) — Documentation

| Path | Description |
|---|---|
| [`docs/architecture.md`](docs/architecture.md) | Layered architecture, "add a board / add an MCU" guides, memory map, thread model |
| [`docs/build-guide.md`](docs/build-guide.md) | Prerequisites, build/flash/debug commands, serial console |
| [`docs/rtos-comparison.md`](docs/rtos-comparison.md) | FreeRTOS feature matrix, memory footprint, future RTOS roadmap |
| [`docs/FILE_INDEX.md`](docs/FILE_INDEX.md) | This file — complete inventory |

---

## Directory tree (condensed)

```
nautilus/
├── README.md
├── Makefile
├── .gitignore
├── common/
│   ├── mcu/
│   │   ├── mcu.h
│   │   └── stm32f4/
│   │       ├── mcu_stm32f4.c
│   │       ├── mcu_stm32f4_impl.h
│   │       ├── mcu_stm32f4_regs.h
│   │       ├── mcu_stm32f4_gpio.c
│   │       ├── mcu_stm32f4_uart.c
│   │       ├── mcu_stm32f4_system.c
│   │       ├── ld/
│   │       │   └── stm32f4.ld
│   │       ├── startup/
│   │       │   └── stm32f4xx_startup.s
│   │       └── system/
│   │           ├── stm32f4xx_hal_conf.h
│   │           ├── stm32f4xx_it.c
│   │           └── system_stm32f4xx.c
│   ├── boards/
│   │   ├── boards.h
│   │   └── board_stm32f4_discovery.c
│   ├── inc/
│   │   ├── led.h
│   │   ├── uart.h
│   │   └── utils.h
│   └── src/
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

**Total: 30 files** across 9 directories.