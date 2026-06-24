#ifndef PIT_H
#define PIT_H

#include <stdint.h>

/*
 * Initializes the PIT timer at the given frequency.
 */
void pit_initialize(uint32_t frequency);

/*
 * Returns the number of timer ticks since PIT initialization.
 */
uint32_t pit_get_ticks(void);

/*
 * Handles one PIT timer tick.
 */
void pit_tick(void);

#endif
