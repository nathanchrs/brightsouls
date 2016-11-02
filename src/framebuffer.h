#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdlib.h>
#include "boolean.h"
#include "point.h"
#include "color.h"

#define BLANK ' '

typedef struct {
	char *contents;
	Color *fgColors;
	Color *bgColors;
	char *outputBuffer;
	char *inputPrompt;
	size_t width;
	size_t height;
} FrameBuffer;

FrameBuffer FrameBuffer_allocate(size_t height, size_t width);

void FrameBuffer_deallocate(FrameBuffer *fb);

void FrameBuffer_resize(FrameBuffer *fb, size_t newHeight, size_t newWidth);

void FrameBuffer_clear(FrameBuffer *fb);

void FrameBuffer_drawPoint(FrameBuffer *fb, Point p, char content, Color fgColor, Color bgColor);

void FrameBuffer_drawTextBox(FrameBuffer *fb, Point topLeft, Point bottomRight, const char *str, Color fgColor, Color bgColor);

void FrameBuffer_drawRectangle(FrameBuffer *fb, Point topLeft, Point bottomRight, const char borderCharacter, Color textColor, Color bgColor, Color borderColor);

void FrameBuffer_setInputPrompt(FrameBuffer *fb, const char *str);

void FrameBuffer_output(FrameBuffer *fb, bool useColor);

#endif