/* =============================================================================
 *  stm32f407xx.ld — Linker script for STM32F407VG (STM32F4-Discovery)
 *
 *  Memory map:
 *    Flash : 0x0800_0000 – 0x080F_FFFF  (1 MB)
 *    SRAM  : 0x2000_0000 – 0x2001_FFFF  (128 KB)
 *    CCM   : 0x1000_0000 – 0x1000_7FFF  ( 32 KB)
 * ============================================================================= */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
  CCM   (xrw) : ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS
{
  /* ------------------------------------------------------------------ */
  /*  Vector table + interrupt handlers (placed at start of Flash)       */
  /* ------------------------------------------------------------------ */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > FLASH

  /* ------------------------------------------------------------------ */
  /*  Read-only data (constants, strings, FreeRTOS kernel code)          */
  /* ------------------------------------------------------------------ */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP(*(.init))
    KEEP(*(.fini))

    . = ALIGN(4);
    _etext = .;
  } > FLASH

  /* ------------------------------------------------------------------ */
  /*  Pre-initialised data (copy from Flash to SRAM at startup)          */
  /* ------------------------------------------------------------------ */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH

  /* ------------------------------------------------------------------ */
  /*  .data section — initialised RAM variables                          */
  /* ------------------------------------------------------------------ */
  .data : AT (ADDR(.rodata) + SIZEOF(.rodata))
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM

  /* ------------------------------------------------------------------ */
  /*  .bss section — zero-initialised RAM variables                      */
  /* ------------------------------------------------------------------ */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  /* ------------------------------------------------------------------ */
  /*  FreeRTOS heap — placed at the top of SRAM                          */
  /* ------------------------------------------------------------------ */
  .heap (NOLOAD):
  {
    . = ALIGN(8);
    _sheap = .;
    *(.heap*)
    . = ALIGN(8);
    _eheap = .;
  } > RAM

  /* ------------------------------------------------------------------ */
  /*  Stack — 1 KB main stack (MSP)                                      */
  /* ------------------------------------------------------------------ */
  .stack (NOLOAD):
  {
    . = ALIGN(8);
    _sstack = .;
    . = . + 1024;
    . = ALIGN(8);
    _estack = .;
  } > RAM

  /* Discard everything not specifically referenced above */
  /DISCARD/ :
  {
    *(.ARM.exidx*)
    *(.comment)
    *(.ARM.attributes)
  }
}
