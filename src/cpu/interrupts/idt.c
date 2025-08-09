#include "idt.h"
#include "../gdt.h"
#include "../../util/logging.h"
#include "../../libc/string.h"

extern void* isr_stub_table[];

__attribute__((noreturn))
void exception_handler(InterruptFrame* frame) {
    char buf[5];
    warn("UNHANDLED INTERRUPT");
    print("\t- Interrupt #: ");
    print(itoa(frame->int_no, buf, 10));
    print("\n\t- Error Code : ");
    print(itoa(frame->err_code, buf, 10));
    print("\n");

    //print("Halting CPU...\n");
    //asm volatile ("hlt");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs      = GDT_CODE_SEGMENT;
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->isr_mid        = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved       = 0;
}

void idt_init(void) {
	idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_ENTRIES - 1;

    print("\tIDTR INFO:\n\t\t- BASE: 0x");
    char buf[16];
    print(itoa((int)idtr.base, buf, 16));
    print("\n\t\t- LIMIT: 0x");
    print(itoa((int)idtr.limit, buf, 16));
    print("\n");

    for (uint8_t vector = 0; vector < IDT_MAX_ENTRIES-1; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }

    debug("All IDT gates open!");
    debug("Loading IDTR...");

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}