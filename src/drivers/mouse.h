#pragma once

#include "../hardware/driver.h"
#include "../cpu/interrupts/irq.h"
#include "../cpu/io.h"
#include "../util/logging.h"

#define MOUSE_DATA 0x60
#define MOUSE_COMMAND 0x64
#define MOUSE_IRQ 0x2C

static InterruptFrame* mouse_interrupt_handler(InterruptFrame* frame) {
	print("MOUSE INTERRUPT\n");
	return frame;
}


static int mouse_init() {
	outb(MOUSE_COMMAND, 0xA8); // enable 2nd PS2 port
	outb(MOUSE_COMMAND, 0x20); // command: read config

	uint8_t status = inb(MOUSE_DATA); // read the config send back by the mouse
	status |= 0x02; // enable IRQ12 for the second port

	outb(MOUSE_COMMAND, 0x60); // command: write config
	outb(MOUSE_DATA, status); // send the new configuration

	outb(MOUSE_COMMAND, 0xD4); // next byte goes to mouse
	outb(MOUSE_DATA, 0xF4); // enable data reporting

	uint8_t ack = inb(MOUSE_DATA);
	if (ack != 0xFA) {
		// uhh....
		error("mouse init error, mouse ACK was not 0xFA");
		return 1;
	}

	//register_interrupt_handler(MOUSE_IRQ, mouse_interrupt_handler);

	return 0;
}

static Driver mouseDriver = {
	.name = "PS2Mouse",
	.init = mouse_init,
	.shutdown = NULL
};