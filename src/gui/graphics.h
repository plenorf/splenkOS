#pragma once
#include <stddef.h>
#include "limine.h"

typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t alpha;
} Colour;

typedef struct
{
	int x;
	int y;
} Point;

typedef struct
{
	int width;
	int height;
} Size;


// r, g, b, alpha
static const Colour COLOUR_BLACK       = {0,0,0,255};
static const Colour COLOUR_WHITE       = {255,255,255,255};
static const Colour COLOUR_GREY        = {127,127,127,255};
static const Colour COLOUR_LIGHT_GREY  = {192,192,192,255};
static const Colour COLOUR_DARK_GREY   = {64,64,64,255};
static const Colour COLOUR_RED         = {255,0,0,255};
static const Colour COLOUR_LIGHT_RED   = {255,127,127,255};
static const Colour COLOUR_GREEN       = {0,255,0,255};
static const Colour COLOUR_LIGHT_GREEN = {127,255,127,255};
static const Colour COLOUR_BLUE        = {0,0,255,255};
static const Colour COLOUR_LIGHT_BLUE  = {127,127,255,255};
static const Colour COLOUR_CYAN        = {0,255,255,255};
static const Colour COLOUR_LIGHT_CYAN  = {127,255,255,255};
static const Colour COLOUR_DARK_CYAN   = {0,128,128,255};

uint32_t colour_to_uint32(Colour colour);
void clear_screen(Colour colour, struct limine_framebuffer *buffer);
void draw_filled_rect(Point position, Size size, Colour colour, struct limine_framebuffer *buffer);
void draw_circle(Point center, int radius, Colour colour, struct limine_framebuffer *buffer);
void draw_filled_circle(Point center, int radius, Colour colour, struct limine_framebuffer *buffer);
void draw_rounded_rect(Point position, Size size, int cornerRadius, Colour colour, struct limine_framebuffer *buffer);