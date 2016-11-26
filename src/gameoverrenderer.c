#include "gameoverrenderer.h"
#include "stringutils.h"

void GameoverRenderer_render(FrameBuffer *fb, const GameState *gameState) {

    FrameBuffer_drawRectangle(fb, Point_make(5,29), Point_make(24,88), ' ',RED, BLACK, TRANSPARENT); // box battle
     FrameBuffer_drawTextBox(fb, Point_make(7,55), Point_make(7,88), "GAME OVER", WHITE, TRANSPARENT);
    FrameBuffer_drawRectangle(fb, Point_make(8,30), Point_make(23,87), ' ',RED, WHITE, TRANSPARENT); // box battle

    char *buffer;
    int i=0,j;
    Point topleft;
    topleft = Point_make(12,37);
    buffer = "            Sorry, ";
    buffer = StringUtils_concat(buffer, gameState->player.name);
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    StringUtils_deallocate(buffer);
    i++;
    buffer = "             Your HP is 0 :(";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "        Please go back to main menu";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "to load a existing game or make a new game";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "                     :)";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "               Enjoy the game!";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;

    FrameBuffer_setInputPrompt(fb, "Command [exit] >> ");
}