#ifndef STDIO_H
#define STDIO_H

/*
 * Writes a single character to the kernel output.
 */
int kputchar(int c);

/*
 * Writes a string to the kernel output.
 */
int kputs(const char* str);

/*
 * Writes formatted text to the kernel output.
 *
 * Supported formats: %c, %s, %d, %u, %x, %%
 */
int kprintf(const char* format, ...);

#endif
