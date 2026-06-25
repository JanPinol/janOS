#include <stdlib.h>

#include <stddef.h>

int abs(int n)
{
    if (n < 0) {
        return -n;
    }

    return n;
}

int atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    size_t i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\r' || str[i] == '\v' || str[i] == '\f') {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

char *utoa(unsigned int value, char *buffer, int base)
{
    const char digits[] = "0123456789abcdef";
    char temp[32];
    size_t i = 0;
    size_t j = 0;

    if (base < 2 || base > 16) {
        buffer[0] = '\0';
        return buffer;
    }

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }

    while (value > 0) {
        temp[i] = digits[value % base];
        value /= base;
        i++;
    }

    while (i > 0) {
        i--;
        buffer[j] = temp[i];
        j++;
    }

    buffer[j] = '\0';

    return buffer;
}

char *itoa(int value, char *buffer, int base)
{
    if (base < 2 || base > 16) {
        buffer[0] = '\0';
        return buffer;
    }

    if (value < 0 && base == 10) {
        buffer[0] = '-';
        utoa((unsigned int)(-(value + 1)) + 1, buffer + 1, base);
        return buffer;
    }

    utoa((unsigned int)value, buffer, base);

    return buffer;
}
