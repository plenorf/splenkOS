#include "driver.h"
#include "../cpu/interrupts/irq.h"
#include "../util/logging.h"

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_FREQUENCY 1193182

static uint64_t msSinceBoot = 0;

static void timer_interrupt_handler(InterruptFrame* frame) {
	msSinceBoot += 1;
}

static int timer_init() {
	uint32_t freq = 1000; // 1000 Hz
	uint16_t divisor = PIT_FREQUENCY / freq;
	outb(PIT_COMMAND, 0x36);           // Channel 0, low/high byte, mode 3
    outb(PIT_CHANNEL0, divisor & 0xFF); // Low byte
    outb(PIT_CHANNEL0, divisor >> 8);   // High byte

	register_interrupt_handler(0x20, timer_interrupt_handler);
	return 0;
}