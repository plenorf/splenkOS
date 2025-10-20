#pragma once
#include "graphics.h"
#include <stdbool.h>

struct BaseWidget;

struct BaseWidget
{ 
	Point position;
	Size size;
	Point anchourPoint;
	Colour backgroundColour;
	Colour borderColour;
	int borderSize;
	struct BaseWidget *parent;
	struct BaseWidget *children[100];
	struct BaseWidget *focussedChild;
	int numChildren;
	bool focussable;

	void (*draw)(struct BaseWidget* self, struct limine_framebuffer *framebuffer);
	void (*onKeyDown)(struct BaseWidget* self, char key);
	void (*onKeyUp)(struct BaseWidget* self, char key);
	void (*onMouseDown)(struct BaseWidget* self);
	void (*onMouseUp)(struct BaseWidget* self);
};

void getFocus(struct BaseWidget *parent, struct BaseWidget *widget);
void addChild(struct BaseWidget *parent, struct BaseWidget *newChild);
void drawWidget(struct BaseWidget *widget, struct limine_framebuffer *framebuffer);