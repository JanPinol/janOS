#include "tty.h"

void kernel_main(void)
{
    tty_initialize();
    tty_writestring("VGA text terminal initialized.\n");

    while (1) {
    }
}
