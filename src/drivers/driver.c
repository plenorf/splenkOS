#include "driver.h"

void register_driver(Driver driver) {
    if (num_drivers < 256) {
        drivers[num_drivers++] = driver;
    }
}

void start_drivers() {
	for (int i = 0; i < num_drivers; i++) {
		drivers[i].init();
	}
}