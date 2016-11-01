#ifndef COLOR_H
#define COLOR_H

#define CS_INITIATOR "\033["
#define CS_TERMINATOR "m"
#define RESET "0"

typedef enum {
	TRANSPARENT,

	BLACK,
	MAROON,
	GREEN,
	BROWN,
	DARK_BLUE,
	PURPLE,
	TEAL,
	WHITE,

	GRAY,
	RED,
	LIME,
	YELLOW,
	BLUE,
	PINK,
	CYAN,
	LIGHT_GRAY
} Color;

extern const char *fgColorConstants[];
extern const char *bgColorConstants[];

#endif