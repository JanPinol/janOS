#include <kernel/shell.h>
#include <drivers/pit.h>
#include <drivers/tty.h>
#include <stdio.h>
#include <string.h>

#include <stddef.h>

#define SHELL_BUFFER_SIZE   128
#define SHELL_COMMAND_COUNT (sizeof(shell_commands) / sizeof(shell_commands[0]))
#define SHELL_HELP_COLUMN   8

/*
 * Handler for a shell command. Receives the argument string, which is
 * whatever followed the command name (empty if there was none).
 */
typedef void (*shell_handler_t)(const char *args);

struct shell_command {
    const char *name;
    shell_handler_t handler;
    const char *help;
};

static void cmd_help(const char *args);
static void cmd_clear(const char *args);
static void cmd_uptime(const char *args);
static void cmd_echo(const char *args);

static char shell_buffer[SHELL_BUFFER_SIZE];
static size_t shell_buffer_length;

/*
 * Command registry. Adding a command means adding one row here.
 */
static const struct shell_command shell_commands[] = {
    { "help",   cmd_help,   "Show this help message" },
    { "clear",  cmd_clear,  "Clear the screen" },
    { "uptime", cmd_uptime, "Show system uptime" },
    { "echo",   cmd_echo,   "Print text" },
};

static void cmd_help(const char *args)
{
    (void)args;

    kputs("Available commands:");

    for (size_t i = 0; i < SHELL_COMMAND_COUNT; i++) {
        size_t name_length = strlen(shell_commands[i].name);

        kprintf("  %s", shell_commands[i].name);

        for (size_t pad = name_length; pad < SHELL_HELP_COLUMN; pad++) {
            kputchar(' ');
        }

        kputs(shell_commands[i].help);
    }
}

static void cmd_clear(const char *args)
{
    (void)args;

    tty_initialize();
}

static void cmd_uptime(const char *args)
{
    (void)args;

    kprintf("Uptime: %u seconds\n", pit_get_ticks() / 100);
}

static void cmd_echo(const char *args)
{
    kputs(args);
}

static void shell_print_prompt(void)
{
    kprintf("janOS> ");
}

static void shell_clear_buffer(void)
{
    shell_buffer_length = 0;
    shell_buffer[0] = '\0';
}

/*
 * Splits the input line into a command name and its argument string, then
 * runs the matching command from the registry.
 */
static void shell_dispatch(void)
{
    char *args = shell_buffer;

    if (shell_buffer_length == 0) {
        return;
    }

    while (*args != '\0' && *args != ' ') {
        args++;
    }

    if (*args == ' ') {
        *args = '\0';
        args++;
    }

    for (size_t i = 0; i < SHELL_COMMAND_COUNT; i++) {
        if (strcmp(shell_buffer, shell_commands[i].name) == 0) {
            shell_commands[i].handler(args);
            return;
        }
    }

    kprintf("Unknown command: %s\n", shell_buffer);
}

static void shell_execute_command(void)
{
    shell_buffer[shell_buffer_length] = '\0';

    shell_dispatch();

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
