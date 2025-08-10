#include "driver.h"
#include "../cpu/interrupts/irq.h"
#include "../util/logging.h"

static void timer_interrupt_handler(InterruptFrame* frame) {
	debug("Timer interrupt received by the driver!");
}

static int timer_init() {
	register_interrupt_handler(0x20, timer_interrupt_handler);
	return 0;
}