# =============================================================================
#  nautilus — Top-level Makefile
#  STM32F4-Discovery firmware with FreeRTOS
#
#  Select the target board and MCU at build time:
#    make BOARD=stm32f4_discovery MCU=stm32f4
# =============================================================================

# ---- Toolchain --------------------------------------------------------------
CROSS_COMPILE ?= arm-none-eabi-
CC            := $(CROSS_COMPILE)gcc
AS            := $(CROSS_COMPILE)gcc -x assembler-with-cpp
LD            := $(CROSS_COMPILE)gcc
OBJCOPY       := $(CROSS_COMPILE)objcopy
SIZE          := $(CROSS_COMPILE)size
OPENOCD       := openocd

# ---- Target selection -------------------------------------------------------
BOARD ?= stm32f4_discovery
MCU   ?= stm32f4

# ---- MCU / CPU settings -----------------------------------------------------
CPU_MAP_stm32f4 := cortex-m4
FPU_MAP_stm32f4 := fpv4-sp-d16

CPU      := $(CPU_MAP_$(MCU))
FPU      := $(FPU_MAP_$(MCU))
FLOAT_ABI:= hard
CPU_FREQ_MHZ := 168

# ---- Directories ------------------------------------------------------------
ROOT        := $(CURDIR)
COMMON_INC  := $(ROOT)/common/inc
COMMON_SRC  := $(ROOT)/common/src
MCU_ROOT    := $(ROOT)/common/mcu
MCU_STARTUP := $(MCU_ROOT)/$(MCU)/startup
MCU_SYSTEM  := $(MCU_ROOT)/$(MCU)/system
MCU_LD      := $(MCU_ROOT)/$(MCU)/ld
BOARD_SRC   := $(ROOT)/common/boards
RTOS_INC    := $(ROOT)/rtos/freertos
RTOS_SRC    := $(ROOT)/rtos/freertos/src
RTOS_PORT   := $(ROOT)/rtos/freertos/port
BUILD_DIR   := $(ROOT)/build/$(BOARD)

# ---- FreeRTOS kernel sources (portable part) --------------------------------
FREERTOS_ROOT := $(RTOS_INC)/FreeRTOS/Source
FREERTOS_PORT := $(FREERTOS_ROOT)/portable/GCC/ARM_CM4

# ---- Source files -----------------------------------------------------------
C_SRCS := \
  $(COMMON_SRC)/led.c \
  $(COMMON_SRC)/uart.c \
  $(COMMON_SRC)/utils.c \
  $(wildcard $(MCU_ROOT)/$(MCU)/*.c) \
  $(BOARD_SRC)/board_$(BOARD).c \
  $(RTOS_SRC)/tasks.c \
  $(MCU_SYSTEM)/system_stm32f4xx.c \
  $(MCU_SYSTEM)/stm32f4xx_it.c \
  $(FREERTOS_ROOT)/tasks.c \
  $(FREERTOS_ROOT)/queue.c \
  $(FREERTOS_ROOT)/list.c \
  $(FREERTOS_ROOT)/timers.c \
  $(FREERTOS_ROOT)/event_groups.c \
  $(FREERTOS_ROOT)/stream_buffer.c \
  $(FREERTOS_PORT)/port.c

ASM_SRCS := \
  $(MCU_STARTUP)/stm32f4xx_startup.s

# ---- Object files -----------------------------------------------------------
C_OBJS   := $(patsubst $(ROOT)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))
ASM_OBJS := $(patsubst $(ROOT)/%.s,$(BUILD_DIR)/%.o,$(ASM_SRCS))
OBJS     := $(C_OBJS) $(ASM_OBJS)

# ---- Output -----------------------------------------------------------------
ELF       := $(BUILD_DIR)/firmware.elf
BIN       := $(BUILD_DIR)/firmware.bin
HEX       := $(BUILD_DIR)/firmware.hex

# ---- Compiler flags ---------------------------------------------------------
CPU_FLAGS := -mcpu=$(CPU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT_ABI)

CFLAGS := \
  $(CPU_FLAGS) \
  -O2 \
  -g3 \
  -Wall \
  -Wextra \
  -Werror \
  -ffunction-sections \
  -fdata-sections \
  -fno-common \
  -I$(COMMON_INC) \
  -I$(MCU_ROOT) \
  -I$(MCU_ROOT)/$(MCU) \
  -I$(MCU_SYSTEM) \
  -I$(MCU_STARTUP) \
  -I$(BOARD_SRC) \
  -I$(RTOS_INC) \
  -I$(FREERTOS_ROOT)/include \
  -I$(FREERTOS_PORT) \
  -DBOARD_$(BOARD) \
  -DMCU_$(MCU) \
  -DUSE_HAL_DRIVER \
  -DSTM32F407xx

ASFLAGS := $(CPU_FLAGS) -c -g -x assembler-with-cpp

LDFLAGS := \
  $(CPU_FLAGS) \
  -T $(MCU_LD)/$(MCU).ld \
  -nostartfiles \
  -Wl,--gc-sections \
  -Wl,-Map=$(BUILD_DIR)/firmware.map \
  -specs=nano.specs \
  -specs=nosys.specs

# ---- Phony targets ----------------------------------------------------------
.PHONY: all clean flash size help

# ---- Default target ---------------------------------------------------------
all: $(ELF) $(BIN) $(HEX)
	@$(SIZE) $(ELF)

# ---- Linking ---------------------------------------------------------------
$(ELF): $(OBJS) | $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -lm
	@echo "  LD     $@"

$(BIN): $(ELF) | $(BUILD_DIR)
	$(OBJCOPY) -O binary $< $@
	@echo "  BIN    $@"

$(HEX): $(ELF) | $(BUILD_DIR)
	$(OBJCOPY) -O ihex $< $@
	@echo "  HEX    $@"

# ---- Compilation -----------------------------------------------------------
$(BUILD_DIR)/%.o: $(ROOT)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "  CC     $<"

$(BUILD_DIR)/%.o: $(ROOT)/%.s | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<
	@echo "  AS     $<"

# ---- Flash ----------------------------------------------------------------
flash: $(ELF)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f4x.cfg \
		-c "program $< verify reset exit"

# ---- Size ------------------------------------------------------------------
size: $(ELF)
	$(SIZE) $<

# ---- Clean -----------------------------------------------------------------
clean:
	rm -rf build

# ---- Help ------------------------------------------------------------------
help:
	@echo "Targets:"
	@echo "  all    — Build firmware (default)"
	@echo "  flash  — Flash to STM32F4-Discovery via OpenOCD"
	@echo "  size   — Print memory usage"
	@echo "  clean  — Remove build artefacts"
	@echo ""
	@echo "Variables:"
	@echo "  BOARD=stm32f4_discovery   — Select target board (default)"
	@echo "  MCU=stm32f4               — Select MCU family (default)"
	@echo "  CROSS_COMPILE=            — Override toolchain prefix"
