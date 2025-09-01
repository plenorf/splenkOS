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

void outw(uint16_t port, uint16_t value) {
	__asm__ __volatile__("outw %1, %0" : : "dN"(port), "a"(value));
}

uint16_t inw(uint16_t port) {
	uint16_t rv;
	__asm__ __volatile__("inw %1, %0"
						: "=a"(rv)
						: "dN"(port));
	return rv;
}

void outl(uint16_t port, uint32_t value) {
    asm volatile ("outl %0, %1" : : "a"(value), "dN"(port));
}

uint32_t inl(uint16_t port) {
    uint32_t rv;
    asm volatile ("inl %1, %0"
                  : "=a"(rv)
                  : "dN"(port));
    return rv;
}

void io_wait(void)
{
	inb(0x80);
}