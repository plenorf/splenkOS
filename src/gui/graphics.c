#include "graphics.h"

uint32_t colour_to_uint32(Colour colour) {
	return ((uint32_t)colour.R << 16) | ((uint32_t)colour.G << 8) | (uint32_t)colour.B;
}

// alpha: 0 = fully color2, 255 = fully color1
static inline uint32_t blend(uint32_t color1, uint32_t color2, uint8_t alpha)
{
    // Extract color channels (assuming 0xRRGGBB)
    uint8_t r1 = (color1 >> 16) & 0xFF;
    uint8_t g1 = (color1 >> 8)  & 0xFF;
    uint8_t b1 =  color1        & 0xFF;

    uint8_t r2 = (color2 >> 16) & 0xFF;
    uint8_t g2 = (color2 >> 8)  & 0xFF;
    uint8_t b2 =  color2        & 0xFF;

    // Integer linear interpolation
    uint8_t r = (r1 * alpha + r2 * (255 - alpha)) / 255;
    uint8_t g = (g1 * alpha + g2 * (255 - alpha)) / 255;
    uint8_t b = (b1 * alpha + b2 * (255 - alpha)) / 255;

    return (r << 16) | (g << 8) | b;
}

static inline void put_pixel(int x, int y, uint32_t colour, uint8_t alpha, struct limine_framebuffer *buffer) {
	uint32_t *fb_ptr = buffer->address;
	uint64_t bufferIndex = y * buffer->width + x;

	uint32_t currentColour = fb_ptr[bufferIndex];

	fb_ptr[y * buffer->width + x] = blend(colour, currentColour, alpha);
};

void clear_screen(Colour colour, struct limine_framebuffer *buffer) {
	if (buffer == NULL)
		return;

	uint32_t actualColour = colour_to_uint32(colour);

	uint32_t *fb_ptr = buffer->address;

	for (int y = 0; y < buffer->height; y++) {
		for (int x = 0; x < buffer->width; x++) {
			put_pixel(x, y, actualColour, colour.alpha, buffer);
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
        for (int xx = 0; xx < size.width; ++xx) {
			put_pixel(xx + x0, yy, actualColour, colour.alpha, buffer);
        }
	}
}

void draw_circle(Point center, int radius, Colour colour, struct limine_framebuffer *buffer)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius; // decision parameter

	uint32_t actualColour = colour_to_uint32(colour);

	int xc = center.x;
	int yc = center.y;

    while (x <= y) {
        // draw 8 symmetrical points
		put_pixel(xc + x, yc + y, actualColour, colour.alpha, buffer);
		put_pixel(xc - x, yc + y, actualColour, colour.alpha, buffer);
		put_pixel(xc + x, yc - y, actualColour, colour.alpha, buffer);
		put_pixel(xc - x, yc - y, actualColour, colour.alpha, buffer);
		put_pixel(xc + y, yc + x, actualColour, colour.alpha, buffer);
		put_pixel(xc - y, yc + x, actualColour, colour.alpha, buffer);
		put_pixel(xc + y, yc - x, actualColour, colour.alpha, buffer);
		put_pixel(xc - y, yc - x, actualColour, colour.alpha, buffer);

        if (d < 0)
            d = d + 4 * x + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void draw_filled_circle(Point center, int radius, Colour colour, struct limine_framebuffer *buffer) {
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;

	uint32_t actualColour = colour_to_uint32(colour);

	while (x <= y) {
		// draw horizontal spans between symmetrical points
		for (int i = center.x - x; i <= center.x + x; i++) {
			put_pixel(i, center.y + y, actualColour, colour.alpha, buffer);
			put_pixel(i, center.y - y, actualColour, colour.alpha, buffer);
		}
		for (int i = center.x - y; i <= center.x + y; i++) {
			put_pixel(i, center.y + x, actualColour, colour.alpha, buffer);
			put_pixel(i, center.y - x, actualColour, colour.alpha, buffer);
		}

		if (d < 0)
			d += 4 * x + 6;
		else {
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

void draw_rounded_rect(Point position, Size size, int cornerRadius, Colour colour, struct limine_framebuffer *buffer) {
	draw_filled_rect((Point){position.x + cornerRadius, position.y}, (Size){size.width - 2 * cornerRadius, size.height}, colour, buffer);

	draw_filled_rect((Point){position.x, position.y + cornerRadius}, (Size){cornerRadius, size.height - 2 * cornerRadius}, colour, buffer);
	draw_filled_rect((Point){position.x + size.width - cornerRadius, position.y + cornerRadius}, (Size){cornerRadius, size.height - 2 * cornerRadius}, colour, buffer);

	draw_filled_circle((Point){position.x + cornerRadius, position.y + cornerRadius}, cornerRadius, colour, buffer); // top left
	draw_filled_circle((Point){position.x + size.width - cornerRadius - 1, position.y + cornerRadius}, cornerRadius, colour, buffer); // top right
	draw_filled_circle((Point){position.x + cornerRadius, position.y + size.height - cornerRadius - 1}, cornerRadius, colour, buffer); // bottom left
	draw_filled_circle((Point){position.x + size.width - cornerRadius - 1, position.y + size.height - cornerRadius - 1}, cornerRadius, colour, buffer); // bottom right
}