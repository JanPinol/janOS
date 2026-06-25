#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "isr.h"
#include "keyboard.h"
#include "pic.h"
#include "pit.h"
#include "stdio.h"
#include "tty.h"

void kernel_main(void)
{
    tty_initialize();

    kputs("janOS kernel initialized");

    gdt_initialize();
    idt_initialize();
    isr_initialize();

    pic_remap();
    irq_initialize();
    pit_initialize(100);
    keyboard_initialize();

    kputs("Kernel setup complete");

    __asm__ volatile ("sti");

    for (;;) {
        __asm__ volatile ("hlt");
    }
}
