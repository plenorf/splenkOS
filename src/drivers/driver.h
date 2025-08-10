#pragma once
#include <stdint.h>

typedef struct Driver {
    const char *name;
    int (*init)(void);      // Called when driver is loaded
    int (*shutdown)(void);  // Called before driver is unloaded
} Driver;