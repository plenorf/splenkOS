#pragma once
#include <stdint.h>
#include <stdbool.h>

#define DATA_PORT 0
#define ERROR_PORT 1
#define SECTOR_COUNT_PORT 2
#define LBA_LOW_PORT 3
#define LBA_MID_PORT 4
#define LBA_HIGH_PORT 5
#define DEVICE_PORT 6 // the only 16 bit port, the rest are 8 bit
#define COMMAND_PORT 7
#define CONTROL_PORT 0x206

typedef struct
{
	uint16_t bytesPerSector;
	bool master;
	uint8_t portBase;

} ATA;


void identifyAHCI(ATA ata);
void readAHCI20(uint32_t sector);
void writeAHCI20(uint32_t sector, uint8_t* data, int count);
void flushAHCI();