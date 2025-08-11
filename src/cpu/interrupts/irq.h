#pragma once
#include <stdint.h>
#include <stddef.h>
#include "../multitasking.h"

typedef struct InterruptFrame
{
    uint64_t r11, r10, r9, r8;
    uint64_t rsi, rdi, rdx, rcx, rax;
    uint64_t int_no, err_code;
    uint64_t rsp, rflags, cs, rip;
}__attribute__((packed)) InterruptFrame;

typedef void (*irq_handler_t)(InterruptFrame* frame, TaskManager irqTaskManager);
static irq_handler_t interruptHandlers[256];

static TaskManager* irqTaskManager = NULL;

void register_interrupt_handler(uint8_t irq, irq_handler_t handler);
void unregister_interrupt_handler(uint8_t irq);
void exception_handler(InterruptFrame* frame);