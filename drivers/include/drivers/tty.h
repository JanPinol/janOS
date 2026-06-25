#ifndef DRIVERS_TTY_H
#define DRIVERS_TTY_H

#include <stddef.h>

#include <drivers/vga.h>

/*
 * Initializes the terminal state and clears the screen.
 */
void tty_initialize(void);

/*
 * Sets the current terminal color.
 */
void tty_set_color(enum vga_color foreground, enum vga_color background);

/*
 * Writes one character at the current cursor position.
 */
void tty_putchar(char character);

/*
 * Writes exactly size characters from data.
 *
 * The buffer does not need to be null-terminated.
 */
void tty_write(const char *data, size_t size);

/*
 * Writes a null-terminated string.
 */
void tty_writestring(const char *data);

#endif
