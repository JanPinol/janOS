#ifndef STDLIB_H
#define STDLIB_H

/*
 * Minimum buffer size, in bytes, that always fits an itoa/utoa result.
 * The worst case is a 32-bit value in base 2: 32 digits, an optional sign,
 * and the null terminator.
 */
#define ITOA_BUFFER_SIZE 34

/*
 * Returns the absolute value of an integer.
 */
int abs(int n);

/*
 * Converts a string to an integer.
 */
int atoi(const char *str);

/*
 * Converts an unsigned integer to a string.
 *
 * Supports bases from 2 to 16. The buffer must hold at least
 * ITOA_BUFFER_SIZE bytes to be safe for every base.
 */
char *utoa(unsigned int value, char *buffer, int base);

/*
 * Converts a signed integer to a string.
 *
 * Supports bases from 2 to 16. The buffer must hold at least
 * ITOA_BUFFER_SIZE bytes to be safe for every base.
 */
char *itoa(int value, char *buffer, int base);

#endif
