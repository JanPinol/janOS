#include "idt.h"
#include "stdio.h"
#include "string.h"

#define IDT_ENTRIES 256

struct idt_entry {
    uint16_t offset_1;          // offset bits 0..15
    uint16_t selector;          // a code segment selector in GDT or LDT
    uint8_t zero;               // unused
    uint8_t type_attributes;    // gate type, dpl, and p fields
    uint16_t offset_2;          // offset bits 16..31
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr idt_descriptor;

extern void idt_load(uint32_t idt_ptr_address);

void idt_set_entry(uint8_t index, uint32_t handler, uint16_t selector,
                          uint8_t type_attributes)
{
    idt[index].offset_1 = (uint16_t) (handler & 0xFFFF);
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].type_attributes = type_attributes;
    idt[index].offset_2 = (uint16_t) ((handler >> 16) & 0xFFFF);
}

void idt_initialize(void)
{
    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (uint32_t) &idt;

    memset(idt, 0, sizeof(idt));

    idt_load((uint32_t) &idt_descriptor);

    kputs("IDT initialized");
}
