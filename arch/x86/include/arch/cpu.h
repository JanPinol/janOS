#ifndef ARCH_CPU_H
#define ARCH_CPU_H

#include <stdint.h>

/*
 * Thin wrappers around common x86 CPU control instructions.
 *
 * These are static inline so they compile down to the bare instruction
 * with no call overhead.
 */

static inline void cpu_halt(void)
{
    __asm__ volatile ("hlt");
}

static inline void cpu_enable_interrupts(void)
{
    __asm__ volatile ("sti" ::: "memory");
}

static inline void cpu_disable_interrupts(void)
{
    __asm__ volatile ("cli" ::: "memory");
}

/*
 * Saves the current interrupt flag and disables interrupts. Pair with
 * cpu_restore_irq() to form a critical section that nests safely.
 */
static inline uint32_t cpu_save_irq(void)
{
    uint32_t flags;

    __asm__ volatile ("pushf\n\t"
                      "pop %0\n\t"
                      "cli"
                      : "=r"(flags)
                      :
                      : "memory");
    return flags;
}

/*
 * Restores the interrupt flag captured by cpu_save_irq().
 */
static inline void cpu_restore_irq(uint32_t flags)
{
    __asm__ volatile ("push %0\n\t"
                      "popf"
                      :
                      : "r"(flags)
                      : "memory", "cc");
}

#endif
