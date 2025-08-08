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

// display a message to the system console with the specified log level.
void logMsg(const char* message, LogLevel logLevel, struct flanterm_context *ft_ctx);
// display a message to the system console with a log level of DEBUG.
void debug(const char* message, struct flanterm_context *ft_ctx);
// display a message to the system console with a log level of OK.
void ok(const char* message, struct flanterm_context *ft_ctx);
// display a message to the system console with a log level of INFO.
void info(const char* message, struct flanterm_context *ft_ctx);
// display a warning to the system console.
void warn(const char* message, struct flanterm_context *ft_ctx);
// display an error to the system console.
void error(const char* message, struct flanterm_context *ft_ctx);

struct flanterm_context* init_console(struct limine_framebuffer *framebuffer);