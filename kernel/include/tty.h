#ifndef TTY_H
#define TTY_H

#include <stddef.h>

#include "vga.h"

/*
 * Initialize the terminal state and clear the screen.
 */
void tty_initialize(void);

/*
 * Set the current terminal color.
 */
void tty_set_color(enum vga_color foreground, enum vga_color background);

/*
 * Write one character at the current cursor position.
 */
void tty_putchar(char character);

/*
 * Write exactly size characters from data.
 *
 * The buffer does not need to be null-terminated.
 */
void tty_write(const char* data, size_t size);

/*
 * Write a null-terminated string.
 */
void tty_writestring(const char* data);

#endif
