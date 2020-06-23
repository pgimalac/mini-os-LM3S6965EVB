MEMORY
{
        flash (rx) : ORIGIN = 0x00000000, LENGTH = 256k
        ram  (!rx) : ORIGIN = 0x20000000, LENGTH = 64k
}

ENTRY(_start)

SECTIONS
{
    .vect_table :
    {
        _irq_table = . ;
        irq/irq.o(*vectors*)
    } >flash

    .text :
    {
        crt0.o(.text)
        *(.text)
    } >flash

    .rodata :
    {
        *(.rodata*);
    } >flash

    .data :
    {
        *(.data);
    } >ram AT>flash

    .bss :
    {
    _bstart = . ;
        *(.bss) *(*COM*);
    _bend = . ;
    } >ram
}

_stack = ORIGIN(ram) + LENGTH(ram);
_data_lma = LOADADDR(.data);
_data_lma_end = LOADADDR(.data) + SIZEOF(.data);
_data_vma = ADDR(.data);
