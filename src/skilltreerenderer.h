#ifndef SKILLTREERENDERER_H
#define SKILLTREERENDERER_H

#include "gamestate.h"
#include "gameresources.h"
#include "framebuffer.h"

void SkillTreeRenderer_render(FrameBuffer *fb, const GameState *gameState, const SkillTree *skillTree);

#endif