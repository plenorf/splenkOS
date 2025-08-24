#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H
#include "../hardware/driver.h"
#include "../cpu/interrupts/irq.h"
#include "../util/logging.h"
#include "../util/serial.h"
#include "../libc/string.h"
#include "../cpu/io.h"
#include "../scheduler.h"

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_FREQUENCY 1193182
#define PIT_IRQ      0x20

static uint64_t msSinceBoot = 0;

static InterruptFrame* timer_interrupt_handler(InterruptFrame* frame) {
	msSinceBoot += 1;

	if (scheduler != NULL)
	{
		print("BEFORE:\n");
		char buf[32];
		print("INT: 0x");
		print(itoa(frame->int_no, buf, 16));
		printChar('\n');
		print("RIP: 0x");
		print(itoa(frame->rip, buf, 16));
		printChar('\n');
		print("RSP: 0x");
		print(itoa(frame->rsp, buf, 16));
		printChar('\n');
		print("RAX: 0x");
		print(itoa(frame->rax, buf, 16));
		printChar('\n');
		print("proc pointer: 0x");
		print(itoa((uint32_t)scheduler->currentProcess, buf, 16));
		printChar('\n');
		print("context pointer: 0x");
		print(itoa((uint32_t)scheduler->currentProcess->context, buf, 16));
		printChar('\n');
		print("---------------\n");

		// each clock tick we swap between each running process
		// this gives the illusion that multiple processes are
		// running simultaneously, since our clock is running
		// at 1KHz, each program gets 1 ms of CPU time per tick,
		// this is called a quantum.
		frame = schedule(scheduler, &frame);

		print("AFTER:\n");
		print("INT: 0x");
		print(itoa(frame->int_no, buf, 16));
		printChar('\n');
		print("RIP: 0x");
		print(itoa(frame->rip, buf, 16));
		printChar('\n');
		print("RSP: 0x");
		print(itoa(frame->rsp, buf, 16));
		printChar('\n');
		print("RAX: 0x");
		print(itoa(frame->rax, buf, 16));
		printChar('\n');
		print("proc pointer: 0x");
		print(itoa((uint32_t)scheduler->currentProcess, buf, 16));
		printChar('\n');
		print("context pointer: 0x");
		print(itoa((uint32_t)scheduler->currentProcess->context, buf, 16));
		printChar('\n');
		print("---------------\n");
		
	}

	return frame;
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

static int timer_init() {
	uint32_t freq = 1000; // 1 KHz
	uint16_t divisor = PIT_FREQUENCY / freq;
	outb(PIT_COMMAND, 0x36);           // Channel 0, low/high byte, mode 3
    outb(PIT_CHANNEL0, divisor & 0xFF); // Low byte
    outb(PIT_CHANNEL0, divisor >> 8);   // High byte

	register_interrupt_handler(0x20, timer_interrupt_handler);
	return 0;
}

static Driver timerDriver = {
	.name = "Timer",
	.init = timer_init,
	.shutdown = NULL
};
#endif // ! TIMER_DRIVER_H