#include "logging.h"
#include "flanterm/flanterm.h"
#include "flanterm/flanterm_backends/fb.h"
#include "limine.h"

struct flanterm_context *logging_init(struct limine_framebuffer *framebuffer) {
	struct flanterm_context *ft_ctx = flanterm_fb_init(
        NULL,
        NULL,
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch,
        framebuffer->red_mask_size, framebuffer->red_mask_shift,
        framebuffer->green_mask_size, framebuffer->green_mask_shift,
        framebuffer->blue_mask_size, framebuffer->blue_mask_shift,
        NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, 0, 0, 1,
        0, 0,
        0
    );
	return ft_ctx;
}

void print(const char *message, enum LOG_LEVEL level, struct flanterm_context *ft_ctx) {
	char* final = message;
}
void debug(const char *message, struct flanterm_context *ft_ctx) {
	print(message, DEBUG, ft_ctx);
}
void info(const char *message, struct flanterm_context *ft_ctx) {
	print(message, INFO, ft_ctx);
}
void ok(const char *message, struct flanterm_context *ft_ctx) {
	print(message, OK, ft_ctx);
}
void warn(const char *message, struct flanterm_context *ft_ctx) {
	print(message, WARN, ft_ctx);
}
void error(const char *message, struct flanterm_context *ft_ctx) {
	print(message, ERROR, ft_ctx);
}
void fatal(const char *message, struct flanterm_context *ft_ctx) {
	print(message, FATAL, ft_ctx);
}