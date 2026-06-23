#include "gdt.h"
#include "stdio.h"

#include <stdint.h>

#define GDT_ENTRIES 3

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct gdt_entry gdt[GDT_ENTRIES];
static struct gdt_ptr gdt_descriptor;

extern void gdt_flush(uint32_t gdt_descriptor_address);

static void gdt_set_entry(int index, uint32_t base, uint32_t limit,
                          uint8_t access, uint8_t granularity)
{
    gdt[index].base_low = (uint16_t) (base & 0xFFFF);
    gdt[index].base_middle = (uint8_t) ((base >> 16) & 0xFF);
    gdt[index].base_high = (uint8_t) ((base >> 24) & 0xFF);

    gdt[index].limit_low = (uint16_t) (limit & 0xFFFF);
    gdt[index].granularity = (uint8_t) ((limit >> 16) & 0x0F);
    gdt[index].granularity |= granularity & 0xF0;

    gdt[index].access = access;
}

void gdt_initialize(void) {
    gdt_descriptor.limit = sizeof(gdt) - 1;
    gdt_descriptor.base = (uint32_t) &gdt;

    gdt_set_entry(0, 0, 0, 0, 0);

    /*
    * Kernel code segment:
    * base = 0, limit = 4 GiB, ring 0, executable and readable.
    */
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xC0);

    /*
    * Kernel data segment:
    * base = 0, limit = 4 GiB, ring 0, readable and writable.
    */
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xC0);

    gdt_flush((uint32_t) &gdt_descriptor);

    kputs("GDT initialized");
}
