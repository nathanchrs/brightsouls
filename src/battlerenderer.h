#ifndef BATTLERENDERER_H
#define BATTLERENDERER_H

#include "gamestate.h"
#include "gameresources.h"
#include "framebuffer.h"

void BattleRenderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources);

#endif