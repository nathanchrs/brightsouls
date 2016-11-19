#ifndef AREARENDERER_H
#define AREARENDERER_H

#include "gamestate.h"
#include "gameresources.h"
#include "framebuffer.h"

void AreaRenderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources);

#endif