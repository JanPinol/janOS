#include "tty.h"

/*
 * Simple VGA-backed terminal state.
 *
 * The cursor is tracked in text cells, not pixels.
 */
static size_t tty_row;
static size_t tty_col;
static uint8_t tty_color;

void tty_initialize(void)
{
    tty_row = 0;
    tty_col = 0;
    tty_color = vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    uint16_t entry = vga_entry(' ', tty_color);

    for (size_t row = 0; row < VGA_HEIGHT; row++) {
        for (size_t col = 0; col < VGA_WIDTH; col++) {
            vga_putentry_at(entry, row, col);
        }
    }
}

void tty_set_color(enum vga_color foreground, enum vga_color background)
{
    tty_color = vga_color(foreground, background);
}

void tty_scroll(void)
{
    uint16_t blank = vga_entry(' ', tty_color);

    for (size_t row = 1; row < VGA_HEIGHT; row++) {
        for (size_t col = 0; col < VGA_WIDTH; col++) {
            uint16_t entry = vga_getentry_at(row, col);
            vga_putentry_at(entry, row - 1, col);
        }
    }

    for (size_t col = 0; col < VGA_WIDTH; col++) {
        vga_putentry_at(blank, VGA_HEIGHT - 1, col);
    }

    tty_col = 0;
    tty_row = VGA_HEIGHT - 1;
}


void tty_putchar(char character)
{
    if (character == '\n') {
        tty_col = 0;
        tty_row++;

        if (tty_row >= VGA_HEIGHT) {
            tty_scroll();
        }

        return;
    }

    uint16_t entry = vga_entry(character, tty_color);

    vga_putentry_at(entry, tty_row, tty_col);

    tty_col++;

    if (tty_col >= VGA_WIDTH) {
        tty_col = 0;
        tty_row++;
    }

    if (tty_row >= VGA_HEIGHT) {
        tty_scroll();
    }
}

void tty_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        tty_putchar(data[i]);
    }
}

void tty_writestring(const char* data)
{
    size_t i = 0;

    while (data[i] != '\0') {
        tty_putchar(data[i]);
        i++;
    }
}
