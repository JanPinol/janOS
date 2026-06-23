#include "tty.h"
#include "gdt.h"
#include "stdio.h"

void kernel_main(void)
{
    tty_initialize();
    gdt_initialize();

    kputs("janOS kernel initialized");
}
