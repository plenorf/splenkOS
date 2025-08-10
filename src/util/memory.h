#pragma once

#include <stdint.h>

void memory_init(uint64_t start_addr);
void* kmalloc(uint64_t size);
uint64_t get_mem_pointer(void);
void roll_back(uint64_t size);
