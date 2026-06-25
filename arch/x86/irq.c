#include <arch/irq.h>
#include <arch/idt.h>
#include <arch/pic.h>
#include <stdio.h>

#include <stddef.h>
#include <stdint.h>

#define IRQ_COUNT   16
#define IRQ_OFFSET  32

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

static void (*irq_stubs[IRQ_COUNT])(void) = {
    irq0,
    irq1,
    irq2,
    irq3,
    irq4,
    irq5,
    irq6,
    irq7,
    irq8,
    irq9,
    irq10,
    irq11,
    irq12,
    irq13,
    irq14,
    irq15
};

static irq_handler_t irq_handlers[IRQ_COUNT];

void irq_initialize(void)
{
    for (uint8_t i = 0; i < IRQ_COUNT; i++) {
        irq_handlers[i] = NULL;

        idt_set_entry(IRQ_OFFSET + i, (uint32_t)irq_stubs[i],
                      IDT_KERNEL_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    }
}

void irq_install_handler(uint8_t irq, irq_handler_t handler)
{
    if (irq >= IRQ_COUNT) {
        return;
    }

    irq_handlers[irq] = handler;
}

void irq_uninstall_handler(uint8_t irq)
{
    if (irq >= IRQ_COUNT) {
        return;
    }

    irq_handlers[irq] = NULL;
}

void irq_handler(struct interrupt_frame *frame)
{
    uint8_t irq = frame->interrupt_number - IRQ_OFFSET;

    if (irq < IRQ_COUNT && irq_handlers[irq] != NULL) {
        irq_handlers[irq]();
    } else {
        kprintf("Unhandled IRQ: %u\n", irq);
    }

    pic_send_eoi(irq);
}

