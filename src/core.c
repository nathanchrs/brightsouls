#include "core.h"
#include "stringutils.h"
#include "skilltree.h"
#include "boolean.h"
#include "location.h"
#include "player.h"
#include "battle.h"

void Core_exploration(GameState *gameState, GameResources *gameResources, const char *input) {
	Location ltemp;

	if (StringUtils_strcmpi(input, "u") == 0) {
		ltemp = Location_moveUp(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if (StringUtils_strcmpi(input, "d") == 0) {
		ltemp = Location_moveDown(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if (StringUtils_strcmpi(input, "l") == 0) {
		ltemp = Location_moveLeft(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if (StringUtils_strcmpi(input, "r") == 0) {
		ltemp = Location_moveRight(gameState->player.location, &(gameResources->areas), &(gameState->locationEdges));
	} else if (StringUtils_strcmpi(input, "skilltree") == 0) {
		gameState->currentPhase = SKILLTREE;
		return;
	} else {
		gameState->message = StringUtils_clone("Invalid command.");
		return;
	}

	int enemyId = EnemyArray_searchLocation(&(gameResources->enemies), ltemp);
	if (enemyId >= 0 && !gameState->isEnemyDefeated.items[enemyId]) {
		// Enter battle
		Battle_init(&(gameState->battle), &(gameResources->enemies), &(gameResources->enemyTypes), enemyId);
		gameState->currentPhase = BATTLE;
		return; // Don't move to next location if entering battle
	}

	if (Location_isEqual(ltemp, gameState->player.location)) {
		gameState->message = StringUtils_clone("Can't go that way...");
	} else {
		int powerUpId = PowerUpArray_searchLocation(&(gameResources->powerUps), ltemp);
		if (powerUpId >= 0 && !gameState->isPowerUpUsed.items[powerUpId]) {
			PowerUp_use(&(gameResources->powerUpTypes), &(gameResources->powerUps.items[powerUpId]), &(gameState->player));
			gameState->isPowerUpUsed.items[powerUpId] = true;
			gameState->message = StringUtils_clone("Power up!");
		}

		gameState->player.location = ltemp;
	}
}

void Core_battle(GameState *gameState, GameResources *gameResources, const char *input) {
	if (gameState->battle.currentPhase == BATTLE_PLAYER_WIN) {
		gameState->isEnemyDefeated.items[gameState->battle.enemyId] = true;
		gameState->currentPhase = EXPLORATION;
		gameState->message = StringUtils_clone("You won the battle!");

	} else if (gameState->battle.currentPhase == BATTLE_ENEMY_WIN) {
		gameState->currentPhase = GAMEOVER;
		gameState->message = StringUtils_clone("You died.");

	} else if (gameState->battle.currentPhase == BATTLE_DRAW) {
		gameState->currentPhase = EXPLORATION;
		gameState->message = StringUtils_clone("You failed to defeat the enemy; the enemy has recovered!");

	} else { // BATTLE_ONGOING

		if (StringUtils_strcmpi(input, "a") == 0) {
			List_pushLast(&(gameState->battle.playerMoveQueue), 'A');
		} else if (StringUtils_strcmpi(input, "b") == 0) {
			List_pushLast(&(gameState->battle.playerMoveQueue), 'B');
		} else if (StringUtils_strcmpi(input, "f") == 0) {
			List_pushLast(&(gameState->battle.playerMoveQueue), 'F');
		} else if (gameState->battle.playerMoveQueue.length > 0 && (StringUtils_strcmpi(input, "e") == 0 || StringUtils_strcmpi(input, "erase") == 0)) {
			char ign;
			List_popLast(&(gameState->battle.playerMoveQueue), &ign);
			gameState->message = StringUtils_clone("Erased last move.");
		} else {
			gameState->message = StringUtils_clone("Invalid input.");
		}

		if (gameState->battle.playerMoveQueue.length >= MOVE_QUEUE_LENGTH) {
			Battle_calcMove(&(gameState->battle), &(gameState->player));
		}
	}
}

void Core_process(GameState *gameState, GameResources *gameResources, const char *input) {
	// Clear message
	StringUtils_deallocate(gameState->message);
	gameState->message = StringUtils_clone("");

	if (gameState->currentPhase == SKILLTREE) {
		if (StringUtils_strcmpi(input, "back") == 0) {
			gameState->currentPhase = EXPLORATION;
		} else {
			bool skillUnlocked = SkillTree_unlockSkill(&(gameResources->skillTree), gameState, input);
			if (skillUnlocked) {
				gameState->message = StringUtils_clone("Skill unlocked!");
			} else {
				gameState->message = StringUtils_clone("Can't unlock the specified skill.");
			}
		}
	} else if (gameState->currentPhase == EXPLORATION) {
		Core_exploration(gameState, gameResources, input);

	} else if (gameState->currentPhase == BATTLE) {
		Core_battle(gameState, gameResources, input);
	}
}
