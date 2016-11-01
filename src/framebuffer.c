#include "framebuffer.h"
#include "utilities.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OUTPUT_BUFFER_RATIO 20

FrameBuffer FrameBuffer_allocate(size_t height,size_t width) {
	FrameBuffer fb;
	fb.contents = malloc(width * height * sizeof(char));
	fb.fgColors = malloc(width * height * sizeof(Color));
	fb.bgColors = malloc(width * height * sizeof(Color));
	fb.outputBuffer = malloc(width * height * sizeof(char) * OUTPUT_BUFFER_RATIO);
	if (fb.contents && fb.fgColors && fb.bgColors && fb.outputBuffer) {
		fb.width = width;
		fb.height = height;
	} else {
		FrameBuffer_deallocate(&fb);
		fb.width = fb.height = 0;
	}
	return fb;
}

void FrameBuffer_deallocate(FrameBuffer *fb) {
	free(fb->contents);
	free(fb->fgColors);
	free(fb->bgColors);
	free(fb->outputBuffer);
	fb->width = fb->height = 0;
}

void FrameBuffer_resize(FrameBuffer *fb, size_t newHeight, size_t newWidth) {
	fb->contents = realloc(fb->contents, newWidth * newHeight * sizeof(char));
	fb->fgColors = realloc(fb->fgColors, newWidth * newHeight * sizeof(Color));
	fb->bgColors = realloc(fb->bgColors, newWidth * newHeight * sizeof(Color));
	fb->outputBuffer = realloc(fb->outputBuffer, newWidth * newHeight * sizeof(char) * OUTPUT_BUFFER_RATIO);
	if (fb->contents && fb->fgColors && fb->bgColors && fb->outputBuffer) {
		fb->width = newWidth;
		fb->height = newHeight;
	} else {
		FrameBuffer_deallocate(fb);
		fb->width = fb->height = 0;
	}
}

void FrameBuffer_clear(FrameBuffer *fb) {
	memset(fb->contents, BLANK, fb->width * fb->height * sizeof(char));
	memset(fb->fgColors, TRANSPARENT, fb->width * fb->height * sizeof(Color));
	memset(fb->bgColors, TRANSPARENT, fb->width * fb->height * sizeof(Color));
}

void FrameBuffer_drawPoint(FrameBuffer *fb, Point p, char content, Color fgColor, Color bgColor) {
	if (p.r >= 0 && p.c >= 0 && p.r < fb->height && p.c < fb->width) {
		fb->contents[p.r*fb->width + p.c] = content;
		fb->fgColors[p.r*fb->width + p.c] = fgColor;
		fb->bgColors[p.r*fb->width + p.c] = bgColor;
	}
}

void FrameBuffer_drawTextBox(FrameBuffer *fb, Point topLeft, Point bottomRight, char *str, Color fgColor, Color bgColor) {
	int r, c;
	size_t slen = strlen(str);
	size_t it = 0;
	bool done = false;
	for (r = topLeft.r; r <= bottomRight.r && !done; r++) {
		for (c = topLeft.c; c <= bottomRight.c && !done; c++) {
			if (r >= 0 && c >= 0 && r < fb->height && c < fb->width) {
				fb->contents[r*fb->width + c] = str[it];
				if (fgColor != TRANSPARENT) fb->fgColors[r*fb->width + c] = fgColor;
				if (bgColor != TRANSPARENT) fb->bgColors[r*fb->width + c] = bgColor;
			}
			it++;
			if (it >= slen) done = true;
		}
	}
}

void FrameBuffer_drawRectangle(FrameBuffer *fb, Point topLeft, Point bottomRight, char borderCharacter, Color textColor, Color bgColor, Color borderColor) {
	int r, c;
	for (r = topLeft.r; r <= bottomRight.r; r++) {
		for (c = topLeft.c; c <= bottomRight.c; c++) {
			if (r >= 0 && c >= 0 && r < fb->height && c < fb->width) {
				if (r == topLeft.r || r == bottomRight.r || c == topLeft.c || c == bottomRight.c) {
					fb->contents[r*fb->width + c] = borderCharacter;
					if (textColor != TRANSPARENT) fb->fgColors[r*fb->width + c] = textColor;
					if (borderColor != TRANSPARENT) fb->bgColors[r*fb->width + c] = borderColor;
				} else {
					if (bgColor != TRANSPARENT) {
						fb->contents[r*fb->width + c] = BLANK;
						fb->bgColors[r*fb->width + c] = bgColor;
					}
				}
			}
		}
	}
}

void FrameBuffer_output(FrameBuffer *fb, bool useColor) {
	clearScreen();
	int r, c;
	size_t it = 0;
	for (r = 0; r < fb->height; r++) {
		for (c = 0; c < fb->width; c++) {
			if (useColor) {
				sprintf(fb->outputBuffer + it, "%s%s;", CS_INITIATOR, RESET);
				it += strlen(CS_INITIATOR) + strlen(RESET);
				if (fb->fgColors[r*fb->width + c] != TRANSPARENT) {
					sprintf(fb->outputBuffer + it, "%s;", fgColorConstants[fb->fgColors[r*fb->width + c]]);
					it += strlen(fgColorConstants[fb->fgColors[r*fb->width + c]]) + 1;
				}
				if (fb->bgColors[r*fb->width + c] != TRANSPARENT) {
					sprintf(fb->outputBuffer + it, "%s", bgColorConstants[fb->bgColors[r*fb->width + c]]);
					it += strlen(bgColorConstants[fb->bgColors[r*fb->width + c]]);
				}
				sprintf(fb->outputBuffer + it, "%s", CS_TERMINATOR);
				it += strlen(CS_TERMINATOR);
			}
			sprintf(fb->outputBuffer + it, "%c", fb->contents[r*fb->width + c]);
			it++;
			if (useColor) {
				sprintf(fb->outputBuffer + it, "%s%s;%s", CS_INITIATOR, RESET, CS_TERMINATOR);
				it += strlen(CS_INITIATOR) + 1 + strlen(RESET) + strlen(CS_TERMINATOR);
			}
		}
		sprintf(fb->outputBuffer + it, "\n");
		it++;
	}
	fb->outputBuffer[it] = 0;
	printf("%s", fb->outputBuffer);
}
