#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "isr.h"
#include "pic.h"
#include "pit.h"
#include "stdio.h"
#include "tty.h"

void kernel_main(void)
{
    tty_initialize();

    gdt_initialize();
    idt_initialize();
    isr_initialize();

    pic_remap();
    irq_initialize();
    pit_initialize(100);

    kputs("Kernel setup complete");

    __asm__ volatile ("sti");

    for (;;) {
        __asm__ volatile ("hlt");
    }
}
