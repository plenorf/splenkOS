#include "mem.h"

static uint8_t* g_bitmap;
static uint64_t g_total_frames;

#define BIT_SET(a, i)   (a[i >> 3] |=  (1 << (i & 7)))
#define BIT_CLEAR(a, i) (a[i >> 3] &= ~(1 << (i & 7)))
#define BIT_TEST(a, i)  (a[i >> 3] &   (1 << (i & 7)))

void pmm_init(uint64_t mem_size, uintptr_t bitmap_addr) {
    g_bitmap = (uint8_t*)bitmap_addr;
    g_total_frames = mem_size / FRAME_SIZE;

    /*mark all as free, RAM is precious and remember the rules
    Dont call free twice 
    Dont use freed memory right after being freed
    Dont call free after midnight
    Dont forget bounds checking 
    And Never Ever drink and Allocate*/ 

    for (uint64_t i = 0; i < (g_total_frames / 8); i++) {
        g_bitmap[i] = 0;
    }
}

void* pmm_alloc(void) {
    for (uint64_t i = 0; i < g_total_frames; i++) {
        if (!BIT_TEST(g_bitmap, i)) {
            BIT_SET(g_bitmap, i);
            return (void*)(i * FRAME_SIZE);
        }
    }
    return NULL; // this means you are a broke ass mf and doesn't own 4KB of ram https://www.memorystock.com/order-memory/orderitem.asp?it=509ms-122-M&sys=M935CG+V+1.0&MnfId=5664&MdlId=52964&Passfrm=lnk&srsltid=AfmBOor7CPIqSTfwAJ36BGfglXqlDMMYbYv3YHS8k_oKf8vyYDYAnwlsYAY
}

void pmm_free(void* frame) {
    uint64_t i = (uintptr_t)frame / FRAME_SIZE;
    BIT_CLEAR(g_bitmap, i);
}
