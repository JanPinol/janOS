#ifndef SHELL_H
#define SHELL_H

/*
 * Initializes the kernel shell.
 */
void shell_initialize(void);

/*
 * Handles one input character.
 */
void shell_handle_char(char character);

#endif
