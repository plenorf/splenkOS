#include "command_parser.h"
#include "../libc/string.h"
#include "logging.h"
// #include "../drivers/timer.h"
#include "mem/mem.h"

#include "main.h"


// this is terrible coding right here but it'll be removed later.
// its gonna be mainly used for testing features of the OS without
// having to hardcode exact values, which will make things easier

void parseCommand(char *input, struct limine_framebuffer *framebuffer)
{
	char *command = strtok(input, " ");
	if (command)
	{
		if (strcmp(command, "help") == 0)
		{
			print("Available commands: help time sleep echo splenkfetch halt clear memtest\n");
		}
		else if (strcmp(command, "echo") == 0)
		{
			char *token = strtok(NULL, " ");
			while (token != NULL)
			{
				print(token);
				printChar(' ');
				token = strtok(NULL, " ");
			}
			printChar('\n');
		}
		else if (strcmp(command, "time") == 0)
		{
			char buf[32];
			print("Seconds since boot: ");
			print(itoa((int)(get_uptime_ms() / 1000), buf, 10));
			printChar('\n');
		}
		else if (strcmp(command, "sleep") == 0)
		{
			char *durationStr = strtok(NULL, " ");
			if (durationStr == NULL)
			{
				print("Usage: sleep <duration in ms>");
				return;
			}
			int duration = atoi(durationStr);
			print("Sleeping for ");
			print(durationStr);
			print(" ms...");
			sleep(duration);
			printChar('\n');
		}
		else if (strcmp(command, "halt") == 0)
		{
			print("Bye bye computer!!!!!\n");
			for (;;)
			{
				asm("hlt");
			}
		}
		else if (strcmp(command, "clear") == 0)
		{
			print("\x1b[2J\x1b[H");
		}
		else if (strcmp(command, "splenkfetch") == 0)
		{
			char uptimeBuf[32];

			char resXBuffer[8];
			char resYBuffer[8];
			char finalBuf[128] = "\0";

			itoa((int)(get_uptime_ms() / 1000), uptimeBuf, 10);
			print("\033[1;92m       @@@@@                   @@@@@@         \033[0m");
			print("\n\033[1;92m    @@@    @@                @@    @@         \033[0m--------");
			print("\n\033[1;92m    @@     @@  @@@@@@@@@@@@ @@      @@        \033[0m\033[1;92mOS\033[0m: SplenkOS x86_64");
			print("\n\033[1;92m    @@   @@@@@@@@@@         @@@@    @@        \033[0m\033[1;92mUptime\033[0m: ");
			print(uptimeBuf);
			print(" seconds");
			print("\n\033[1;92m     @@@@                      @@@@@@@        \033[0m\033[1;92mResolution\033[0m: ");
			itoa(framebuffer->width, resXBuffer, 10);
			itoa(framebuffer->height, resYBuffer, 10);
			strcat(finalBuf, resXBuffer);
			strcat(finalBuf, "x");
			strcat(finalBuf, resYBuffer);
			print(finalBuf);
			print("\n\033[1;92m    @@                              @@        \033[0m");
			print("\n\033[1;92m   @@                                @@@      \033[0m");
			print("\n\033[1;92m  @@                                   @@     \033[0m");
			print("\n\033[1;92m  @@           @              @@        @     \033[0m");
			print("\n\033[1;92m  @@           @@            @@        @@     \033[0m");
			print("\n\033[1;92m  @@           @@            @@        @@     \033[0m");
			print("\n\033[1;92m  @@            @@           @@       @@@     \033[0m");
			print("\n\033[1;92m   @              @@@       @@        @@      \033[0m");
			print("\n\033[1;92m   @                @@@@@@@@@          @@@@   \033[0m");
			print("\n\033[1;92m   @                                      @@  \033[0m");
			print("\n\033[1;92m@@@@                    @@@               @@  \033[0m");
			print("\n\033[1;92m@       @     @@@@@@@@     @@     @@  @@@@@   \033[0m");
			print("\n\033[1;92m@@@@@@@@@     @             @@@@@@@           \033[0m");
			print("\n\033[1;92m     @ @@   @@                                \033[0m");
			print("\n\033[1;92m        @@@@@                                 \033[0m\n");
		}
		else if (strcmp(command, "memtest") == 0)
		{
			print("Testing kmalloc...\n");
			void *ptr1 = kmalloc(16);
			void *ptr2 = kmalloc(32);
			void *ptr3 = kmalloc(64);
			void *ptr4 = kmalloc(128);
			void *ptr5 = kmalloc(256);
			void *ptr6 = kmalloc(512);
			void *ptr7 = kmalloc(1024);
			void *ptr8 = kmalloc(2048);
			void *ptr9 = kmalloc(4096);
			print("Allocated 16 bytes at ");
			print(itoa((int)(uint64_t)ptr1, (char *)kmalloc(12), 16));
			print("\nAllocated 32 bytes at ");
			print(itoa((int)(uint64_t)ptr2, (char *)kmalloc(12), 16));
			print("\nAllocated 64 bytes at ");
			print(itoa((int)(uint64_t)ptr3, (char *)kmalloc(12), 16));
			print("\nAllocated 128 bytes at ");
			print(itoa((int)(uint64_t)ptr4, (char *)kmalloc(12), 16));
			print("\nAllocated 256 bytes at ");
			print(itoa((int)(uint64_t)ptr5, (char *)kmalloc(12), 16));
			print("\nAllocated 512 bytes at ");
			print(itoa((int)(uint64_t)ptr6, (char *)kmalloc(12), 16));
			print("\nAllocated 1024 bytes at ");
			print(itoa((int)(uint64_t)ptr7, (char *)kmalloc(12), 16));
			print("\nAllocated 2048 bytes at ");
			print(itoa((int)(uint64_t)ptr8, (char *)kmalloc(12), 16));
			print("\nAllocated 4096 bytes at ");
			print(itoa((int)(uint64_t)ptr9, (char *)kmalloc(12), 16));
			printChar('\n');
			print("Filling memory with pattern 0xAA...\n");
			memset(ptr1, 0xAA, 16);
			memset(ptr2, 0xAA, 32);
			memset(ptr3, 0xAA, 64);
			memset(ptr4, 0xAA, 128);
			memset(ptr5, 0xAA, 256);
			memset(ptr6, 0xAA, 512);
			memset(ptr7, 0xAA, 1024);
			memset(ptr8, 0xAA, 2048);
			memset(ptr9, 0xAA, 4096);
			print("Memory filled.\n");
			print("Emptying Memory...\n");
			memset(ptr1, 0x00, 16);
			memset(ptr2, 0x00, 32);
			memset(ptr3, 0x00, 64);
			memset(ptr4, 0x00, 128);
			memset(ptr5, 0x00, 256);
			memset(ptr6, 0x00, 512);
			memset(ptr7, 0x00, 1024);
			memset(ptr8, 0x00, 2048);
			memset(ptr9, 0x00, 4096);
			print("Emptied memory at ");
			print(itoa((int)(uint64_t)ptr1, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr2, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr3, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr4, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr5, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr6, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr7, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr8, (char *)kmalloc(12), 16));
			print("\nEmptied memory at ");
			print(itoa((int)(uint64_t)ptr9, (char *)kmalloc(12), 16));
			print("\n");
			print("Memory emptied.\n");
			print("Memory test complete.\n");
		}

		else if (strcmp(command, "add") == 0)
		{
			char *num1Str = strtok(NULL, " ");
			char *num2Str = strtok(NULL, " ");
			if (num1Str == NULL || num2Str == NULL) {
				print("Usage: add <num1> <num2>\n");
				return;
			}
			int num1 = atoi(num1Str);
			int num2 = atoi(num2Str);
			char resultBuf[32];
			print("Result: ");
			print(itoa(num1 + num2, resultBuf, 10));
			printChar('\n');
		}
		
		else
		{
			print("Unknown command.\n");
		}
	}
}