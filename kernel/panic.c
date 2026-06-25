#include <kernel/panic.h>
#include <arch/cpu.h>
#include <stdio.h>

#include <stdarg.h>

void kpanic(const char *format, ...)
{
    va_list args;

    cpu_disable_interrupts();

    kprintf("\n*** KERNEL PANIC: ");

    va_start(args, format);
    kvprintf(format, args);
    va_end(args);

    kprintf(" ***\n");

    for (;;) {
        cpu_halt();
    }
}
