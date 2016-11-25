#include "area.h"
#include "io.h"
#include "stringutils.h"

void Area_load(Area *area, FILE *fin){
	/* Read area name and size */
	area->areaName = IO_readString(fin);
	area->height = IO_readInteger(fin);
	area->width = IO_readInteger(fin);

	/* Read area grid contents */
	area->grid = malloc(area->height * area->width * sizeof(char));
	if (area->grid) {
		int r, c;
		for (r = 0; r < area->height; r++) {
			IO_discardCharacters(fin, IO_WHITESPACE);
			char *inp = StringUtils_scan(fin, IO_WHITESPACE);
			size_t slen = StringUtils_strlen(inp);
			for (c = 0; c < area->width && c < slen; c++) {
				area->grid[r*(area->width) + c] = inp[c];
			}

			StringUtils_deallocate(inp);
		}
	} else {
		Area_deallocate(area); /* Clean up on allocation failure */
	}
}

void AreaArray_load(AreaArray *areas, FILE *fin) {
	int n, i;
	n = IO_readInteger(fin);
	Array_allocate(areas, n);
	areas->length = n;
	for (i = 0; i < n; i++) {
		Area_load(&(areas->items[i]), fin);
	}
}

char Area_getCell(const Area *area, Point point) {
	if (point.r >= 0 && point.r < area->height && point.c >= 0 && point.c < area->width) {
		return area->grid[point.r * (area->width) + point.c];
	} else {
		return AREA_INVALID_CELL;
	}
}

void Area_deallocate(Area *area) {
	free(area->grid);
	StringUtils_deallocate(area->areaName);
}

void AreaArray_deallocate(AreaArray *areas) {
	int i;
	for (i = 0; i < areas->length; i++) {
		Area_deallocate(&(areas->items[i]));
	}
	Array_deallocate(areas);
}