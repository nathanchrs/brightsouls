#ifndef MAINMENU_H
#define MAINMENU_H

#include "boolean.h"
#include "gamestate.h"
#include "config.h"

void MainMenu_showSplashScreen(const Config *config);

void MainMenu_show(const bool isGameRunning, const Config *config);

void MainMenu_processInput(GameState *gameState, bool *isGameRunning, bool *exitGame, const char *input);

#endif