#include <drivers/vga.h>
#include <arch/io.h>

/*
 * VGA CRT controller ports and cursor registers.
 */
#define VGA_CRTC_INDEX              0x3D4
#define VGA_CRTC_DATA               0x3D5
#define VGA_CURSOR_START            0x0A
#define VGA_CURSOR_END              0x0B
#define VGA_CURSOR_LOCATION_HIGH    0x0E
#define VGA_CURSOR_LOCATION_LOW     0x0F

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

void vga_enable_cursor(uint8_t start, uint8_t end)
{
    outb(VGA_CRTC_INDEX, VGA_CURSOR_START);
    outb(VGA_CRTC_DATA, (inb(VGA_CRTC_DATA) & 0xC0) | start);

    outb(VGA_CRTC_INDEX, VGA_CURSOR_END);
    outb(VGA_CRTC_DATA, (inb(VGA_CRTC_DATA) & 0xE0) | end);
}

void vga_set_cursor(size_t row, size_t col)
{
    const uint16_t position = (uint16_t)((row * VGA_WIDTH) + col);

    outb(VGA_CRTC_INDEX, VGA_CURSOR_LOCATION_LOW);
    outb(VGA_CRTC_DATA, (uint8_t)(position & 0xFF));

    outb(VGA_CRTC_INDEX, VGA_CURSOR_LOCATION_HIGH);
    outb(VGA_CRTC_DATA, (uint8_t)((position >> 8) & 0xFF));
}
