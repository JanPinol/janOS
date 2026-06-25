#ifndef ARCH_IRQ_H
#define ARCH_IRQ_H

#include <stdint.h>

#include <arch/isr.h>

/*
 * Callback invoked when a hardware IRQ fires.
 */
typedef void (*irq_handler_t)(void);

/*
 * Installs hardware IRQ handlers into the IDT.
 */
void irq_initialize(void);

/*
 * Registers a handler for a hardware IRQ line.
 *
 * Drivers call this to receive their interrupt instead of the arch layer
 * dispatching to them directly. A second registration on the same line
 * replaces the previous handler.
 */
void irq_install_handler(uint8_t irq, irq_handler_t handler);

/*
 * Removes the handler previously registered for a hardware IRQ line.
 */
void irq_uninstall_handler(uint8_t irq);

/*
 * Handles hardware interrupts from IRQ stubs.
 */
void irq_handler(struct interrupt_frame *frame);

#endif
