#ifndef ISR_H
#define ISR_H

#include <stdint.h>

struct interrupt_frame {
    uint32_t interrupt_number;
    uint32_t error_code;
} __attribute__((packed));

/*
 * Installs CPU exception handlers into the IDT.
 */
void isr_initialize(void);

/*
 * Handles CPU exceptions from ISR stubs.
 */
void isr_handler(struct interrupt_frame *frame);

#endif
