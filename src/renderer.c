#include "renderer.h"
#include "skilltreerenderer.h"

void Renderer_render(FrameBuffer *fb, const GameState *gameState, const GameResources *gameResources) {
	FrameBuffer_clear(fb);

	// if (gameState->gamePhase == SKILLTREE) {
		SkillTreeRenderer_render(fb, gameState, &(gameResources->skillTree));
	// }
	
	FrameBuffer_output(fb, true);
}
