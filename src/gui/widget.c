#include "widget.h"

void getFocus(struct BaseWidget *parent, struct BaseWidget *widget) {
	if (!widget->focussable)
		return;
		
	parent->focussedChild = widget;
	if (parent->parent != NULL) {
		// send the focus message up the parent chain
		getFocus(parent->parent, parent);
	}
}

void addChild(struct BaseWidget *parent, struct BaseWidget *newChild) {
	if (parent->numChildren >= 100) // max number of children
		return false;
	if (newChild->parent) // can't change parent if child already has a parent
		return false;

	parent->children[parent->numChildren++] = newChild;
	newChild->parent = parent;

	return true;
}

void drawWidget(struct BaseWidget *widget, struct limine_framebuffer *framebuffer) {
	if (widget->draw == NULL)
		return false;

	widget->draw(widget, framebuffer);
	for (int i = widget->numChildren-1; i >= 0; i--)

		if (widget->children[i]->draw)
			widget->children[i]->draw(widget->children[i], framebuffer);

	return true;
}