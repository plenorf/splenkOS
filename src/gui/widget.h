#pragma once
#include "graphics.h"

typedef struct
{
	Point position;
	Size size;
	Point anchourPoint;
	Colour backgroundColour;
	Colour borderColour;
	int borderSize;
	Widget *parent;
	Widget *children[255];
	void (*render)();
} Widget;
