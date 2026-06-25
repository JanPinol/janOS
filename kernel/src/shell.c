#include "shell.h"
#include "pit.h"
#include "stdio.h"
#include "string.h"
#include "tty.h"

#include <stddef.h>

#define SHELL_BUFFER_SIZE   128

static char shell_buffer[SHELL_BUFFER_SIZE];
static size_t shell_buffer_length;

static void shell_print_prompt(void)
{
    kprintf("janOS> ");
}

static void shell_clear_buffer(void)
{
    shell_buffer_length = 0;
    shell_buffer[0] = '\0';
}

static void shell_execute_command(void)
{
    shell_buffer[shell_buffer_length] = '\0';

    if (strcmp(shell_buffer, "help") == 0) {
        kputs("Available commands:");
        kputs("  help    Show this help message");
        kputs("  clear   Clear the screen");
        kputs("  uptime  Show system uptime");
        kputs("  echo    Print text");
    } else if (strcmp(shell_buffer, "clear") == 0) {
        tty_initialize();
    } else if (strcmp(shell_buffer, "uptime") == 0) {
        kprintf("Uptime: %u seconds\n", pit_get_ticks() / 100);
    } else if (strncmp(shell_buffer, "echo ", 5) == 0) {
        kputs(shell_buffer + 5);
    } else if (shell_buffer_length == 0) {
        /*
         * Empty command.
         */
    } else {
        kprintf("Unknown command: %s\n", shell_buffer);
    }

    shell_clear_buffer();
    shell_print_prompt();
}

void shell_initialize(void)
{
    shell_clear_buffer();
    shell_print_prompt();
}

void shell_handle_char(char character)
{
    if (character == '\n') {
        tty_putchar('\n');
        shell_execute_command();
        return;
    }

    if (character == '\b') {
        if (shell_buffer_length > 0) {
            shell_buffer_length--;
            shell_buffer[shell_buffer_length] = '\0';
            tty_putchar('\b');
        }

        return;
    }

    if (shell_buffer_length >= SHELL_BUFFER_SIZE - 1) {
        return;
    }

    shell_buffer[shell_buffer_length] = character;
    shell_buffer_length++;

    tty_putchar(character);
}
