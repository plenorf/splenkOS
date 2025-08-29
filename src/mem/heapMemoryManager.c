#include "mem.h"
#include "../util/logging.h"
#include "../libc/string.h"

typedef struct Block {
    size_t size;
    int    free;
    struct Block* next;
} Block;

static Block* heap_start = NULL;

#define BLOCK_SIZE sizeof(Block)

void heap_init(void* start, size_t heap_size) {
    heap_start = (Block*)start;
    heap_start->size = heap_size - BLOCK_SIZE;
    heap_start->free = 1;
    heap_start->next = NULL;
}

static Block* find_free_block(size_t size) {
    Block* curr = heap_start;
    while (curr) {
        if (curr->free && curr->size >= size)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void* kmalloc(size_t size) {
    Block* block = find_free_block(size);
    if (!block) return NULL;

    //Dont keep all your blocks in one basket, split them up if they are too big
    if (block->size > size + BLOCK_SIZE) {
        Block* newBlock = (Block*)((char*)block + BLOCK_SIZE + size);
        newBlock->size = block->size - size - BLOCK_SIZE;
        newBlock->free = 1;
        newBlock->next = block->next;

        block->size = size;
        block->next = newBlock;
    }

    block->free = 0;
    return (char*)block + BLOCK_SIZE;
}
//susie is fine for this
void kfree(void* ptr) {
    if (!ptr) return;
    Block* block = (Block*)((char*)ptr - BLOCK_SIZE);
    block->free = 1;

    // merge with next
    if (block->next && block->next->free) {
        block->size += BLOCK_SIZE + block->next->size;
        block->next = block->next->next;
    }
}


void mm_dump(void) {
    Block* curr = heap_start;
    while (curr) {
        char buf[64];
        print("[Block] ");
        itoa((uintptr_t)curr, buf, 10);
        print(buf);
        print(" size=");
        itoa((unsigned)curr->size, buf, 10);
        print(buf);
        print(" free=");
        itoa(curr->free, buf, 10);
        printChar('\n');
        curr = curr->next;
    }
}
