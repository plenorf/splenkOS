#include "pci.h"
#include "../cpu/io.h"

uint32_t pciRead(uint16_t bus, uint16_t device, uint16_t function, uint32_t registerOffset)
{
	uint32_t id = 0x1 << 31 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | (registerOffset & 0xFC);
	outl(PCI_COMMAND_PORT, id);
	uint32_t result = inl(PCI_DATA_PORT) >> (8 * (registerOffset % 4));
	return result;
}

void pciWrite(uint16_t bus, uint16_t device, uint16_t function, uint32_t registerOffset, uint32_t value)
{
	uint32_t id = 0x1 << 31 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | (registerOffset & 0xFC);
	outl(PCI_COMMAND_PORT, id);
	outl(PCI_DATA_PORT, value);
}

bool pciDeviceHasFunction(uint16_t bus, uint16_t device)
{
	// the 7th bit of the address tells us if the device has function or not
	return pciRead(bus, device, 0, 0x0E) & (1 << 7);
}

DeviceDescriptor getDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function) {
	DeviceDescriptor result;

	result.bus = bus;
	result.device = device;
	result.function = function;

	result.vendorId = pciRead(bus, device, function, 0x00);
	result.deviceId = pciRead(bus, device, function, 0x02);

	result.classId  = pciRead(bus, device, function, 0x0B);
	result.subclassId = pciRead(bus, device, function, 0x0A);
	result.interfaceId = pciRead(bus, device, function, 0x09);

	result.revision = pciRead(bus, device, function, 0x08);
	result.interrupt = pciRead(bus, device, function, 0x3C);

	return result;
}