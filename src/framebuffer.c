#include "framebuffer.h"
#include "utilities.h"
#include "stringutils.h"
#include <stdlib.h>
#include <stdio.h>

// Make sure the output buffer is large enough for the screen output + maximum length of control characters
#define OUTPUT_BUFFER_RATIO 20

FrameBuffer FrameBuffer_allocate(const size_t height, const size_t width, bool supportsColor) {
	FrameBuffer fb;
	fb.contents = malloc(width * height * sizeof(char));
	fb.fgColors = malloc(width * height * sizeof(Color));
	fb.bgColors = malloc(width * height * sizeof(Color));
	fb.inputPrompt = malloc(width * sizeof(char));
	fb.outputBuffer = malloc(width * height * sizeof(char) * OUTPUT_BUFFER_RATIO);
	if (fb.contents && fb.fgColors && fb.bgColors && fb.outputBuffer) {
		fb.width = width;
		fb.height = height;
	} else {
		FrameBuffer_deallocate(&fb);
		fb.width = fb.height = 0;
	}
	fb.supportsColor = supportsColor;
	return fb;
}

void FrameBuffer_deallocate(FrameBuffer *fb) {
	free(fb->contents);
	free(fb->fgColors);
	free(fb->bgColors);
	free(fb->inputPrompt);
	free(fb->outputBuffer);
	fb->width = fb->height = 0;
}

void FrameBuffer_resize(FrameBuffer *fb, const size_t newHeight, const size_t newWidth) {
	fb->contents = realloc(fb->contents, newWidth * newHeight * sizeof(char));
	fb->fgColors = realloc(fb->fgColors, newWidth * newHeight * sizeof(Color));
	fb->bgColors = realloc(fb->bgColors, newWidth * newHeight * sizeof(Color));
	fb->inputPrompt = realloc(fb->inputPrompt, newWidth * sizeof(char));
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
	size_t i;
	for (i = 0; i < fb->width * fb->height; i++) {
		fb->contents[i] = BLANK;
		fb->fgColors[i] = TRANSPARENT;
		fb->bgColors[i] = TRANSPARENT;
	}
	for (i = 0; i < fb->width; i++) fb->inputPrompt[i] = 0;
}

void FrameBuffer_drawPoint(FrameBuffer *fb, Point p, const char content, const Color fgColor, const Color bgColor) {
	if (p.r >= 0 && p.c >= 0 && p.r < fb->height && p.c < fb->width) {
		fb->contents[p.r*fb->width + p.c] = content;
		if (fgColor != TRANSPARENT) fb->fgColors[p.r*fb->width + p.c] = fgColor;
		if (bgColor != TRANSPARENT) fb->bgColors[p.r*fb->width + p.c] = bgColor;
	}
}

void FrameBuffer_drawHorizontalLine(FrameBuffer *fb, const Point p1, const Point p2, const char content, const Color fgColor, const Color bgColor) {
	int i1 = p1.c < p2.c ? p1.c : p2.c;
	int i2 = p1.c < p2.c ? p2.c : p1.c;
	int i;
	for (i = i1; i <= i2; i++) FrameBuffer_drawPoint(fb, Point_make(p1.r, i), content, fgColor, bgColor);
}

void FrameBuffer_drawVerticalLine(FrameBuffer *fb, const Point p1, const Point p2, const char content, const Color fgColor, const Color bgColor) {
	int i1 = p1.r < p2.r ? p1.r : p2.r;
	int i2 = p1.r < p2.r ? p2.r : p1.r;
	int i;
	for (i = i1; i <= i2; i++) FrameBuffer_drawPoint(fb, Point_make(i, p1.c), content, fgColor, bgColor);
}

void FrameBuffer_drawTextBox(FrameBuffer *fb, const Point topLeft, const Point bottomRight, const char *str, const Color fgColor, const Color bgColor) {
	if (str) {
		int r, c;
		size_t slen = StringUtils_strlen(str);
		if (slen > 0) {
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
					if (str[it] == '\n') break;
				}
			}
		}
	}
}

void FrameBuffer_drawRectangle(FrameBuffer *fb, Point topLeft, Point bottomRight, const char borderCharacter, Color textColor, Color bgColor, Color borderColor) {
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

void FrameBuffer_setInputPrompt(FrameBuffer *fb, const char *str) {
	if (fb->width >= 2) {
		StringUtils_strncpy(fb->inputPrompt, str, fb->width - 2);
		fb->inputPrompt[fb->width-1] = 0;
	}
}

void appendBuffer(char *buf, size_t *pos, const char *str) {
	sprintf(buf + *pos, "%s", str);
	*pos += StringUtils_strlen(str);
}

void appendBufferChar(char *buf, size_t *pos, const char c) {
	sprintf(buf + *pos, "%c", c);
	(*pos)++;
}

void FrameBuffer_output(FrameBuffer *fb, bool useColor) {
	useColor =  fb->supportsColor && useColor;
	clearScreen();
	int r, c;
	size_t it = 0;
	for (r = 0; r < fb->height; r++) {
		for (c = 0; c < fb->width; c++) {

			// Output color-specifying control characters
			if (useColor) {
				appendBuffer(fb->outputBuffer, &it, CS_INITIATOR);
				appendBuffer(fb->outputBuffer, &it, RESET);
				if (fb->fgColors[r*fb->width + c] != TRANSPARENT) {
					appendBuffer(fb->outputBuffer, &it, fgColorConstants[fb->fgColors[r*fb->width + c]]);
					appendBuffer(fb->outputBuffer, &it, ";");
				}
				if (fb->bgColors[r*fb->width + c] != TRANSPARENT) {
					appendBuffer(fb->outputBuffer, &it, bgColorConstants[fb->bgColors[r*fb->width + c]]);
				}
				appendBuffer(fb->outputBuffer, &it, CS_TERMINATOR);
			}

			// Output actual character to be printed
			appendBufferChar(fb->outputBuffer, &it, fb->contents[r*fb->width + c]);

			// Output reset control characters
			if (useColor) {
				appendBuffer(fb->outputBuffer, &it, CS_INITIATOR);
				appendBuffer(fb->outputBuffer, &it, RESET);
				appendBuffer(fb->outputBuffer, &it, ";");
				appendBuffer(fb->outputBuffer, &it, CS_TERMINATOR);
			}
		}

		// Output newline
		appendBufferChar(fb->outputBuffer, &it, '\n');
	}

	fb->outputBuffer[it] = 0; // Add trailing null byte to output buffer
	printf("%s%s", fb->outputBuffer, fb->inputPrompt); // Actually print the output buffer's contents and input prompt
}

/* Draws meter: 111/999 #####............ */
void FrameBuffer_drawMeter(FrameBuffer *fb, Point topLeft, int width, int value, int maxValue) {
    if (width < 8) width = 8; // Minimum width is 8 for the digits only
    char *valueStr = StringUtils_fromInt(value % 1000, "%03d");
    char *maxValueStr = StringUtils_fromInt(maxValue % 1000, "%03d");

    FrameBuffer_drawTextBox(fb, topLeft, Point_translate(topLeft, 0, 2), valueStr, WHITE, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_translate(topLeft, 0, 3), Point_translate(topLeft, 0, 3), "/", WHITE, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_translate(topLeft, 0, 4), Point_translate(topLeft, 0, 6), maxValueStr, WHITE, TRANSPARENT);

    Color barColor;
    if (value*3 < maxValue) barColor = MAROON;
    else if (value*2 < maxValue) barColor = BROWN;
    else if (value > maxValue) barColor = BLUE;
    else barColor = GREEN;

    if (value < 0) value = 0;
    if (value > maxValue) value = maxValue;
    if (maxValue > 0) {
        int barWidth = (value*(width-8)+(maxValue-1)) / maxValue; // Scale value to width-8, round up
        int remWidth = (width-8) - barWidth;
        if (barWidth > 0) FrameBuffer_drawHorizontalLine(fb, Point_translate(topLeft, 0, 8), Point_translate(topLeft, 0, 7+barWidth), '#', barColor, barColor);
        if (remWidth > 0) FrameBuffer_drawHorizontalLine(fb, Point_translate(topLeft, 0, 8+barWidth), Point_translate(topLeft, 0, 7+barWidth+remWidth), '.', GRAY, GRAY);
    }

    StringUtils_deallocate(valueStr);
    StringUtils_deallocate(maxValueStr);
}