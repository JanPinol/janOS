ENTRY(_start)

/*
 * Separate loadable segments so each gets the minimal permissions:
 *   text   = read + execute
 *   rodata = read only
 *   data   = read + write (also holds .bss)
 *
 * FLAGS bits: 1 = execute, 2 = write, 4 = read.
 */
PHDRS
{
    text   PT_LOAD FLAGS(5);
    rodata PT_LOAD FLAGS(4);
    data   PT_LOAD FLAGS(6);
}

SECTIONS
{
    . = 1M;

    .multiboot :
    {
        KEEP(*(.multiboot))
    } :text

    .text ALIGN(4K) :
    {
        *(.text.boot)
        *(.text)
        *(.text.*)
    } :text

    .rodata ALIGN(4K) :
    {
        *(.rodata)
        *(.rodata.*)
    } :rodata

    .data ALIGN(4K) :
    {
        *(.data)
        *(.data.*)
    } :data

    .bss ALIGN(4K) :
    {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    } :data
}
