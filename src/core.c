#include "core.h"
#include "stringutils.h"
#include "skilltree.h"
#include "boolean.h"

void Core_process(GameState *gameState, GameResources *gameResources, const char *input) {
	// if (gameState->currentPhase == SKILLTREE) {
		if (StringUtils_strcmpi(input, "exit") == 0) {
			gameState->currentPhase = EXPLORATION;
		} else {
			bool skillUnlocked = SkillTree_unlockSkill(&(gameResources->skillTree), gameState, input);
			if (skillUnlocked) {
				gameState->message = "Skill unlocked!";
			} else {
				gameState->message = "Can't unlock the specified skill.";
			}
		}
	// }
}