#ifndef ARCH_PIC_H
#define ARCH_PIC_H

#include <stdint.h>

/*
 * Remaps the PIC IRQs away from CPU exception vectors.
 */
void pic_remap(void);

/*
 * Sends an end-of-interrupt signal for an IRQ.
 */
void pic_send_eoi(uint8_t irq);

/*
 * Masks all PIC IRQ lines.
 */
void pic_disable(void);

#endif
