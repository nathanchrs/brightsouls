#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>

typedef struct {
	size_t frameBufferWidth;
	size_t frameBufferHeight;
	bool useColor;
} Config;

#endif