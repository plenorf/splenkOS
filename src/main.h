#pragma once
#include "cpu/interrupts/irq.h"

void kpanic(InterruptFrame* frame);
extern volatile struct limine_memmap_request memmap_request;