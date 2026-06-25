#include "keyboard.h"
#include "io.h"
#include "tty.h"

#include <stdbool.h>
#include <stddef.h>

#define KEYBOARD_DATA_PORT     0x60

#define KEYBOARD_RELEASED      0x80
#define KEYBOARD_SCANCODE_MASK 0x7F
#define KEYBOARD_E0_PREFIX     0xE0

#define KEY_LEFT_SHIFT         0x2A
#define KEY_RIGHT_SHIFT        0x36
#define KEY_CAPS_LOCK          0x3A
#define KEY_ALT                0x38

#define ASCII_ESCAPE           0x1B

static bool shift_pressed;
static bool caps_lock_enabled;
static bool alt_pressed;
static bool altgr_pressed;
static bool extended_scancode;

/*
 * Spanish keyboard layout, scancode set 1.
 *
 * Unsupported characters are mapped to 0.
 */
static const char keyboard_normal_map[128] = {
    [0x01] = ASCII_ESCAPE,

    [0x02] = '1',
    [0x03] = '2',
    [0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',
    [0x07] = '6',
    [0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',
    [0x0B] = '0',
    [0x0C] = '\'',
    [0x0D] = 0,
    [0x0E] = '\b',

    [0x0F] = '\t',
    [0x10] = 'q',
    [0x11] = 'w',
    [0x12] = 'e',
    [0x13] = 'r',
    [0x14] = 't',
    [0x15] = 'y',
    [0x16] = 'u',
    [0x17] = 'i',
    [0x18] = 'o',
    [0x19] = 'p',
    [0x1A] = '`',
    [0x1B] = '+',
    [0x1C] = '\n',

    [0x1E] = 'a',
    [0x1F] = 's',
    [0x20] = 'd',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',
    [0x27] = 'n',
    [0x28] = 0,
    [0x2B] = 'c',

    [0x2C] = 'z',
    [0x2D] = 'x',
    [0x2E] = 'c',
    [0x2F] = 'v',
    [0x30] = 'b',
    [0x31] = 'n',
    [0x32] = 'm',
    [0x33] = ',',
    [0x34] = '.',
    [0x35] = '-',

    [0x39] = ' ',

    [0x56] = '<',
};

/*
 * Shift combinations for the current Spanish keyboard mapping.
 */
static const char keyboard_shift_map[128] = {
    [0x01] = ASCII_ESCAPE,

    [0x02] = '!',
    [0x03] = '"',
    [0x04] = 0,
    [0x05] = '$',
    [0x06] = '%',
    [0x07] = '&',
    [0x08] = '/',
    [0x09] = '(',
    [0x0A] = ')',
    [0x0B] = '=',
    [0x0C] = '?',
    [0x0D] = 0,
    [0x0E] = '\b',

    [0x0F] = '\t',
    [0x10] = 'Q',
    [0x11] = 'W',
    [0x12] = 'E',
    [0x13] = 'R',
    [0x14] = 'T',
    [0x15] = 'Y',
    [0x16] = 'U',
    [0x17] = 'I',
    [0x18] = 'O',
    [0x19] = 'P',
    [0x1A] = '^',
    [0x1B] = '*',
    [0x1C] = '\n',

    [0x1E] = 'A',
    [0x1F] = 'S',
    [0x20] = 'D',
    [0x21] = 'F',
    [0x22] = 'G',
    [0x23] = 'H',
    [0x24] = 'J',
    [0x25] = 'K',
    [0x26] = 'L',
    [0x27] = 0,
    [0x28] = 0,
    [0x2B] = 0,

    [0x2C] = 'Z',
    [0x2D] = 'X',
    [0x2E] = 'C',
    [0x2F] = 'V',
    [0x30] = 'B',
    [0x31] = 'N',
    [0x32] = 'M',
    [0x33] = ';',
    [0x34] = ':',
    [0x35] = '_',

    [0x39] = ' ',

    [0x56] = '>',
};

/*
 * AltGr combinations for the current Spanish keyboard mapping.
 */
static const char keyboard_altgr_map[128] = {
    [0x02] = '|',
    [0x03] = '@',
    [0x04] = '#',
    [0x05] = '~',

    [0x1A] = '[',
    [0x1B] = ']',

    [0x28] = '{',
    [0x29] = '\\',
    [0x2B] = '}',
};

static bool keyboard_is_lower_letter(char character)
{
    return character >= 'a' && character <= 'z';
}

static bool keyboard_is_upper_letter(char character)
{
    return character >= 'A' && character <= 'Z';
}

static char keyboard_to_upper(char character)
{
    if (!keyboard_is_lower_letter(character)) {
        return character;
    }

    return character - ('a' - 'A');
}

static char keyboard_to_lower(char character)
{
    if (!keyboard_is_upper_letter(character)) {
        return character;
    }

    return character + ('a' - 'A');
}

static char keyboard_translate(uint8_t scancode)
{
    char character;

    if (scancode >= sizeof(keyboard_normal_map)) {
        return 0;
    }

    if (altgr_pressed) {
        return keyboard_altgr_map[scancode];
    }

    if (shift_pressed) {
        character = keyboard_shift_map[scancode];

        if (caps_lock_enabled && keyboard_is_upper_letter(character)) {
            character = keyboard_to_lower(character);
        }

        return character;
    }

    character = keyboard_normal_map[scancode];

    if (caps_lock_enabled) {
        character = keyboard_to_upper(character);
    }

    return character;
}

void keyboard_initialize(void)
{
    shift_pressed = false;
    caps_lock_enabled = false;
    alt_pressed = false;
    altgr_pressed = false;
    extended_scancode = false;
}

void keyboard_handle_irq(void)
{
    uint8_t scancode;
    uint8_t key;
    bool released;
    char character;

    scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode == KEYBOARD_E0_PREFIX) {
        extended_scancode = true;
        return;
    }

    key = scancode & KEYBOARD_SCANCODE_MASK;
    released = (scancode & KEYBOARD_RELEASED) != 0;

    if (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT) {
        shift_pressed = !released;
        extended_scancode = false;
        return;
    }

    if (key == KEY_ALT) {
        if (extended_scancode) {
            altgr_pressed = !released;
        } else {
            alt_pressed = !released;
        }

        extended_scancode = false;
        return;
    }

    extended_scancode = false;

    if (released) {
        return;
    }

    if (key == KEY_CAPS_LOCK) {
        caps_lock_enabled = !caps_lock_enabled;
        return;
    }

    character = keyboard_translate(key);

    if (character == 0) {
        return;
    }

    tty_putchar(character);
}
