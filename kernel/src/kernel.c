#include "tty.h"
#include "stdio.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"

void kernel_main(void)
{
    tty_initialize();

    kputs("janOS kernel initialized");

    gdt_initialize();
    idt_initialize();
    isr_initialize();

    kputs("Kernel setup complete");

    __asm__ volatile ("int $0");
}
