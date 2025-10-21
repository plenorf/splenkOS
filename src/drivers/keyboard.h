#pragma once
#include "../hardware/driver.h"
#include "../cpu/interrupts/irq.h"
#include "../util/logging.h"
#include "../cpu/io.h"

#define KEYBOARD_IRQ 0x21

char *keycode = "\e 1234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0\0\0 ";
char *keycode_shift = "\e !@#$%^&*()_+\b\tQWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0\0\0 ";
bool isShift = false;

static volatile uint8_t kb_buffer[255];
static volatile int kb_head = 0;
static volatile int kb_tail = 0;

bool kb_has_scancode() {
    return kb_head != kb_tail;
}

static inline void kb_push(uint8_t sc) {
    int next = (kb_head + 1) % (int)(sizeof(kb_buffer));
    if (next == kb_tail) return; // buffer full, drop
    kb_buffer[kb_head] = sc;
    kb_head = next;
}

uint8_t kb_pop() {
    if (!kb_has_scancode()) return 0;
    uint8_t v = kb_buffer[kb_tail];
    kb_tail = (kb_tail + 1) % (int)(sizeof(kb_buffer));
    return v;
}

static InterruptFrame* keyboard_interrupt_handler(InterruptFrame *frame)
{
    uint8_t scancode = inb(0x60);

    // Handle shift presses/releases
    if (scancode == 0x2A) { isShift = true; return frame; }
    if (scancode == 0xAA) { isShift = false; return frame; }

    // Push scancode to buffer
    kb_push(scancode);

    PIC_sendEOI(frame->int_no-0x20); // Send End of Interrupt signal to PIC

    return frame;
}

// Convert scancode to ASCII
static char scancode_to_char(uint8_t sc)
{
    if (sc > 60) return 0;
    return isShift ? keycode_shift[sc] : keycode[sc];
}

char get_char()
{
    uint8_t scancode = inb(0x60);
    if (scancode < 60 && scancode > 0 && keycode[scancode] > 0 && keycode[scancode] < 254)
        return keycode[scancode];
    return 0;
}

int keyboard_init()
{
    
    register_interrupt_handler(KEYBOARD_IRQ, keyboard_interrupt_handler);
    //register_interrupt_handler(0x27, keyboard_interrupt_handler); // spurious interrupt, often unused, just ignore it
    PIC_set_mask(1, false);
    return 0;
}

char read_char()
{
    while (!kb_has_scancode()) {
        asm volatile("hlt"); // sleep until next interrupt
    }

    uint8_t scancode = kb_pop();
    char out = scancode_to_char(scancode);

    return out;
}

char *input(char *out)
{
    int index = 0;
    char c;

    while ((c = read_char()) != '\n')
    {
        if (c == '\b') {
            if (index > 0) {
                index--;
                out[index] = '\0';
                print("\b \b");
            }
            continue;
        }

        out[index++] = c;
        out[index] = '\0';
        printChar(c);
    }

    printChar('\n');
    return out;
}

static Driver keyboardDriver = {
    .name = "PS2Keyboard",
    .init = keyboard_init,
    .shutdown = NULL};
