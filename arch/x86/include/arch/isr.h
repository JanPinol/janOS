#ifndef ARCH_ISR_H
#define ARCH_ISR_H

#include <stdint.h>

/*
 * CPU state captured by the ISR/IRQ stubs, from the bottom of the stack up.
 * The field order MUST match how the stubs build the frame:
 *
 *   - ds                          pushed by the common stub
 *   - edi..eax                    pushed by `pusha` (edi lowest, eax highest)
 *   - interrupt_number, error_code  pushed by the per-vector stub / CPU
 *   - eip, cs, eflags             pushed by the CPU on the exception
 *
 * (useresp/ss are only pushed on a privilege change, which does not happen
 * while the kernel runs entirely in ring 0.)
 */
struct interrupt_frame {
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t interrupt_number;
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

_Static_assert(sizeof(struct interrupt_frame) == 56,
               "interrupt_frame layout must match the ISR/IRQ stubs");

/*
 * Installs CPU exception handlers into the IDT.
 */
void isr_initialize(void);

/*
 * Handles CPU exceptions from ISR stubs.
 */
void isr_handler(struct interrupt_frame *frame);

#endif
