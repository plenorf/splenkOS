#pragma once
#include <stddef.h>
#include "limine.h"

typedef struct
{
	char R;
	char G;
	char B;
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



static const Colour COLOUR_BLACK = {0,0,0};
static const Colour COLOUR_RED   = {255,0,0};

uint32_t colour_to_uint32(Colour colour);
void clear_screen(Colour colour, struct limine_framebuffer *buffer);
void draw_filled_rect(Point position, Size size, Colour colour, struct limine_framebuffer *buffer);