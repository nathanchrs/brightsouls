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
	} else if(StringUtils_strcmpi(input, "restoration") == 0) {
		if(SkillTree_isSkillUnlocked(&(gameResources->skillTree),gameState, "Restoration")) {
			if(gameState->player.exp-20 < 0) {
				gameState->message = StringUtils_clone("Not enough exp");
			} else {
				gameState->player.hp = gameState->player.maxHp;
				gameState->player.exp -= 20;
			}
		} else {
			gameState->message = StringUtils_clone("Invalid command.");
		}
		return;
	} else if(StringUtils_strcmpi(input, "purification") == 0) {
		if(SkillTree_isSkillUnlocked(&(gameResources->skillTree),gameState, "Purification")) {
			if(gameState->player.exp-10 < 0) {
				gameState->message = StringUtils_clone("Not enough exp");
			} else {
				gameState->player.hp += 30;
				if(gameState->player.hp > gameState->player.maxHp) {
					gameState->player.hp = gameState->player.maxHp;
				}
				gameState->player.exp -= 10;
			}
		} else {
			gameState->message = StringUtils_clone("Invalid command.");
		}
		return;
	} else if(StringUtils_strcmpi(input, "healward") == 0) {
		if(SkillTree_isSkillUnlocked(&(gameResources->skillTree),gameState, "Healward")) {
			if(gameState->player.exp-3 < 0) {
				gameState->message = StringUtils_clone("Not enough exp");
			} else {
				gameState->player.hp += 10;
				if(gameState->player.hp > gameState->player.maxHp) {
					gameState->player.hp = gameState->player.maxHp;
				}
				gameState->player.exp -= 3;
			}
		} else {
			gameState->message = StringUtils_clone("Invalid command.");
		}
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
	/*if (Battle_getState(gameState->battle.round) == BATTLE_PLAYER_WIN) {
		gameState->isEnemyDefeated.items[enemyId] = true;
		gameState->currentPhase = EXPLORATION;
	} else if (Battle_getState(gameState->battle.round) == BATTLE_PLAYER_WIN) {

		gameState->currentPhase = GAMEOVER;
	}

	Battle_calcMove(gameState->battle, gameState->player);*/
}

void Core_process(GameState *gameState, GameResources *gameResources, const char *input) {
	// Clear message
	StringUtils_deallocate(gameState->message);
	gameState->message = StringUtils_clone("");

	if (gameState->currentPhase == SKILLTREE) {
		if (StringUtils_strcmpi(input, "back") == 0) {
			gameState->currentPhase = EXPLORATION;
		} else {
			int skillUnlocked = SkillTree_unlockSkill(&(gameResources->skillTree), gameState, input);
			bool skillAlreadyUnlocked = SkillTree_isSkillUnlocked(&(gameResources->skillTree), gameState, input);
			if(!skillAlreadyUnlocked) {
				if (skillUnlocked == SKILL_UNLOCKED) {
					gameState->message = StringUtils_clone("Skill unlocked!");
				} else {
					gameState->message = StringUtils_clone("Can't unlock the specified skill.");
				}
			} else {
					gameState->message = StringUtils_clone("You had already unlocked that skill before!");
			}
		}
	} else if (gameState->currentPhase == EXPLORATION) {
		Core_exploration(gameState, gameResources, input);

	} else if (gameState->currentPhase == BATTLE) {

	}
}
