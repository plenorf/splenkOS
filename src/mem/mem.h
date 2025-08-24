#pragma once
#include <stdint.h>
#include <stddef.h>

#define FRAME_SIZE 4096  

// Physical Memory Manager functions
void pmm_init(uint64_t mem_size, uintptr_t bitmap_addr);
void* pmm_alloc(void);
void  pmm_free(void* frame);

// Heap functions
void  heap_init(void* heap_start, size_t heap_size);
void* kmalloc(size_t size);
void  kfree(void* ptr);
void  mm_dump(void);
