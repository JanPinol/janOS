#include "tty.h"
#include "stdio.h"

void kernel_main(void)
{
    tty_initialize();

    kputs("janOS kernel initialized");

    kprintf("char: %c\n", 'A');
    kprintf("string: %s\n", "janOS");
    kprintf("signed: %d\n", -42);
    kprintf("unsigned: %u\n", 42);
    kprintf("hex: 0x%x\n", 0x2a);
    kprintf("percent: %%\n");

    while (1) {}
}
