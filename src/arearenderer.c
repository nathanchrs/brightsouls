#include "arearenderer.h"
#include "area.h"
#include "point.h"
#include "location.h"

#define AREA_RENDER_BORDER 2
#define AREA_TOP_PADDING 5

void AreaRenderer_drawBlankCell(FrameBuffer *fb, Point topLeft) {
	int i;
	for (i = 0; i<=4; i++) FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, i), '_', GRAY, TRANSPARENT);
	for (i = 0; i<=2; i++) {
		FrameBuffer_drawPoint(fb, Point_translate(topLeft, i+1, i), '\\', GRAY, TRANSPARENT);
		FrameBuffer_drawPoint(fb, Point_translate(topLeft, i+1, i+5), '\\', GRAY, TRANSPARENT);
	}
	for (i = 3; i<=6; i++) FrameBuffer_drawPoint(fb, Point_translate(topLeft, 3, i), '_', GRAY, TRANSPARENT);
}

void AreaRenderer_drawWaterCell(FrameBuffer *fb, Point topLeft) {
	int i, j;
	for (i = 1; i<=3; i++) {
		for (j = 0; j<=4; j++) FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, i+j), '~', BLUE, TRANSPARENT);
	}
}

void AreaRenderer_drawTree(FrameBuffer *fb, Point topLeft) {
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, 1), '^', LIME, GREEN);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, 2), '^', LIME, GREEN);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 0), '^', LIME, GREEN);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 1), '^', LIME, GREEN);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 2), '^', LIME, GREEN);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 3), '^', LIME, GREEN);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 2, 1), ']', BROWN, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 2, 2), '[', BROWN, TRANSPARENT);
}

void AreaRenderer_drawPlayer(FrameBuffer *fb, Point topLeft) {
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, 1), 'O', CYAN, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 0), '/', CYAN, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 1), '|', CYAN, TEAL);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 2), '\\', CYAN, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 2, 0), '/', CYAN, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 2, 2), '\\', CYAN, TRANSPARENT);
}

void AreaRenderer_drawEnemy(FrameBuffer *fb, Point topLeft) {
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, 0), '<', RED, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, 1), 'O', RED, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, 2), '>', RED, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 0), '/', RED, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 1), '|', RED, MAROON);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 2), '\\', RED, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 2, 0), '/', RED, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 2, 2), '\\', RED, TRANSPARENT);
}

void AreaRenderer_drawPowerUp(FrameBuffer *fb, Point topLeft) {
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 0, 1), '_', WHITE, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 0), '[', WHITE, TRANSPARENT);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 1), '+', RED, WHITE);
	FrameBuffer_drawPoint(fb, Point_translate(topLeft, 1, 2), ']', WHITE, TRANSPARENT);
}


void AreaRenderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources) {
	Area *currentArea = &(gameResources->areas.items[gameState->player.location.areaId]);

	// Draw background
	FrameBuffer_drawRectangle(fb, Point_make(0, 0), Point_make(fb->height-1, fb->width-1), BLANK, TRANSPARENT, BLACK, BLACK);

	int r, c;

	// Draw water cells
	for (r = currentArea->height-1; r >= 0; r--) {
		for (c = 0; c < currentArea->width; c++) {
			if (Area_getCell(currentArea, Point_make(r, c)) == 'w') {
				AreaRenderer_drawWaterCell(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING, r*3 + c*5 + AREA_RENDER_BORDER));
			}
		}
	}

	// Draw blank cells
	for (r = currentArea->height-1; r >= 0; r--) {
		for (c = 0; c < currentArea->width; c++) {
			if (Area_getCell(currentArea, Point_make(r, c)) == '.'
				|| Area_getCell(currentArea, Point_make(r, c)) == 't'
				|| Area_getCell(currentArea, Point_make(r, c)) == 'p'
				|| Area_getCell(currentArea, Point_make(r, c)) == 'e') {
				AreaRenderer_drawBlankCell(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING, r*3 + c*5 + AREA_RENDER_BORDER));
			}
		}
	}

	// Draw player, enemies and powerups
	for (r = 0; r < currentArea->height; r++) {
		for (c = 0; c < currentArea->width; c++) {
			if (Area_getCell(currentArea, Point_make(r, c)) == 'p') {
				AreaRenderer_drawPowerUp(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING + 1, r*3 + c*5 + AREA_RENDER_BORDER + 2));
			}
			if (Area_getCell(currentArea, Point_make(r, c)) == 'e') {
				AreaRenderer_drawEnemy(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING, r*3 + c*5 + AREA_RENDER_BORDER + 2));
			}
			if (Location_isEqual(Location_make(Point_make(r, c), gameState->player.location.areaId), gameState->player.location)) {
				AreaRenderer_drawPlayer(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING, r*3 + c*5 + AREA_RENDER_BORDER + 2));
			}
		}
	}

	// Draw trees
	for (r = 0; r < currentArea->height; r++) {
		for (c = 0; c < currentArea->width; c++) {
			if (Area_getCell(currentArea, Point_make(r, c)) == 't') {
				AreaRenderer_drawTree(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING, r*3 + c*5 + AREA_RENDER_BORDER + 2));
			}
		}
	}

	FrameBuffer_drawTextBox(fb, Point_make(AREA_RENDER_BORDER, AREA_RENDER_BORDER), Point_make(AREA_RENDER_BORDER, 30), currentArea->areaName, WHITE, TRANSPARENT);

	FrameBuffer_drawTextBox(fb, Point_make(fb->height-1,0), Point_make(fb->height-1, fb->width-1), gameState->message, WHITE, TRANSPARENT);
	FrameBuffer_setInputPrompt(fb, "Command [u/d/l/r/skilltree] >> ");
}