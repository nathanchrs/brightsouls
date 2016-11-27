#include "battlerenderer.h"
#include "stringutils.h"
#include "framebuffer.h"
#include <stdio.h>
#include "move.h"
#include "utilities.h"

#define ENEMY_BOSS "BEELZEBUB"
#define ENEMY_CREEP1 "CROCS"


void BattleRenderer_drawPlayer(FrameBuffer *fb, Point topLeft) {
    char *buffer;
    int i=0,j;
    buffer = "            _A";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "          .'`\"`'.";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "         /        \\ ";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "        |         |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "        |         |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "        /         \\";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "       (.---._ _.-.)";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "        |         |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "        (         |\\";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "         \\        ;";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "         |\\      /";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "      _.'\\ |_____/ '-.";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "  _.-'              ` .";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = " /  \\                  \\";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "|    \\                  |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
}

void BattleRenderer_drawEnemy(FrameBuffer *fb, Point topLeft, int type) {
    char *buffer;
    int i=0,j;
    if(type < 6) {
            buffer = "    ____";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "   /....)";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "   |^  ^ \\";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "   <^   ^ >";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "   |^    ^\\\\_-_";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "   i^     ^ \\^/\\";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "   +' (@)  _\\  7";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "  / ..   _ -'  |";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = " / ..  _~  _'  |";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "i    _~_.-\\    |";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "I--~~_~  .|    |";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = " ~~'| ''' |  _ |";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "   /|-___-| | ||";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
    } else {
            buffer = "        /-/--\\";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "      (@~@)   )/\\";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "  ___/--      \\  |";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = " (oo)__ _      )_/";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "  ^^___/       \\   ";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "        \\       |/-\\   ";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "         (      )   |";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
            i++;
            buffer = "         |       \\_/ ";
            for(j=0; j<StringUtils_strlen(buffer); j++) {
                FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
            }
    }

}

void BattleRenderer_drawBoss(FrameBuffer *fb, Point topLeft) {
    char *buffer;
    int i=0,j;
    buffer = "                                                                _";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "                                                              _( (~\\";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "       _ _                        /                          ( \\> > \\";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "   -/~/ / ~\\                     :;                \\       _  > /(~\\/";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "  || | | /\\ ;\\                   |l      _____     |;     ( \\/    > >";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "  _\\)\\)\\)/ ;;;                  `8o __-~     ~\\   d|      \\      //";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = " ///(())(__/~;;\\                  \"88p;.  -. _\\_;.oP        (_._/ /";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "(((__   __ \\   \\                  `>,%% (\\  (\\./)8\"         ;:'  i";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = ")))--`.'-- (( ;,8 \\               ,;%%%%%%:  ./V^^^V'          ;.   ;.";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = "((\\   |   /)) .,88  `: ..,,;;;;,-::::::'_::\\   ||\\         ;[8:   ;";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = " )|  ~-~  |(|(888; ..``'::::8888oooooo.  :\\`^^^/,,~--._    |88::  |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = " |\\ -===- /|  \\8;; ``:.      oo.8888888888:`((( o.ooo8888Oo;:;:'  |";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = " |_~-___-~_|   `-\\.   `        `o`88888888b` )) 888b88888P\"\"'     ;";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
    i++;
    buffer = " ; ~~~~;~~         \"`--_`.       b`888888888;(.,\"888b888\"  ..::;-'";
    for(j=0; j<StringUtils_strlen(buffer); j++) {
        FrameBuffer_drawPoint(fb, Point_translate(topLeft, i, j), buffer[j], CYAN, TRANSPARENT);
    }
}

void BattleRenderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources) {

    int i, j; // hpbar player
    char tmp, *cpy, hp[11], maxHp[11], *st = " / ", stats[11], *move;
    snprintf(hp, 10, "%d", gameState->player.hp);
    snprintf(maxHp, 10, "%d", gameState->player.maxHp);

    cpy = StringUtils_clone("");
    StringUtils_concat(&cpy, st);
    StringUtils_concat(&cpy, maxHp);

    if(gameState->battle.enemyTypeId == 0) {
        i = gameState->player.hp * 24 / gameState->player.maxHp;
        if(i>0) {
            FrameBuffer_drawHorizontalLine(fb, Point_make(23,92), Point_make(23,92+i), ' ', RED, RED); // HP BAR
        }
        FrameBuffer_drawRectangle(fb, Point_make(1,0), Point_make(29,118), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); // box battle
        FrameBuffer_drawRectangle(fb, Point_make(19,89), Point_make(29,118), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); // box stats player
        BattleRenderer_drawBoss(fb,Point_make(2,40)); // drawboss

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
    } else {
        i = gameState->player.hp * 25 / gameState->player.maxHp;
        if(i>0) {
            FrameBuffer_drawHorizontalLine(fb, Point_make(23,42), Point_make(23,42+i), ' ', RED, RED); // HP BAR
        }
        FrameBuffer_drawRectangle(fb, Point_make(1,0), Point_make(29,70), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); //box battle
        FrameBuffer_drawRectangle(fb, Point_make(19,39), Point_make(29,70), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); //box stats player
        BattleRenderer_drawEnemy(fb,Point_make(2,40),  getRandomInt(1,10)); // rand enemy

        FrameBuffer_drawRectangle(fb, Point_make(22,41), Point_make(24,68), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); // box hpbar player

        FrameBuffer_drawTextBox(fb,Point_make(21,44), Point_make(21,49), "100", TRANSPARENT, TRANSPARENT);
        FrameBuffer_drawTextBox(fb,Point_make(25,44), Point_make(25,49), "100", TRANSPARENT, TRANSPARENT);
        FrameBuffer_drawTextBox(fb,Point_make(26,44), Point_make(26,49), "100", TRANSPARENT, TRANSPARENT);

        FrameBuffer_drawTextBox(fb,Point_make(20,44), Point_make(20,116), gameState->player.name, TRANSPARENT, TRANSPARENT);
        FrameBuffer_drawTextBox(fb,Point_make(21,44), Point_make(21,54), "HP       =", TRANSPARENT, TRANSPARENT);
        FrameBuffer_drawTextBox(fb,Point_make(21,56), Point_make(21,116), cpy, TRANSPARENT, TRANSPARENT);

        FrameBuffer_drawTextBox(fb,Point_make(25,44), Point_make(25,54), "Strength = ", TRANSPARENT, TRANSPARENT);
        snprintf(stats,10, "%d", gameState->player.str);
        FrameBuffer_drawTextBox(fb,Point_make(25,56), Point_make(25,68), stats, TRANSPARENT, TRANSPARENT);
        FrameBuffer_drawTextBox(fb,Point_make(26,44), Point_make(26,54), "Defence  = ", TRANSPARENT, TRANSPARENT);
        snprintf(stats,10, "%d", gameState->player.def);
        FrameBuffer_drawTextBox(fb,Point_make(26,56), Point_make(26,68), stats, TRANSPARENT, TRANSPARENT);
        FrameBuffer_drawTextBox(fb,Point_make(27,44), Point_make(27,54), "Exp      = ", TRANSPARENT, TRANSPARENT);
        snprintf(stats,10, "%d", gameState->player.exp);
        FrameBuffer_drawTextBox(fb,Point_make(27,56), Point_make(27,68), stats, TRANSPARENT, TRANSPARENT);
        /*

        for (j = 0; j < gameState->player.moveQueue.length; j++) {
            List_popFirst(&(gameState->player.moveQueue), &tmp);
            move = StringUtils_append(move,tmp);
            move = StringUtils_append(move, ' ');
            List_pushLast(&(gameState->player.moveQueue), tmp);
        }
        */
        //FrameBuffer_drawTextBox(fb,Point_make(28,56), Point_make(28,68), move, TRANSPARENT, TRANSPARENT);
        StringUtils_deallocate(cpy);
        //StringUtils_deallocate(move);
    }
    //i = gameState->battle.enemyHp * 24 / gameResources->enemyTypes.items[gameState->battle.enemyTypeId].hp;


    BattleRenderer_drawPlayer(fb, Point_make(13,5));
    /*enemy box*/
    FrameBuffer_drawRectangle(fb, Point_make(1,0), Point_make(10,30), '*',TRANSPARENT, TRANSPARENT, TRANSPARENT); // box enemy static
    /* enemy stats */
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
    /*end of enemy box */
    FrameBuffer_setInputPrompt(fb, "Command [a,b,f,e] >> ");
}