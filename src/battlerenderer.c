#include "battlerenderer.h"
#include "stringutils.h"
#include <stdio.h>
#include "move.h"
#include "utilities.h"

#define BATTLE_IMAGE_HEIGHT 15
#define BATTLE_IMAGE_WIDTH 25

void BattleRenderer_drawPlayer(FrameBuffer *fb, const GameResources *gameResources, Point topLeft) {
    Point bottomRight = Point_translate(topLeft, BATTLE_IMAGE_HEIGHT-1, BATTLE_IMAGE_WIDTH-1);
    FrameBuffer_drawTextBox(fb, topLeft, bottomRight, gameResources->playerImage, CYAN, TRANSPARENT);
}

void BattleRenderer_drawEnemy(FrameBuffer *fb, const GameResources *gameResources, Point topLeft, int typeId) {
    Point bottomRight = Point_translate(topLeft, BATTLE_IMAGE_HEIGHT-1, BATTLE_IMAGE_WIDTH-1);
    FrameBuffer_drawTextBox(fb, topLeft, bottomRight, gameResources->enemyTypes.items[typeId].image, MAROON, TRANSPARENT);
}

/* Draws meter: 111/999 #####............ */
void BattleRenderer_drawMeter(FrameBuffer *fb, Point topLeft, int width, int value, int maxValue) {
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

void BattleRenderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources) {

    // Draw background
    FrameBuffer_drawRectangle(fb, Point_make(0, 0), Point_make(fb->height-1, fb->width-1), BLANK, TRANSPARENT, BLACK, BLACK);

    // Draw player + stats
    
    FrameBuffer_drawRectangle(fb, Point_make(0,0), Point_make(27,34), '*', GRAY, TRANSPARENT, TRANSPARENT); // player box
    BattleRenderer_drawPlayer(fb, gameResources, Point_make(1,4));

    FrameBuffer_drawTextBox(fb, Point_make(18, 3), Point_make(18, 30), gameState->player.name, CYAN, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(20, 3), Point_make(20, 5), "HP ", WHITE, TRANSPARENT);
    BattleRenderer_drawMeter(fb, Point_make(20, 6), 26, gameState->player.hp, gameState->player.maxHp);

    // Draw enemy + stats

    FrameBuffer_drawRectangle(fb, Point_make(0,84), Point_make(27,119), '*', GRAY, TRANSPARENT, TRANSPARENT); // enemy box
    BattleRenderer_drawEnemy(fb, gameResources, Point_make(1,89), gameState->battle.enemyTypeId);

    FrameBuffer_drawTextBox(fb, Point_make(18, 87), Point_make(18, 114), gameState->battle.enemyName, MAROON, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(20, 87), Point_make(20, 89), "HP ", WHITE, TRANSPARENT);
    BattleRenderer_drawMeter(fb, Point_make(20, 90), 26, gameState->battle.enemyHp, gameResources->enemyTypes.items[gameState->battle.enemyTypeId].hp);
    
    FrameBuffer_drawRectangle(fb, Point_make(0,34), Point_make(24,84), '*', GRAY, TRANSPARENT, TRANSPARENT); // battleLog box
    FrameBuffer_drawRectangle(fb, Point_make(24,34), Point_make(27,84), '*', GRAY, TRANSPARENT, TRANSPARENT); // input box
   
    /*
    
    FrameBuffer_drawTextBox(fb,Point_make(20,92), Point_make(20,116), gameState->player.name, TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawTextBox(fb,Point_make(21,92), Point_make(21,102), "HP       =", TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawTextBox(fb,Point_make(21,104), Point_make(21,116), cpy, TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawRectangle(fb, Point_make(22,91), Point_make(24,116), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); // box hpbar player
    FrameBuffer_drawTextBox(fb,Point_make(25,92), Point_make(25,102), "Strength = ", TRANSPARENT, TRANSPARENT);
    snprintf(stats,10, "%d", gameState->player.str);
    FrameBuffer_drawTextBox(fb,Point_make(25,104), Point_make(25,117), stats, TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawTextBox(fb,Point_make(26,92), Point_make(26,102), "Defence  = ", TRANSPARENT, TRANSPARENT);
    snprintf(stats,10, "%d", gameState->player.def);
    FrameBuffer_drawTextBox(fb,Point_make(26,104), Point_make(26,117), stats, TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawTextBox(fb,Point_make(27,92), Point_make(27,102), "Exp      = ", TRANSPARENT, TRANSPARENT);
    snprintf(stats,10, "%d", gameState->player.exp);
    FrameBuffer_drawTextBox(fb,Point_make(27,104), Point_make(27,117), stats, TRANSPARENT, TRANSPARENT);
    StringUtils_deallocate(cpy);
    

        for (j = 0; j < gameState->player.moveQueue.length; j++) {
            List_popFirst(&(gameState->player.moveQueue), &tmp);
            move = StringUtils_append(move,tmp);
            move = StringUtils_append(move, ' ');
            List_pushLast(&(gameState->player.moveQueue), tmp);
        }
        
        //FrameBuffer_drawTextBox(fb,Point_make(28,56), Point_make(28,68), move, TRANSPARENT, TRANSPARENT);
        StringUtils_deallocate(cpy);
        //StringUtils_deallocate(move);
    }
    //i = gameState->battle.enemyHp * 24 / gameResources->enemyTypes.items[gameState->battle.enemyTypeId].hp;


    BattleRenderer_drawPlayer(fb, Point_make(13,5));
    
    FrameBuffer_drawRectangle(fb, Point_make(1,0), Point_make(10,30), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); // box enemy static
   
    FrameBuffer_drawRectangle(fb, Point_make(4,2), Point_make(6,28), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); // box hpbar enemy
    if(i>0) {
        FrameBuffer_drawHorizontalLine(fb, Point_make(5,3), Point_make(5,3+i), ' ', RED, RED); // HP BAR
    }

    FrameBuffer_drawTextBox(fb,Point_make(2,5), Point_make(2,10), gameResources->enemyTypes.items[gameState->battle.enemyTypeId].name, TRANSPARENT, TRANSPARENT);

    FrameBuffer_drawTextBox(fb,Point_make(3,5), Point_make(3,15), "HP       =", TRANSPARENT, TRANSPARENT);

    FrameBuffer_drawTextBox(fb,Point_make(7,5), Point_make(7,15), "Strength = ", TRANSPARENT, TRANSPARENT);
    snprintf(stats,10, "%d", gameState->battle.enemyStr);
    FrameBuffer_drawTextBox(fb,Point_make(7,17), Point_make(7,28), stats, TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawTextBox(fb,Point_make(8,5), Point_make(8,15), "Defence  = ", TRANSPARENT, TRANSPARENT);
    snprintf(stats,10, "%d", gameState->battle.enemyDef);
    FrameBuffer_drawTextBox(fb,Point_make(8,17), Point_make(8,28), stats, TRANSPARENT, TRANSPARENT);
    

    */

    FrameBuffer_setInputPrompt(fb, "Enter [a(ttack)/b(lock)/f(lank)], [e(rase)] or [pause] >> ");
}