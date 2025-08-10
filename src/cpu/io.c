#include "io.h"

void outb(uint16_t port, uint8_t value) {
	asm volatile ("outb %1, %0" : : "dN"(port), "a"(value));
}

uint8_t inb(uint16_t port) {
	uint8_t rv;
	__asm__ __volatile__("inb %1, %0"
						: "=a"(rv)
						: "dN"(port));
	return rv;
}

void io_wait(void)
{
	inb(0x80);
}