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

	if (StringUtils_strcmpi(input, "u") == 0) {
		ltemp = Location_moveUp(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if(StringUtils_strcmpi(input, "d") == 0) {
		ltemp = Location_moveDown(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if(StringUtils_strcmpi(input, "l") == 0) {
		ltemp = Location_moveLeft(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if(StringUtils_strcmpi(input, "r") == 0) {
		ltemp = Location_moveRight(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else {
		gameState->message = "Invalid command.";
		return;
	}

	int enemyId = EnemyArray_searchLocation(&(gameResources->enemies), ltemp);
	if (enemyId >= 0 && !gameState->isEnemyDefeated.items[enemyId]) {
		// Enter battle
		Battle_init(&(gameState->battle), &(gameResources->enemyTypes), gameResources->enemies.items[enemyId].typeId);
		// gameState->currentPhase = BATTLE;
		return; // Don't move to next location if entering battle
	}

	if (Location_isEqual(ltemp, gameState->player.location)) {
		gameState->message = "Can't go that way...";
	} else {
		for (i = 0; i < gameResources->powerUps.length; i++) {
			if (Location_isEqual(ltemp, gameResources->powerUps.items[i].location)) {
				PowerUp_use(&(gameResources->powerUpTypes), &(gameResources->powerUps.items[i]), &(gameState->player));
			}
		}

		gameState->player.location = ltemp;
	}
}

void Core_process(GameState *gameState, GameResources *gameResources, const char *input) {
	// Clear message
	gameState->message = "";

	if (gameState->currentPhase == SKILLTREE) {
		if (StringUtils_strcmpi(input, "back") == 0) {
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
