#pragma once
#include "flanterm/flanterm.h"
#include "flanterm/flanterm_backends/fb.h"
#include "limine.h"

typedef enum {
	DEBUG,
	OK,
	INFO,
	WARNING,
	ERROR
} LogLevel;

#define MIN_LOG_LEVEL DEBUG

static struct flanterm_context *ft_ctx = NULL;

// display a message to the system console with the specified log level.
void logMsg(const char* message, LogLevel logLevel);
// display a message to the system console with a log level of DEBUG.
void debug(const char* message);
// display a message to the system console with a log level of OK.
void ok(const char* message);
// display a message to the system console with a log level of INFO.
void info(const char* message);
// display a warning to the system console.
void warn(const char* message);
// display an error to the system console.
void error(const char* message);

void init_console(struct limine_framebuffer *framebuffer);