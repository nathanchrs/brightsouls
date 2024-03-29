#include "renderer.h"
#include "skilltreerenderer.h"
#include "arearenderer.h"
#include "battlerenderer.h"
#include "creditrenderer.h"
#include "gameoverrenderer.h"

void Renderer_render(FrameBuffer *fb, GameState *gameState, const GameResources *gameResources) {
	FrameBuffer_clear(fb);

	if (gameState->currentPhase == EXPLORATION) {
		AreaRenderer_render(fb, gameState, gameResources);
	} else if (gameState->currentPhase == SKILLTREE) {
		SkillTreeRenderer_render(fb, gameState, &(gameResources->skillTree));
	} else if (gameState->currentPhase == BATTLE) {
		BattleRenderer_render(fb, gameState, gameResources);
	} else if (gameState->currentPhase == CREDITS) {
		CreditRenderer_render(fb, gameState);
	} else if (gameState->currentPhase == GAMEOVER) {
		GameoverRenderer_render(fb, gameState);
	}

	FrameBuffer_output(fb, true);
}
