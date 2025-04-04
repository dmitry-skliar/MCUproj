ENTRY(Reset_Handler)

MEMORY
{
    FLASH(RX)  : ORIGIN = 0x08000000, LENGTH = 64k
    SRAM(RWX)  : ORIGIN = 0x20000000, LENGTH = 20k
}

__stack_sram_start = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    __irq_table_flash_start = LOADADDR(.text);
    .text : ALIGN(4)
    {
        KEEP(*(.irq_table))
        KEEP(*(.irq_handlers))
        . = ALIGN(4);
        *(.text .text.*)
    } > FLASH

    .rodata : ALIGN(4)
    {
        *(.rodata .rodata.*)
    } > FLASH

    __data_flash_start = LOADADDR(.data);
    .data : ALIGN(4)
    {
        __data_sram_start = .;
        *(.data .data.*)
        . = ALIGN(4);
        __data_sram_end = .;

    } > SRAM AT> FLASH

    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_sram_start = .;
        *(.bss .bss.*)
        . = ALIGN(4);
        __bss_sram_end = .;
    } > SRAM

    /DISCARD/ :
    {
        *(.ARM.exidx .ARM.exidx.* .ARM.extab.*)
    }
}
