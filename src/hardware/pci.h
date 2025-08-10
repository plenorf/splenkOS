#pragma once
#include <stdint.h>
#include <stdbool.h>

#define PCI_DATA_PORT 0xCFC
#define PCI_COMMAND_PORT 0xCF8

typedef struct DeviceDescriptor
{
	uint32_t portBase;
	uint32_t interrupt;

	uint16_t bus;
	uint16_t device;
	uint16_t function;

	uint16_t vendorId;
	uint16_t deviceId;

	uint8_t classId;
	uint8_t subclassId;
	uint8_t interfaceId;

	uint8_t revision;
} DeviceDescriptor;



uint32_t pciRead(uint16_t bus, uint16_t device, uint16_t function, uint32_t registerOffset);
void pciWrite(uint16_t bus, uint16_t device, uint16_t function, uint32_t registerOffset, uint32_t value);
bool pciDeviceHasFunction(uint16_t bus, uint16_t device);

DeviceDescriptor getDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function);