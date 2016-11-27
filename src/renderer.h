#ifndef RENDERER_H
#define RENDERER_H

#include "gamestate.h"
#include "gameresources.h"
#include "boolean.h"
#include "framebuffer.h"

void Renderer_render(FrameBuffer *fb, GameState *gameState, const GameResources *gameResources);

#endif