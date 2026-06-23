#ifndef STDLIB_H
#define STDLIB_H

/*
 * Returns the absolute value of an integer.
 */
int abs(int n);

/*
 * Converts a string to an integer.
 */
int atoi(const char* str);

/*
 * Converts an unsigned integer to a string.
 *
 * Supports bases from 2 to 16.
 */
char* utoa(unsigned int value, char* buffer, int base);

/*
 * Converts a signed integer to a string.
 *
 * Supports bases from 2 to 16.
 */
char* itoa(int value, char* buffer, int base);

#endif
