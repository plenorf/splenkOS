#include "idt.h"
#include "../gdt.h"
#include "../../util/logging.h"
#include "../../libc/string.h"
#include "pic.h"

extern void* isr_stub_table[];

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
    // set the start position and length of the idt in the pointer
	idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_ENTRIES - 1;

    // open all idt gates
    for (uint8_t vector = 0; vector < IDT_MAX_ENTRIES-1; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }

    // load the idt
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
}