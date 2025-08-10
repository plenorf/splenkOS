#include "driver.h"
#include "pci.h"
#include "../util/logging.h"
#include "../libc/string.h"

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

void select_drivers() {
	for (int bus = 0; bus < 8; bus++) {
		for (int device = 0; device < 32; device++) {
			int numFunctions = pciDeviceHasFunction(bus, device) ? 8 : 1;
			for (int function = 0; function < numFunctions; function++) {
				DeviceDescriptor descriptor = getDeviceDescriptor(bus, device, function);

				if (descriptor.vendorId == 0x0000 || descriptor.vendorId == 0xFFFF)
					continue;
				
				char buf[8];
				print("PCI BUS 0x");
				print(itoa(bus & 0xFF, buf, 16));

				print(", DEVICE 0x");
				print(itoa(device & 0xFF, buf, 16));

				print(", FUNCTION 0x");
				print(itoa(function & 0xFF, buf, 16));

				print(" = VENDOR 0x");
				print(itoa((descriptor.vendorId & 0xFF00) >> 8, buf, 16));
				print(itoa(descriptor.vendorId & 0xFF, buf, 16));
				print(", DEVICE 0x");
				print(itoa((descriptor.deviceId & 0xFF00) >> 8, buf, 16));
				print(itoa(descriptor.deviceId & 0xFF, buf, 16));
				printChar('\n');
			}
		}
	}
}