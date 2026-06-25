#include <stdio.h>
#include <drivers/tty.h>
#include <stdlib.h>
#include <string.h>

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

int kputchar(int c)
{
    tty_putchar((char)c);

    return c;
}

int kputs(const char *str)
{
    tty_writestring(str);
    tty_putchar('\n');

    return (int)strlen(str) + 1;
}

int kvprintf(const char *format, va_list args)
{
    int written = 0;
    char buffer[ITOA_BUFFER_SIZE];

    for (size_t i = 0; format[i] != '\0'; i++) {
        if (format[i] != '%') {
            kputchar(format[i]);
            written++;
            continue;
        }

        i++;

        if (format[i] == '\0') {
            kputchar('%');
            written++;
            break;
        }

        switch (format[i]) {
        case 'c': {
            char c = (char)va_arg(args, int);

            kputchar(c);
            written++;
            break;
        }

        case 's': {
            const char *str = va_arg(args, const char *);

            if (str == NULL) {
                str = "(null)";
            }

            tty_writestring(str);
            written += strlen(str);
            break;
        }

        case 'd': {
            int value = va_arg(args, int);

            itoa(value, buffer, 10);
            tty_writestring(buffer);
            written += strlen(buffer);
            break;
        }

        case 'u': {
            unsigned int value = va_arg(args, unsigned int);

            utoa(value, buffer, 10);
            tty_writestring(buffer);
            written += strlen(buffer);
            break;
        }

        case 'x': {
            unsigned int value = va_arg(args, unsigned int);

            utoa(value, buffer, 16);
            tty_writestring(buffer);
            written += strlen(buffer);
            break;
        }

        case 'p': {
            uintptr_t value = (uintptr_t)va_arg(args, void *);

            tty_writestring("0x");
            utoa((unsigned int)value, buffer, 16);
            tty_writestring(buffer);
            written += 2 + (int)strlen(buffer);
            break;
        }

        case '%':
            kputchar('%');
            written++;
            break;

        default:
            kputchar('%');
            kputchar(format[i]);
            written += 2;
            break;
        }
    }

    return written;
}

int kprintf(const char *format, ...)
{
    va_list args;
    int written;

    va_start(args, format);
    written = kvprintf(format, args);
    va_end(args);

    return written;
}
