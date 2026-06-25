#ifndef KEYBOARD_H
#define KEYBOARD_H

/*
 * Initializes the keyboard driver.
 */
void keyboard_initialize(void);

/*
 * Handles one keyboard interrupt.
 */
void keyboard_handle_irq(void);

#endif
