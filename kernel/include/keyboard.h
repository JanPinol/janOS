#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

/*
 * Initializes the keyboard driver.
 */
void keyboard_initialize(void);

/*
 * Handles one keyboard interrupt.
 */
void keyboard_handle_irq(void);

/*
 * Returns true if a character is available.
 */
bool keyboard_has_char(void);

/*
 * Reads one character from the keyboard buffer.
 *
 * Returns 0 if the buffer is empty.
 */
char keyboard_get_char(void);

#endif
