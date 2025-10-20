#pragma once

#include "../hardware/driver.h"
#include "../cpu/interrupts/irq.h"
#include "../cpu/io.h"
#include "../util/logging.h"

#define MOUSE_DATA 0x60
#define MOUSE_COMMAND 0x64
#define MOUSE_IRQ 0x2C

static InterruptFrame* mouse_interrupt_handler(InterruptFrame* frame) {
	debug("MOUSE INTERRUPT");
	return frame;
}

inline void mouse_wait(uint8_t a_type) //unsigned char
{
  uint32_t _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(uint8_t a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outb(MOUSE_COMMAND, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outb(MOUSE_DATA, a_write);
}

uint8_t mouse_read()
{
  //Get's response from mouse
  mouse_wait(0); 
  return inb(MOUSE_DATA);
}

static int mouse_init() {
	register_interrupt_handler(MOUSE_IRQ, mouse_interrupt_handler);
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

	ok("mouse init success");

	return 0;
}

static Driver mouseDriver = {
	.name = "PS2Mouse",
	.init = mouse_init,
	.shutdown = NULL
};