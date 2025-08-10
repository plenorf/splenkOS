#include "command_parser.h"
#include "../libc/string.h"

// this is terrible coding right here but it'll be removed later.
// its gonna be mainly used for testing features of the OS without
// having to hardcode exact values, which will make things easier

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