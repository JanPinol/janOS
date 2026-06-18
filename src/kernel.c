


void kernel_main(void)
{
    volatile char *vga = (volatile char *)0xB8000;

    vga[0] = 'J';
    vga[1] = 0x0F;

    vga[2] = 'a';
    vga[3] = 0x0F;

    vga[4] = 'n';
    vga[5] = 0x0F;

    while (1) {
    }
}
