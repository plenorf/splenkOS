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
bool isShift = false;

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
    int run = true;
    char out = 0;

    while (run)
    {

        if (inb(0x64) & 0x1)
        {
            uint8_t scancode = inb(0x60);
            if (scancode == 0x2A && !isShift)
                isShift = true;
            else if (scancode == 0xAA && isShift)
                isShift = false;
            if (!isShift)
                out = keycode[scancode];
            else if (isShift)
                out = keycode_shift[scancode];
            if (out != 0 && scancode < 60)
                run = false;
        }
    }
    
    return out;
}

Driver keyboardDriver = {
    .name = "Keyboard",
    .init = keyboard_init,
    .shutdown = NULL
};

