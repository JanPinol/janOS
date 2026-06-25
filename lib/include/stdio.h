#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

/*
 * Writes a single character to the kernel output.
 */
int kputchar(int c);

/*
 * Writes a string followed by a newline to the kernel output.
 */
int kputs(const char *str);

/*
 * Writes formatted text to the kernel output.
 *
 * Supported formats: %c, %s, %d, %u, %x, %p, %%.
 */
int kprintf(const char *format, ...);

/*
 * Like kprintf, but takes an already-started va_list.
 */
int kvprintf(const char *format, va_list args);

#endif
