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

void BattleRenderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources) {
    ListNode *it;
    ListNode *firstNode;
    char tmp;
    int i;

    char *playerMoveStr = StringUtils_clone("");
    char *enemyMoveStr = StringUtils_clone("");

    char *playerStrStr = StringUtils_fromInt(gameState->player.str % 1000, "%03d");
    char *playerDefStr = StringUtils_fromInt(gameState->player.def % 1000, "%03d");
    char *playerLvlStr = StringUtils_fromInt(gameState->player.level % 1000, "%03d");

    char *enemyStrStr = StringUtils_fromInt(gameResources->enemyTypes.items[gameState->battle.enemyTypeId].str % 1000, "%03d");
    char *enemyDefStr = StringUtils_fromInt(gameResources->enemyTypes.items[gameState->battle.enemyTypeId].def % 1000, "%03d");
    char *enemyExpStr = StringUtils_fromInt(gameResources->enemyTypes.items[gameState->battle.enemyTypeId].exp % 1000, "%03d");

    // Draw background
    FrameBuffer_drawRectangle(fb, Point_make(0, 0), Point_make(fb->height-1, fb->width-1), BLANK, TRANSPARENT, BLACK, BLACK);

    // Draw player + stats
    
    FrameBuffer_drawRectangle(fb, Point_make(0,0), Point_make(27,34), '*', GRAY, TRANSPARENT, TRANSPARENT); // player box
    BattleRenderer_drawPlayer(fb, gameResources, Point_make(1,4));

    FrameBuffer_drawTextBox(fb, Point_make(18, 3), Point_make(18, 30), gameState->player.name, CYAN, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(20, 3), Point_make(20, 5), "HP ", WHITE, TRANSPARENT);
    BattleRenderer_drawMeter(fb, Point_make(20, 7), 26, gameState->player.hp, gameState->player.maxHp);

    FrameBuffer_drawTextBox(fb, Point_make(22, 3), Point_make(22, 5), "EXP", WHITE, TRANSPARENT);
    BattleRenderer_drawMeter(fb, Point_make(22, 7), 26, gameState->player.exp, gameState->player.maxExp);

    FrameBuffer_drawTextBox(fb, Point_make(24, 3), Point_make(24, 5), "STR", CYAN, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(24, 7), Point_make(24, 9), playerStrStr, WHITE, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(24, 12), Point_make(24, 14), "DEF", CYAN, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(24, 16), Point_make(24, 18), playerDefStr, WHITE, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(24, 21), Point_make(24, 23), "LVL", CYAN, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(24, 25), Point_make(24, 27), playerLvlStr, WHITE, TRANSPARENT);

    // Draw enemy + stats

    FrameBuffer_drawRectangle(fb, Point_make(0,84), Point_make(27,119), '*', GRAY, TRANSPARENT, TRANSPARENT); // enemy box
    BattleRenderer_drawEnemy(fb, gameResources, Point_make(1,89), gameState->battle.enemyTypeId);

    FrameBuffer_drawTextBox(fb, Point_make(18, 87), Point_make(18, 114), gameState->battle.enemyName, RED, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(20, 87), Point_make(20, 89), "HP ", WHITE, TRANSPARENT);
    BattleRenderer_drawMeter(fb, Point_make(20, 91), 26, gameState->battle.enemyHp, gameResources->enemyTypes.items[gameState->battle.enemyTypeId].hp);

    FrameBuffer_drawTextBox(fb, Point_make(22, 87), Point_make(24, 89), "STR", RED, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(22, 91), Point_make(24, 93), enemyStrStr, WHITE, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(22, 96), Point_make(24, 98), "DEF", RED, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(22, 100), Point_make(24, 102), enemyDefStr, WHITE, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(22, 105), Point_make(25, 107), "EXP", RED, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(22, 109), Point_make(25, 111), enemyExpStr, WHITE, TRANSPARENT);
    
    // Draw player input box

    // Iterate over moveQueue (circular list implementation)
    it = List_first(&(gameState->battle.playerMoveQueue));
    firstNode = it;
    if (it != NULL) {
        do {
            tmp = ListNode_value(it, char);
            StringUtils_appendChar(&playerMoveStr, tmp);
            StringUtils_appendChar(&playerMoveStr, ' ');
            it = ListNode_next(it);
        } while (it != firstNode);
    }

    FrameBuffer_drawRectangle(fb, Point_make(24,34), Point_make(27,59), '*', GRAY, TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(25, 36), Point_make(25, 57), "Player move:", CYAN, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(26, 50), Point_make(26, 57), playerMoveStr, WHITE, TRANSPARENT);

    // Draw enemy input box
    
    // Generate pseudo-random hide id's from round number and player stats
    // so the hidden index will not change even though the game is restarted
    int firstHideId = (gameState->battle.round + gameState->battle.enemyId*gameState->player.exp + gameState->player.str) % MOVE_QUEUE_LENGTH;
    int secondHideId = (firstHideId + (gameState->player.exp + gameState->player.str*gameState->player.def + gameState->battle.enemyId) % (MOVE_QUEUE_LENGTH-1) + 1) % MOVE_QUEUE_LENGTH;
    
    MoveQueue *enemyMoveQueuePtr = ListNode_valuePointer(List_first(&(gameState->battle.enemyMoves)));

    // Iterate over the first enemyMoveQueue
    it = List_first(enemyMoveQueuePtr);
    firstNode = it;
    i = 0;
    if (it != NULL) {
        do {
            tmp = ListNode_value(it, char);
            if (i == firstHideId || i == secondHideId) {
                StringUtils_appendChar(&enemyMoveStr, '#');
            } else {
                StringUtils_appendChar(&enemyMoveStr, tmp);
            }
            StringUtils_appendChar(&enemyMoveStr, ' ');
            it = ListNode_next(it);
            i++;
        } while (it != firstNode);
    }
    
    FrameBuffer_drawRectangle(fb, Point_make(24,59), Point_make(27,84), '*', GRAY, TRANSPARENT, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(25, 61), Point_make(25, 82), "Enemy move:", RED, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(26, 74), Point_make(26, 82), enemyMoveStr, WHITE, TRANSPARENT);
   
    // Draw battle log

    FrameBuffer_drawRectangle(fb, Point_make(0,34), Point_make(24,84), '*', GRAY, TRANSPARENT, TRANSPARENT); // battleLog box
    FrameBuffer_drawTextBox(fb, Point_make(2, 36), Point_make(22, 82), gameState->battle.battleLog, WHITE, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(fb->height-1,0), Point_make(fb->height-1, fb->width-1), gameState->message, WHITE, TRANSPARENT);

    if (gameState->battle.currentPhase == BATTLE_PLAYER_WIN) {
        FrameBuffer_setInputPrompt(fb, "You win! Press any key to continue or [pause] >> ");
    } else if (gameState->battle.currentPhase == BATTLE_ENEMY_WIN) {
        FrameBuffer_setInputPrompt(fb, "You are defeated. Press any key to continue or [pause] >> ");
    } else if (gameState->battle.currentPhase == BATTLE_DRAW) {
        FrameBuffer_setInputPrompt(fb, "It's a draw... press any key to continue or [pause] >> ");
    } else { // BATTLE_ONGOING
        FrameBuffer_setInputPrompt(fb, "Enter [a(ttack)/b(lock)/f(lank)], [e(rase)] or [pause] >> ");
    }

    StringUtils_deallocate(playerMoveStr);
    StringUtils_deallocate(enemyMoveStr);
    StringUtils_deallocate(playerStrStr);
    StringUtils_deallocate(playerDefStr);
    StringUtils_deallocate(playerLvlStr);
    StringUtils_deallocate(enemyStrStr);
    StringUtils_deallocate(enemyDefStr);
    StringUtils_deallocate(enemyExpStr);
}