#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define KERNEL_CODE_SELECTOR 0x08
#define IDT_INTERRUPT_GATE 0x8E

/*
 * Initializes the Interrupt Descriptor Table.
 */
void idt_initialize(void);

/*
 * Sets an IDT entry.
 */
void idt_set_entry(uint8_t index, uint32_t handler, uint16_t selector,
                   uint8_t type_attributes);

#endif
