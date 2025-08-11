#include "driver.h"
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

	// TODO: we're doing a bit of a brute force method here, we're searching every function on every device on every bus,
	// 	     which is slow. i believe the OSDEV wiki has a page on doing this in a better way
	for (int bus = 0; bus < 8; bus++) {
		for (int device = 0; device < 32; device++) {
			int numFunctions = pciDeviceHasFunction(bus, device) ? 8 : 1;
			for (int function = 0; function < numFunctions; function++) {
				DeviceDescriptor descriptor = getDeviceDescriptor(bus, device, function);

				if (descriptor.vendorId == 0x0000 || descriptor.vendorId == 0xFFFF)
					continue;

				for (uint8_t barNum = 0; barNum < 6; barNum++) {
					// in getBaseAddressRegister, the address will be set to the higher bits of the
					// BAR, which in the case of InputOutput BARs contain the port number
					BaseAddressRegister bar = getBaseAddressRegister(bus, device, function, barNum);
					if (bar.address && bar.type == InputOutput) {
						descriptor.portBase = (uint32_t)bar.address;
					}

					Driver *driver = findDriver(descriptor);
					if (driver != NULL)
						register_driver(*driver);
				}
				
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

Driver *findDriver(DeviceDescriptor descriptor) {
	Driver* driver = NULL;

	switch (descriptor.vendorId)
	{
	case 0x1022: // AMD
		switch (descriptor.deviceId)
		{
		case 0x2000: // am79c973
			print("AMD am79c973 ");
			break;
		
		case 0x8086: // Intel
            break;
		}
		break;
	}

	switch(descriptor.classId)
    {
        case 0x03: // graphics
            switch(descriptor.subclassId)
            {
                case 0x00: // VGA
                    print("VGA ");
                    break;
            }
            break;
    }

	return driver;
}