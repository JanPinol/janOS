ENTRY(_start)

SECTIONS
{
    . = 1M;

    .multiboot  : { *(.multiboot) }         /* Header to make GRUB recognize the kernel */
    .text       : { *(.text*) }             /* Here will be the code */
    .rodata     : { *(.rodata*) }           /* Constant variables */
    .data       : { *(.data*) }             /* Initialized variables */
    .bss        : { *(.bss*) *(COMMON) }    /* Uninitialized variables */
}