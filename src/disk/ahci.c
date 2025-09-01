#include "ahci.h"
#include "../util/logging.h"
#include "../cpu/io.h"

void identifyAHCI(ATA ata) {
	outw(ata.portBase + DEVICE_PORT, ata.master ? 0xA0 : 0xB0); // device port
	outb(ata.portBase + COMMAND_PORT, 0); // control port

	outw(ata.portBase + DEVICE_PORT, 0xA0);
	uint8_t status = inb(ata.portBase + COMMAND_PORT);
	if (status == 0xFF)
		return;

	outw(ata.portBase + DEVICE_PORT, ata.master ? 0xA0 : 0xB0);
	outb(ata.portBase + SECTOR_COUNT_PORT, 0);
	outb(ata.portBase + LBA_LOW_PORT, 0);
	outb(ata.portBase + LBA_MID_PORT, 0);
	outb(ata.portBase + LBA_HIGH_PORT, 0);
	outb(ata.portBase + COMMAND_PORT, 0xEC);

	status = inb(ata.portBase + COMMAND_PORT);
	if (status == 0x00) {
		warn("No device.");
		return; // no device
	}

	while (((status & 0x80) == 0x80) && (status & 0x01) != 0x01)
	{
		status = inb(ata.portBase + COMMAND_PORT);
	}

	if (status & 0x01)
	{
		error("ATA IDENTIFY ERROR");
		return;
	}

	for (uint16_t i = 0; i < 256; i++) {
		uint16_t data = inb(ata.portBase + DATA_PORT);	
		char* foo = "  \0";
		foo[1] = (data >> 8) & 0x00FF;
		foo[0] = data & 0x00FF;
		print(foo);
	}
	
}