#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "isr.h"
#include "keyboard.h"
#include "pic.h"
#include "pit.h"
#include "shell.h"
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
    keyboard_initialize();
    shell_initialize();

    irq_enable();

    for (;;) {
        while (keyboard_has_char()) {
            shell_handle_char(keyboard_get_char());
        }

        __asm__ volatile ("hlt");
    }
}
