#ifndef STRING_H
#define STRING_H

#include <stddef.h>

/*
 * Returns the length of a null-terminated string.
 */
size_t strlen(const char *str);

/*
 * Fills a memory region with the given byte value.
 */
void *memset(void *dest, int value, size_t count);

/*
 * Copies bytes from one memory region to another.
 *
 * The source and destination regions must not overlap.
 */
void *memcpy(void *dest, const void *src, size_t count);

/*
 * Copies bytes from one memory region to another.
 *
 * This function is safe for overlapping memory regions.
 */
void *memmove(void *dest, const void *src, size_t count);

/*
 * Compares two memory regions byte by byte.
 *
 * Returns zero if they are equal, a negative value if the first differing byte
 * in a is lower than the one in b, or a positive value otherwise.
 */
int memcmp(const void *a, const void *b, size_t count);

/*
 * Compares two null-terminated strings.
 *
 * Returns zero if they are equal, a negative value if a is lower than b,
 * or a positive value otherwise.
 */
int strcmp(const char *a, const char *b);

/*
 * Compares up to count characters from two strings.
 *
 * Returns zero if they are equal, a negative value if a is lower than b,
 * or a positive value otherwise.
 */
int strncmp(const char *a, const char *b, size_t count);

/*
 * Copies a null-terminated string.
 *
 * The destination buffer must be large enough to hold the source string,
 * including the final null byte.
 */
char *strcpy(char *dest, const char *src);

/*
 * Copies up to count characters from a string.
 *
 * If the source string is shorter than count, the remaining bytes are filled
 * with null bytes.
 */
char *strncpy(char *dest, const char *src, size_t count);

#endif
