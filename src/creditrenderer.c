#include "creditrenderer.h"
#include "stringutils.h"

void CreditRenderer_render(FrameBuffer *fb, const GameState *gameState) {
    FrameBuffer_drawTextBox(fb, Point_make(4,56), Point_make(4,88), "CREDITS", WHITE, TRANSPARENT);
    FrameBuffer_drawRectangle(fb, Point_make(5,29), Point_make(24,88), ' ',RED, BLACK, TRANSPARENT); // box battle
    FrameBuffer_drawRectangle(fb, Point_make(6,30), Point_make(23,87), ' ',RED, WHITE, TRANSPARENT); // box battle

    char *buffer;
    int i=0,j;
    Point topleft;
    topleft = Point_make(7,37);
    buffer = "          _                      _";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "   _     /||                    ||\\     _";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "  ( }    \\||D                  C||/    { )";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "| /\\__,=_[_]      DEVELOPER     [_]_=,__/\\ |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "|_\\_  |----|                    |----|  _/_|";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "|  |/ |    |                    |    | \\|  |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }
    i++;
    buffer = "|  /_ |    |                    |    | _\\  |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topleft, i, j), buffer[j], BLACK, TRANSPARENT);
    }

    FrameBuffer_drawTextBox(fb, Point_make(17,35), Point_make(17,88), "  Jonathan Christopher               13515001", BLACK, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(18,35), Point_make(18,88), "  Nicholas Thie                      13515000", BLACK, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(19,35), Point_make(19,88), "  Ray Andrew                         13515073", BLACK, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(20,35), Point_make(20,88), "  Adnan Radja Maulana                13515000", BLACK, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(21,35), Point_make(21,88), "  Ahmad Belva                        13515000", BLACK, TRANSPARENT);

    FrameBuffer_drawTextBox(fb, Point_make(25,35), Point_make(25,88), "          Thank you for playing our game !     ", BLACK, TRANSPARENT);
    FrameBuffer_drawTextBox(fb, Point_make(26,34), Point_make(26,88), "   We welcome any criticism to improve our game !", BLACK, TRANSPARENT);

}
