#ifndef MAINMENU_H
#define MAINMENU_H

#include "boolean.h"
#include "gamestate.h"
#include "config.h"

void MainMenu_showSplashScreen(const Config *config);

void MainMenu_show(bool isGameRunning, const Config *config);

#endif