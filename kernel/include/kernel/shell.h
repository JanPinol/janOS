#ifndef KERNEL_SHELL_H
#define KERNEL_SHELL_H

/*
 * Initializes the kernel shell.
 */
void shell_initialize(void);

/*
 * Handles one input character.
 */
void shell_handle_char(char character);

#endif
