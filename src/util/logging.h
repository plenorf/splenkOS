#pragma once
struct flanterm_context *logging_init(struct limine_framebuffer *framebuffer);

enum LOG_LEVEL {
	DEBUG,
	INFO,
	OK,
	WARN,
	ERROR,
	FATAL
};

void print(const char *message, enum LOG_LEVEL level, struct flanterm_context *ft_ctx);
void debug(const char *message, struct flanterm_context *ft_ctx);
void info(const char *message, struct flanterm_context *ft_ctx);
void ok(const char *message, struct flanterm_context *ft_ctx);
void warn(const char *message, struct flanterm_context *ft_ctx);
void error(const char *message, struct flanterm_context *ft_ctx);
void fatal(const char *message, struct flanterm_context *ft_ctx);