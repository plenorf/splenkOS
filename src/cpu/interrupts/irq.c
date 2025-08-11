#include "irq.h"
#include "../../util/logging.h"
#include "pic.h"
#include "../../libc/string.h"
#include <stddef.h>
#include "../../main.h"

void exception_handler(InterruptFrame* frame) {

	if (interruptHandlers[frame->int_no]) {
		interruptHandlers[frame->int_no](frame, *irqTaskManager);
		PIC_sendEOI(frame->int_no - 0x20); // Send End of Interrupt signal to PIC
		return;
	}

	// If no handler is registered, log the unhandled interrupt
	if (frame->int_no < 32) {
		kpanic(frame);
	} else {
		warn("Unhandled IRQ");
	}
    char buf[5];
    print("\t- Interrupt #: ");
    print(itoa(frame->int_no, buf, 10));
    print("\n\t- Error Code : ");
    print(itoa(frame->err_code, buf, 10));
    print("\n");
    PIC_sendEOI(frame->int_no-0x20);
    return; // VERY IMPORTANT THAT THIS FUNCTION RETURNS
}

void register_interrupt_handler(uint8_t irq, irq_handler_t handler) {
    interruptHandlers[irq] = handler;

	char buf[8];
	itoa(irq, buf, 16);
	char final[64];
	strcpy(final, "Registered interrupt handler for IRQ 0x");
	strcat(final, buf);
	debug(final);
}

void unregister_interrupt_handler(uint8_t irq) {
    interruptHandlers[irq] = NULL;
}