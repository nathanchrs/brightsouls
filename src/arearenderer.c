#include "arearenderer.h"
#include "area.h"
#include "point.h"
#include "location.h"
#include "stringutils.h"

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

void AreaRenderer_drawMeter(FrameBuffer *fb, Point topLeft, int width, int value, int maxValue) {
    if (width < 8) width = 8; // Minimum width is 8 for the digits only
    char *valueStr = StringUtils_fromInt(value % 1000, "%04d");
    char *maxValueStr = StringUtils_fromInt(maxValue % 1000, "%04d");

    FrameBuffer_drawTextBox(fb, topLeft, Point_translate(topLeft, 0, 2), valueStr, WHITE, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_translate(topLeft, 0, 3), Point_translate(topLeft, 0, 3), "/", WHITE, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_translate(topLeft, 0, 4), Point_translate(topLeft, 0, 6), maxValueStr, WHITE, TRANSPARENT);

    Color barColor;
    if (value*3 < maxValue) barColor = MAROON;
    else if (value*2 < maxValue) barColor = BROWN;
    else barColor = GREEN;

    if (value < 0) value = 0;
    if (maxValue > 0 && maxValue >= value) {
        int barWidth = (value*(width-8)+(maxValue-1)) / maxValue; // Scale value to width-8, round up
        int remWidth = (width-8) - barWidth;
        if (barWidth > 0) FrameBuffer_drawHorizontalLine(fb, Point_translate(topLeft, 0, 8), Point_translate(topLeft, 0, 7+barWidth), '#', barColor, barColor);
        if (remWidth > 0) FrameBuffer_drawHorizontalLine(fb, Point_translate(topLeft, 0, 8+barWidth), Point_translate(topLeft, 0, 7+barWidth+remWidth), '.', GRAY, GRAY);
    }

    StringUtils_deallocate(valueStr);
    StringUtils_deallocate(maxValueStr);
}

void AreaRenderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources) {
	Area *currentArea = &(gameResources->areas.items[gameState->player.location.areaId]);

	// Draw background
	FrameBuffer_drawRectangle(fb, Point_make(0, 0), Point_make(fb->height-1, fb->width-1), BLANK, TRANSPARENT, BLACK, BLACK);

	FrameBuffer_drawRectangle(fb, Point_make(4, fb->width-80), Point_make(20, fb->width-45), BLANK, TRANSPARENT, BLACK, WHITE);

	FrameBuffer_drawTextBox(fb, Point_make(4, fb->width-68), Point_make(4, fb->width-50), gameState->player.name, BLACK, TRANSPARENT);

	FrameBuffer_drawTextBox(fb, Point_make(6, fb->width-77), Point_make(6, fb->width-50), "HP = ", WHITE, TRANSPARENT);

	AreaRenderer_drawMeter(fb, Point_make(6,fb->width-72), 26, gameState->player.hp, gameState->player.maxHp);

	char *stats = StringUtils_clone("Strength     =    ");
	char *statnum = StringUtils_fromInt(gameState->player.str,"%d");
	FrameBuffer_drawTextBox(fb, Point_make(7, fb->width-77), Point_make(7, fb->width-50), StringUtils_concat(stats,statnum), WHITE, TRANSPARENT);
	StringUtils_deallocate(stats);
	StringUtils_deallocate(statnum);
	stats = StringUtils_clone("Defence      =    ");
	statnum = StringUtils_fromInt(gameState->player.def,"%d");
	FrameBuffer_drawTextBox(fb, Point_make(8, fb->width-77), Point_make(8, fb->width-50), StringUtils_concat(stats,StringUtils_fromInt(gameState->player.def,"%d")), WHITE, TRANSPARENT);
	StringUtils_deallocate(stats);
	StringUtils_deallocate(statnum);
	stats = StringUtils_clone("Exp          =    ");
	statnum = StringUtils_fromInt(gameState->player.exp,"%d");
	FrameBuffer_drawTextBox(fb, Point_make(9, fb->width-77), Point_make(9, fb->width-50), StringUtils_concat(stats,StringUtils_fromInt(gameState->player.exp,"%d")), WHITE, TRANSPARENT);
	StringUtils_deallocate(stats);
	StringUtils_deallocate(statnum);
	FrameBuffer_drawTextBox(fb, Point_make(10, fb->width-77), Point_make(10, fb->width-50), "Skill active =", WHITE, TRANSPARENT);

	int i;
	for(i=0;i< gameState->isSkillUnlocked.length; i++) {
		if(gameState->isSkillUnlocked.items[i] == 1) {
			FrameBuffer_drawTextBox(fb, Point_make(11+i, fb->width-77), Point_make(11+i, fb->width-50), StringUtils_concat("+ ",gameResources->skillTree.items[i].skillName), WHITE, TRANSPARENT);
		} else {
			FrameBuffer_drawTextBox(fb, Point_make(11+i, fb->width-77), Point_make(11+i, fb->width-50), StringUtils_concat("- ",gameResources->skillTree.items[i].skillName), GRAY, TRANSPARENT);
		}
	}

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

			int powerUpId = PowerUpArray_searchLocation(&(gameResources->powerUps), Location_make(Point_make(r, c), gameState->player.location.areaId));
			if (powerUpId >= 0 && !gameState->isPowerUpUsed.items[powerUpId]) {
				AreaRenderer_drawPowerUp(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING + 1, r*3 + c*5 + AREA_RENDER_BORDER + 2));
				continue;
			}

			int enemyId = EnemyArray_searchLocation(&(gameResources->enemies), Location_make(Point_make(r, c), gameState->player.location.areaId));
			if (enemyId >= 0 && !gameState->isEnemyDefeated.items[enemyId]) {
				AreaRenderer_drawEnemy(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING, r*3 + c*5 + AREA_RENDER_BORDER + 2));
				continue;
			}
			if (Location_isEqual(Location_make(Point_make(r, c), gameState->player.location.areaId), gameState->player.location)) {
				AreaRenderer_drawPlayer(fb, Point_make(r*3 + AREA_RENDER_BORDER + AREA_TOP_PADDING, r*3 + c*5 + AREA_RENDER_BORDER + 2));
				continue;
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
	FrameBuffer_setInputPrompt(fb, "Command [u/d/l/r/skilltree/pause] >> ");
}