#ifndef _VGA_H_
#define _VGA_H_

#include <stddef.h>
#include <stdint.h>

/*
 * VGA text mode constants.
 *
 * The VGA text buffer starts at physical address 0xB8000.
 * Each screen cell is 16 bits:
 *
 *   bits 0..7   = ASCII character
 *   bits 8..15  = color attribute
 */
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

/*
 * VGA 4-bit color values.
 */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_GRAY = 7,
    VGA_COLOR_DARK_GRAY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15,
};

/*
 * Build a VGA color attribute from foreground and background colors.
 */
uint8_t vga_color(enum vga_color foreground, enum vga_color background);

/*
 * Build a 16-bit VGA text entry from a character and color attribute.
 */
uint16_t vga_entry(uint8_t character, uint8_t color);

/*
 * Write a VGA entry at the given text-mode position.
 */
void vga_putentry_at(uint16_t entry, size_t row, size_t col);

/*
 * Get a VGA entry at the given text-mode position.
 */
uint16_t vga_getentry_at(size_t row, size_t col);

#endif
