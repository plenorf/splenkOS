#include "graphics.h"

uint32_t colour_to_uint32(Colour colour) {
	return ((uint32_t)colour.R << 16) | ((uint32_t)colour.G << 8) | (uint32_t)colour.B;
}

void clear_screen(Colour colour, struct limine_framebuffer *buffer) {
	if (buffer == NULL)
		return;

	uint32_t actualColour = colour_to_uint32(colour);

	uint32_t *fb_ptr = buffer->address;

	for (int y = 0; y < buffer->height-1; y++) {
		for (int x = 0; x < buffer->width-1; x++) {
			fb_ptr[y * buffer->height + x] = 0x000000;
		}
	}
}

void draw_filled_rect(Point position, Size size, Colour colour, struct limine_framebuffer *buffer) {
	if (buffer == NULL)
		return;

	uint32_t actualColour = colour_to_uint32(colour);
	uint32_t *fb_ptr = buffer->address;

	int x0 = position.x;
	int y0 = position.y;
	int x1 = position.x + size.width;
	int y1 = position.y + size.height;

	for (int yy = y0; yy < y1; yy++) {
		uint32_t *row = fb_ptr + yy * buffer->width + x0;
        for (int xx = 0; xx < size.width; ++xx) {
            row[xx] = actualColour;
        }
	}
}