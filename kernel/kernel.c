#include <arch/cpu.h>
#include <arch/gdt.h>
#include <arch/idt.h>
#include <arch/irq.h>
#include <arch/isr.h>
#include <arch/pic.h>
#include <drivers/keyboard.h>
#include <drivers/pit.h>
#include <drivers/tty.h>
#include <kernel/panic.h>
#include <kernel/shell.h>
#include <stdio.h>

#include <stdint.h>

#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

void kernel_main(uint32_t magic, uint32_t multiboot_info_addr)
{
    /* TODO: parse the Multiboot memory map for the physical allocator. */
    (void)multiboot_info_addr;

    tty_initialize();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kpanic("Invalid Multiboot magic: 0x%x", magic);
    }

    gdt_initialize();
    idt_initialize();
    isr_initialize();

    pic_remap();
    irq_initialize();
    pit_initialize(100);
    keyboard_initialize();
    shell_initialize();

    cpu_enable_interrupts();

    for (;;) {
        while (keyboard_has_char()) {
            shell_handle_char(keyboard_get_char());
        }

        cpu_halt();
    }
}
