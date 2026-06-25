#include <arch/pic.h>
#include <arch/io.h>

#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21
#define PIC1_OFFSET     0x20

#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1
#define PIC2_OFFSET     0x28

#define PIC_EOI         0x20

#define ICW1_INIT       0x10
#define ICW1_ICW4       0x01
#define ICW4_8086       0x01

#define PIC_CASCADE_IRQ 2

void pic_remap(void)
{
    uint8_t pic1_mask;
    uint8_t pic2_mask;

    pic1_mask = inb(PIC1_DATA);
    pic2_mask = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, PIC1_OFFSET);
    io_wait();

    outb(PIC2_DATA, PIC2_OFFSET);
    io_wait();

    outb(PIC1_DATA, 1 << PIC_CASCADE_IRQ);
    io_wait();

    outb(PIC2_DATA, PIC_CASCADE_IRQ);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();

    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, pic1_mask);

    outb(PIC2_DATA, pic2_mask);
}

void pic_send_eoi(uint8_t irq)
{
    if (irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
    }

    outb(PIC1_COMMAND, PIC_EOI);
}

void pic_disable(void)
{
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}
