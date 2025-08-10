#pragma once
#include <stdint.h>

typedef struct Driver {
    const char *name;
    int (*init)(void);      // Called when driver is loaded
    int (*shutdown)(void);  // Called before driver is unloaded
} Driver;

static Driver drivers[256];
static int num_drivers = 0;

void register_driver(Driver driver);
void start_drivers();