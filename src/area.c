#include "area.h"
#include "stringutils.h"
#include <stdlib.h>

void Area_load(Area *area, FILE *fin){
	/* Read area name */
	StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
	area->areaName = StringUtils_scan(fin, STRINGUTILS_NEWLINE);

	/* Read area height and width */
	int h, w;
	fscanf(fin, "%d%d", &h, &w);
	area->height = h;
	area->width = w;
	StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);

	/* Read area grid contents */
	area->grid = malloc(area->height * area->width * sizeof(char));
	if (area->grid) {
		int r, c;
		for (r = 0; r < area->height; r++) {
			StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
			char *inp = StringUtils_scan(fin, STRINGUTILS_WHITESPACE);
			size_t slen = StringUtils_strlen(inp);
			for (c = 0; c < area->width && c < slen; c++) {
				area->grid[r*(area->width) + c] = inp[c];
			}

			/* Fill in missing cells with invalid cell character */
			while (c < area->width) {
				area->grid[r*(area->width) + c] = AREA_INVALID_CELL;
				c++;
			}

			StringUtils_deallocate(inp);
		}
	} else {
		Area_deallocate(area); /* Clean up on allocation failure */
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
