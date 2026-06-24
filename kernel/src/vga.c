#include "vga.h"

static volatile uint16_t *const vga_buffer = (volatile uint16_t *)VGA_MEMORY;

uint8_t vga_color(enum vga_color foreground, enum vga_color background)
{
    return foreground | (background << 4);
}

uint16_t vga_entry(uint8_t character, uint8_t color)
{
    return character | ((uint16_t)color << 8);
}

void vga_putentry_at(uint16_t entry, size_t row, size_t col)
{
    const size_t index = (row * VGA_WIDTH) + col;

    vga_buffer[index] = entry;
}

uint16_t vga_getentry_at(size_t row, size_t col)
{
    const size_t index = (row * VGA_WIDTH) + col;

    return vga_buffer[index];
}
