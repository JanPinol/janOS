#ifndef IRQ_H
#define IRQ_H

#include "isr.h"

/*
 * Installs hardware IRQ handlers into the IDT.
 */
void irq_initialize(void);

/*
 * Handles hardware interrupts from IRQ stubs.
 */
void irq_handler(struct interrupt_frame *frame);

#endif
