#include "driver.h"
#include "../cpu/interrupts/irq.h"
#include "../util/logging.h"
#include "../util/serial.h"
#include "../libc/string.h"

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_FREQUENCY 1193182
#define PIT_IRQ      0x20

static uint64_t msSinceBoot = 0;

void timer_interrupt_handler(InterruptFrame* frame) {
	msSinceBoot += 1;
}

uint64_t get_uptime_ms() {
	return msSinceBoot;
}

void sleep(uint64_t ms) {
	uint64_t start = get_uptime_ms();
	uint64_t end = start + ms;

	while (get_uptime_ms() < end) {
		asm("hlt");
	}
}

int timer_init() {
	uint32_t freq = 1000; // 1000 Hz
	uint16_t divisor = PIT_FREQUENCY / freq;
	outb(PIT_COMMAND, 0x36);           // Channel 0, low/high byte, mode 3
    outb(PIT_CHANNEL0, divisor & 0xFF); // Low byte
    outb(PIT_CHANNEL0, divisor >> 8);   // High byte

	register_interrupt_handler(0x20, timer_interrupt_handler);
	return 0;
}

Driver timerDriver = {
	.name = "Timer",
	.init = timer_init,
	.shutdown = NULL
};