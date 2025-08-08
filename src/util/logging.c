#include "logging.h"
#include "libc/string.h"

void logMsg(const char* message, LogLevel logLevel, struct flanterm_context *ft_ctx) {
    if (logLevel < MIN_LOG_LEVEL) return; // if the log level is below the minimum log level then we don't do anything

    // i am the efficient code wizard, do not question my ways
    // my 3 strcats in one function will dazzle, amaze, and blaze
    // through buffer realms with zero bounds check fear
    // concatenating strings swift and clear,
    // a dance of pointers, no bugs to appear,
    // beware, mere mortals, my magic is near.
    char dest[100] = "\033[1m["; // this ansii escape code means bold
    switch (logLevel)
    {
    case DEBUG:
        strcat(dest, "\033[34mDEBUG\033[0m\033[1m]\033[0m  "); // the debug text is bold and dark blue
        break;
    case OK:
        strcat(dest, "\033[32mOK\033[0m\033[1m]\033[0m     "); // the OK text is bold and dark green
        break;
    case INFO:
        strcat(dest, "\033[36mINFO\033[0m\033[1m]\033[0m   "); // the info text is bold and dark cyan
        break;
    case WARNING:
        strcat(dest, "\033[93mWARN\033[0m\033[1m]\033[0m   "); // the warning text is bold and bright yellow
        break;
    case ERROR:
        strcat(dest, "\033[91mERR\033[0m\033[1m]\033[0m    "); // the error text is bold and bright red
        break;
    default:
        return;
    }
    strcat(dest, message);
    strcat(dest, "\n");

    // go forth my beautiful creation and wreak havoc
    flanterm_write(ft_ctx, dest, sizeof(dest));
}

void debug(const char* message, struct flanterm_context *ft_ctx) {
    logMsg(message, DEBUG, ft_ctx);
}
void ok(const char* message, struct flanterm_context *ft_ctx) {
    logMsg(message, OK, ft_ctx);
}
void info(const char* message, struct flanterm_context *ft_ctx) {
    logMsg(message, INFO, ft_ctx);
}
void warn(const char* message, struct flanterm_context *ft_ctx) {
    logMsg(message, WARNING, ft_ctx);
}
void error(const char* message, struct flanterm_context *ft_ctx) {
    logMsg(message, ERROR, ft_ctx);
}

struct flanterm_context* init_console(struct limine_framebuffer *framebuffer) {
	uint32_t *fb_ptr = framebuffer->address;
    struct flanterm_context *ft_ctx = flanterm_fb_init(
        NULL,
        NULL,
        fb_ptr, framebuffer->width, framebuffer->height, framebuffer->pitch,
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