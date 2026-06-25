#include <drivers/pit.h>
#include <arch/io.h>
#include <arch/irq.h>

#define PIT_BASE_FREQUENCY  1193182

#define PIT_CHANNEL0        0x40
#define PIT_COMMAND         0x43

/*
 * Command byte: channel 0, access mode lobyte/hibyte, mode 3 (square wave),
 * binary counter.
 */
#define PIT_MODE_SQUARE_WAVE 0x36

#define PIT_IRQ              0

static uint32_t pit_ticks;

void pit_initialize(uint32_t frequency)
{
    uint32_t divisor;

    if (frequency == 0) {
        return;
    }

    divisor = PIT_BASE_FREQUENCY / frequency;

    outb(PIT_COMMAND, PIT_MODE_SQUARE_WAVE);
    outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xFF));

    pit_ticks = 0;

    irq_install_handler(PIT_IRQ, pit_tick);
}

uint32_t pit_get_ticks(void)
{
    return pit_ticks;
}

void pit_tick(void)
{
    pit_ticks++;
}
