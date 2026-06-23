#include "string.h"

size_t strlen(const char* str)
{
    size_t i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}

void* memset(void* dest, int value, size_t count)
{
    unsigned char* ptr = dest;

    for (size_t i = 0; i < count; i++) {
        ptr[i] = (unsigned char) value;
    }

    return dest;
}

void* memcpy(void* dest, const void* src, size_t count)
{
    unsigned char* d_ptr = dest;
    const unsigned char* s_ptr = src;

    for (size_t i = 0; i < count; i++) {
        d_ptr[i] = s_ptr[i];
    }

    return dest;
}

void* memmove(void* dest, const void* src, size_t count)
{
    unsigned char* d_ptr = dest;
    const unsigned char* s_ptr = src;

    if (d_ptr == s_ptr || count == 0) {
        return dest;
    }

    if (d_ptr < s_ptr) {
        for (size_t i = 0; i < count; i++) {
            d_ptr[i] = s_ptr[i];
        }
    } else {
        for (size_t i = count; i > 0; i--) {
            d_ptr[i - 1] = s_ptr[i - 1];
        }
    }

    return dest;
}

int memcmp(const void* a, const void* b, size_t count)
{
    const unsigned char* a_ptr = a;
    const unsigned char* b_ptr = b;

    for (size_t i = 0; i < count; i++) {
        if (a_ptr[i] > b_ptr[i]) {
            return 1;
        }

        if (a_ptr[i] < b_ptr[i]) {
            return -1;
        }
    }

    return 0;
}

int strcmp(const char* a, const char* b)
{
    size_t i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        unsigned char ca = (unsigned char) a[i];
        unsigned char cb = (unsigned char) b[i];

        if (ca > cb) {
            return 1;
        }

        if (ca < cb) {
            return -1;
        }

        i++;
    }

    if (a[i] == b[i]) {
        return 0;
    }

    if ((unsigned char) a[i] > (unsigned char) b[i]) {
        return 1;
    }

    return -1;
}

int strncmp(const char* a, const char* b, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        unsigned char ca = (unsigned char) a[i];
        unsigned char cb = (unsigned char) b[i];

        if (ca != cb) {
            return ca - cb;
        }

        if (ca == '\0') {
            return 0;
        }
    }

    return 0;
}

char* strcpy(char* dest, const char* src)
{
    size_t i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';

    return dest;
}

char* strncpy(char* dest, const char* src, size_t count)
{
    size_t i = 0;

    while (i < count && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < count) {
        dest[i] = '\0';
        i++;
    }

    return dest;
}
