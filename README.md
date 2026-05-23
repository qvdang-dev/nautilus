# nautilus

Firmware for the **STM32F4-Discovery** board demonstrating **multi-threaded applications** using [FreeRTOS](https://www.freertos.org/).

---

## Overview

`nautilus` is an embedded firmware project targeting the [STM32F4-Discovery](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) development board (STM32F407VG MCU — ARM Cortex-M4, 168 MHz, 1 MB Flash, 192 KB SRAM). The project showcases how to run **multiple concurrent threads** using FreeRTOS, with a set of demo applications that illustrate common RTOS patterns.

---

## Supported RTOS

| RTOS | License | Scheduler | Status |
|---|---|---|---|
| **FreeRTOS** | MIT | Preemptive / Co-op | ✅ Supported |

Additional RTOS ports are planned for the future.

---

## Hardware

| Feature | Detail |
|---|---|
| **MCU** | STM32F407VG (ARM Cortex-M4, FPU) |
| **Clock** | Up to 168 MHz |
| **Flash** | 1 MB |
| **SRAM** | 192 KB (128 KB + 64 KB) |
| **Peripherals used** | GPIO (LEDs, user button), USART, SysTick timer |

### STM32F4-Discovery On-Board Peripherals

- **Green LED** (PG13) — Heartbeat / status indicator
- **Red LED** (PG14) — Error / warning indicator
- **Orange LED** (PA0) — Thread activity indicator
- **Blue LED** (PA1) — Thread activity indicator
- **User button** (PA0) — Triggers context-switch demo

---

## Project Structure

```
nautilus/
├── README.md               # This file
├── LICENSE                 # Project license
├── Makefile                # Top-level build entry point
├── .gitignore
├── common/                 # Shared code across all RTOS ports
│   ├── inc/                # Common headers
│   │   ├── board.h         # Board-level definitions (LEDs, buttons)
│   │   ├── led.h           # LED driver API
│   │   ├── uart.h          # UART / console driver
│   │   └── utils.h         # Utility macros (delay, etc.)
│   └── src/                # Common source files
│       ├── led.c
│       ├── uart.c
│       └── utils.c
├── rtos/                   # RTOS-specific ports
│   └── freertos/           # FreeRTOS port
│       ├── FreeRTOSConfig.h
│       ├── port/           # Cortex-M4 port layer
│       └── src/            # FreeRTOS demo tasks
├── startup/                # MCU startup code
│   └── stm32f4xx_startup.s
├── system/                 # System-level code
│   ├── stm32f4xx_hal_conf.h
│   ├── stm32f4xx_it.c      # Interrupt handlers
│   └── system_stm32f4xx.c  # Clock configuration
└── docs/                   # Documentation
    ├── architecture.md     # System architecture overview
    ├── rtos-comparison.md  # RTOS feature comparison
    └── build-guide.md      # Build and flash instructions
```

---

## Demo Applications

FreeRTOS ships with the following demo tasks:

| Task | Description | Priority |
|---|---|---|
| **LED Blink** | Toggles the green LED at 1 Hz | Low |
| **UART Console** | Prints a status message over USART every 2 s | Medium |
| **Button Handler** | Responds to the user button press | High |
| **CPU Load Monitor** | Measures and reports CPU utilisation | Low |
| **IPC Demo** | Demonstrates queues / mailboxes between threads | Medium |

---

## Build Requirements

| Tool | Version |
|---|---|
| **ARM GCC Toolchain** | `arm-none-eabi-gcc` ≥ 10.x |
| **Make** | ≥ 4.x |
| **OpenOCD** | ≥ 0.11.x (for flashing / debugging) |
| **Python 3** | ≥ 3.8 (for helper scripts) |

---

## Build & Flash

```bash
# Clone the repository
git clone https://github.com/<org>/nautilus.git
cd nautilus

# Build for a specific RTOS
make RTOS=freertos

# Flash to the STM32F4-Discovery board
make flash RTOS=freertos

# Open a serial console (115200 baud, 8N1)
make console
```

---

## RTOS Comparison

See [`docs/rtos-comparison.md`](docs/rtos-comparison.md) for a detailed feature-by-feature overview of FreeRTOS, including:

- Memory footprint (ROM / RAM)
- Context-switch latency
- Maximum number of threads
- IPC mechanisms (queues, semaphores, mutexes, events)
- Power management support

---

## License

FreeRTOS is released under the [MIT License](https://www.freertos.org/a00114.html).

