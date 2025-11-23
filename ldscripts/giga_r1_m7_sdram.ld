/* Custom linker script for Giga R1 M7 to put LVGL assets into SDRAM */

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2M
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 1M
  SDRAM (xrw) : ORIGIN = 0xD0000000, LENGTH = 8M
}

/* Standard sections */
SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)    /* read-only data */
        *(.glue_7)
        *(.glue_7t)
    } > FLASH

    .data : AT (ADDR(.text) + SIZEOF(.text))
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM

    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    /* External SDRAM section for large fonts/images */
    .sdram (NOLOAD) :
    {
        . = ALIGN(4);
        *(.sdram*)
        *(.rodata.sdram*)
        . = ALIGN(4);
    } > SDRAM

    /DISCARD/ : { *(.note*) *(.comment*) }
}
