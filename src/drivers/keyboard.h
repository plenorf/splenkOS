#include "driver.h"
#include "../cpu/interrupts/irq.h"

int keyboard_init() {
    return 0;
}

Driver keyboardDriver = {
    .name = "Keyboard",
    .init = keyboard_init,
    .shutdown = NULL
};

