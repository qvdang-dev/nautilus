# Build & Flash Guide

## Prerequisites

| Tool | Package (Debian/Ubuntu) | Minimum version |
|---|---|---|
| ARM GCC toolchain | `gcc-arm-none-eabi` | 10.x |
| Make | `build-essential` | 4.x |
| OpenOCD | `openocd` | 0.11.x |
| Python 3 | `python3` | 3.8 |

```bash
sudo apt-get install gcc-arm-none-eabi build-essential openocd python3
```

## Toolchain Setup

Set the `CROSS_COMPILE` environment variable if the toolchain is not in
your `PATH`:

```bash
export CROSS_COMPILE=arm-none-eabi-
```

## Building

```bash
# Build the FreeRTOS demo (default target)
make RTOS=freertos

# Verbose build
make RTOS=freertos V=1

# Clean
make clean
```

## Flashing

The STM32F4-Discovery includes an on-board ST-LINK/V2 debugger.  OpenOCD
is used to flash the firmware via SWD:

```bash
make flash RTOS=freertos
```

This runs:

```
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
        -c "program build/freertos/firmware.elf verify reset exit"
```

## Serial Console

The on-board ST-LINK also exposes a virtual COM port (VCP).  Connect at
115200 baud, 8 data bits, no parity, 1 stop bit:

```bash
# Linux / macOS
screen /dev/ttyACM0 115200

# Or use minicom
minicom -b 115200 -o -D /dev/ttyACM0
```

## Debugging

```bash
# Start OpenOCD GDB server
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

# In another terminal, connect GDB
arm-none-eabi-gdb build/freertos/firmware.elf
(gdb) target remote localhost:3333
(gdb) monitor reset halt
(gdb) load
(gdb) continue
```

## Project Layout Reference

```
nautilus/
├── Makefile              # Top-level build entry point
├── common/               # Shared drivers (led, uart, utils)
├── rtos/freertos/        # FreeRTOS port + demo tasks
├── startup/              # Vector table + reset handler
├── system/               # Clock init + IRQ handlers
└── docs/                 # This documentation
```
