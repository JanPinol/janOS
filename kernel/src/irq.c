#include "irq.h"
#include "idt.h"
#include "pic.h"
#include "stdio.h"
#include "pit.h"
#include "keyboard.h"

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

void irq_initialize(void)
{
    for (uint8_t i = 0; i < IRQ_COUNT; i++) {
        idt_set_entry(IRQ_OFFSET + i, (uint32_t) irq_stubs[i],
                      IDT_KERNEL_CODE_SELECTOR, IDT_INTERRUPT_GATE);
    }
}

void irq_handler(struct interrupt_frame *frame)
{
    uint8_t irq = frame->interrupt_number - IRQ_OFFSET;

    if (irq == 0) {
        pit_tick();
    } else if (irq == 1) {
        keyboard_handle_irq();
    } else {
        kprintf("IRQ received: %u\n", irq);
    }

    pic_send_eoi(irq);
}

void irq_enable()
{
    __asm__ volatile ("sti");
}

void irq_disable()
{
    __asm__ volatile ("cli");
}
