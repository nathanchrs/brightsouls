#ifndef CORE_H
#define CORE_H

#include "gamestate.h"
#include "gameresources.h"

void Core_process(GameState *gameState, GameResources *gameResources, const char *input);

#endif