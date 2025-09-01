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
			print("Available commands: help time sleep echo splenkfetch halt clear\n");
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
		else
		{
			print("Unknown command.\n");
		}
	}
}