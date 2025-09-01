#pragma once
#include "cpu/interrupts/irq.h"

static size_t total_ram = 0; // first make sure we dont have extra ram
void kpanic(InterruptFrame* frame);