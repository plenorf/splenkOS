#include "driver.h"
#include "../cpu/interrupts/irq.h"
#include "../util/logging.h"
#include "../cpu/io.h"

char read_char();
char *input();
void keyboard_handler();

#define KEYBOARD_IRQ 0x21

char *keycode = "\e 1234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0\0\0 ";
char *keycode_shift = "\e !@#$%^&*()_+\b\tQWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0\0\0 ";

void keyboard_interrupt_handler(InterruptFrame* frame) {
    
}

char get_char() {
    uint8_t scancode = inb(0x60);
    if (scancode < 60 && scancode > 0 && keycode[scancode] > 0 && keycode[scancode] < 254)
        return keycode[scancode];
}

int keyboard_init() {
    register_interrupt_handler(KEYBOARD_IRQ, keyboard_interrupt_handler);
    return 0;
}

char read_char()
{
    int run = 1;
    char out 0;
    while (run)
    {
        if (inportb(0x64) & 0x1)
        {
            if (inportb(0x60) == 0x2A && !isShift)
                isShift = 1;
            else if (inportb(0x60) == 0xAA && isShift)
                isShift = 0;
            if (!isShift)
                out = keycode[inportb(0x60)];
        }
    }
}

Driver keyboardDriver = {
    .name = "Keyboard",
    .init = keyboard_init,
    .shutdown = NULL
};

