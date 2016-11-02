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
	size_t height;
	size_t width;
} FrameBuffer;

FrameBuffer FrameBuffer_allocate(const size_t height, const size_t width);

void FrameBuffer_deallocate(FrameBuffer *fb);

void FrameBuffer_resize(FrameBuffer *fb, const size_t newHeight, const size_t newWidth);

void FrameBuffer_clear(FrameBuffer *fb);

void FrameBuffer_drawPoint(FrameBuffer *fb, const Point p, const char content, const Color fgColor, const Color bgColor);

void FrameBuffer_drawTextBox(FrameBuffer *fb, const Point topLeft, const Point bottomRight, const char *str, const Color fgColor, const Color bgColor);

void FrameBuffer_drawRectangle(FrameBuffer *fb, const Point topLeft, const Point bottomRight, const char borderCharacter, const Color textColor, const Color bgColor, const Color borderColor);

void FrameBuffer_setInputPrompt(FrameBuffer *fb, const char *str);

void FrameBuffer_output(FrameBuffer *fb, const bool useColor);

#endif