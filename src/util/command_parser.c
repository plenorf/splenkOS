#include "command_parser.h"
#include "../libc/string.h"

void parseCommand(char *input) {
	char *command = strtok(input, " ");
	if (command) {
		if (strcmp(command, "help") == 0) {
			print("Available commands: help, reboot, shutdown");
		} else if (strcmp(command, "reboot") == 0) {
			print("Rebooting...");
		} else if (strcmp(command, "shutdown") == 0) {
			print("Shutting down...");
		} else {
			print("Unknown command.");
		}
	}
}