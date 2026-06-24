#include "pit.h"
#include "io.h"

#define PIT_BASE_FREQUENCY  1193182

#define PIT_CHANNEL0        0x40
#define PIT_COMMAND         0x42

#define PIC_MODE_RATE       0x36

static uint32_t pit_ticks;

void pit_initialize(uint32_t frequency)
{
    uint32_t divisor;

    if (frequency == 0) {
        return;
    }

    divisor = PIT_BASE_FREQUENCY / frequency;

    outb(PIT_COMMAND, PIC_MODE_RATE);
    outb(PIT_CHANNEL0, (uint8_t) divisor & 0xFF);
    outb(PIT_CHANNEL0, (uint8_t) (divisor >> 8) & 0xFF);

    pit_ticks = 0;
}

uint32_t pit_get_ticks(void)
{
    return pit_ticks;
}

void pit_tick(void)
{
    pit_ticks++;
}
