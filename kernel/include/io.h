#ifndef IO_H
#define IO_H

#include <stdint.h>

/*
 * Reads one byte from an I/O port.
 */
uint8_t inb(uint16_t port);

/*
 * Writes one byte to an I/O port.
 */
void outb(uint16_t port, uint8_t value);

/*
 * Performs a small I/O delay.
 */
void io_wait(void);

#endif
