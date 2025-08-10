#include "command_parser.h"
#include "../libc/string.h"
#include "logging.h"

// this is terrible coding right here but it'll be removed later.
// its gonna be mainly used for testing features of the OS without
// having to hardcode exact values, which will make things easier

void parseCommand(char *input) {
	char *command = strtok(input, " ");
	if (command) {
		if (strcmp(command, "help") == 0) {
			print("Available commands: help");
		} else {
			print("Unknown command.");
		}
	}
}