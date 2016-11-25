#ifndef AREA_H
#define AREA_H

#include "point.h"
#include "array.h"
#include <stdio.h>

#define AREA_EMPTY_CELL '.'
#define AREA_INVALID_CELL 0

typedef struct {
	char *grid;
	char *areaName;
	size_t height;
	size_t width;
} Area;

typedef ARRAY(Area) AreaArray;

void Area_load(Area *area, FILE *fin);

void AreaArray_load(AreaArray *areas, FILE *fin);

char Area_getCell(const Area *area, Point point);

void Area_deallocate(Area *area);

void AreaArray_deallocate(AreaArray *areas);

#endif
