#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

/*
 * Reports an unrecoverable error and halts the CPU.
 *
 * Disables interrupts, prints the formatted message and never returns.
 * Accepts the same format specifiers as kprintf.
 */
__attribute__((noreturn))
void kpanic(const char *format, ...);

#endif
