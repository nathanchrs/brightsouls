#include "core.h"
#include "stringutils.h"
#include "skilltree.h"
#include "boolean.h"
#include "location.h"
#include "player.h"
#include "battle.h"

void Core_exploration(GameState *gameState, GameResources *gameResources, const char *input) {
	Location ltemp;
	int i;

	if (StringUtils_strcmpi(input, "GU")) {
		ltemp = Location_moveUp(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if(StringUtils_strcmpi(input, "GD")) {
		ltemp = Location_moveDown(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if(StringUtils_strcmpi(input, "GL")) {
		ltemp = Location_moveLeft(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if(StringUtils_strcmpi(input, "GR")) {
		ltemp = Location_moveRight(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	}

	i = 0;
	while (i < gameResources->enemies.length) {
		if (Location_isEqual(ltemp, gameResources->enemies.items[i].location)) {
			// Battle_init(&battle, &(gameResources->enemies.items[i]), &(gameState->player));
		}
	}

	i = 0;
	while (i < gameResources->powerUps.length) {
		if (Location_isEqual(ltemp, gameResources->powerUps.items[i].location)) {
			PowerUp_use(&(gameResources->powerUpTypes), &(gameResources->powerUps.items[i]), &(gameState->player));
		}
	}
}

void Core_process(GameState *gameState, GameResources *gameResources, const char *input) {
	if (gameState->currentPhase == SKILLTREE) {
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
	} else if (gameState->currentPhase == EXPLORATION) {
		Core_exploration(gameState, gameResources, input);
	}
}
