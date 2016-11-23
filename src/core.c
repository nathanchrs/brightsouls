#include "core.h"
#include "stringutils.h"
#include "skilltree.h"
#include "boolean.h"
#include "location.h"
#include "player.h"
#include "battle.h"


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

void Core_exploration(GameState *gameState, GameResources *gameResources, const char *input) {
	Location Ltemp;
	Battle battle;
	int i;
	if(gameState->currentPhase == EXPLORATION) {
		if(StringUtils_strcmpi(input,"GU")) {
			i=0;
			Ltemp = Location_moveUp(gameState->player->loc, &gameResources->areas, &gameState->locationEdges);
			while(i<gameState->enemies->length) {
				if(Location_isEqual(Ltemp, gameState->enemies->items[i].loc)) {
					Battle_init(&battle,gameState->enemies,gameState->enemies->items[i].id,gameState->player);
				}
			}
			i=0;
			while(i<gameState->powerUps->length) {
				if(Location_isEqual(Ltemp, gameState->powerUps->items[i].loc)) {
					Powerup_add(gameState->powerUps->items[i], gameState->player);
				}
			}
		} else if(StringUtils_strcmpi(input,"GD")) {
			i=0;
			Ltemp = Location_moveDown(gameState->player->loc, &gameResources->areas, &gameState->locationEdges);
			while(i<gameState->enemies->length) {
				if(Location_isEqual(Ltemp, gameState->enemies->items[i].loc)) {
					Battle_init(&battle,gameState->enemies,gameState->enemies->items[i].id,gameState->player);
				}
			}
			i=0;
			while(i<gameState->powerUps->length) {
				if(Location_isEqual(Ltemp, gameState->powerUps->items[i].loc)) {
					Powerup_add(gameState->powerUps->items[i], gameState->player);
				}
			}
		} else if(StringUtils_strcmpi(input,"GL")) {
			i=0;
			Ltemp = Location_moveLeft(gameState->player->loc, &gameResources->areas, &gameState->locationEdges);
			while(i<gameState->enemies->length) {
				if(Location_isEqual(Ltemp, gameState->enemies->items[i].loc)) {
					Battle_init(&battle,gameState->enemies,gameState->enemies->items[i].id,gameState->player);
				}
			}
			i=0;
			while(i<gameState->powerUps->length) {
				if(Location_isEqual(Ltemp, gameState->powerUps->items[i].loc)) {
					Powerup_add(gameState->powerUps->items[i], gameState->player);
				}
			}
		} else if(StringUtils_strcmpi(input,"GR")) {
			i=0;
			Ltemp = Location_moveRight(gameState->player->loc, &gameResources->areas, &gameState->locationEdges);
			while(i<gameState->enemies->length) {
				if(Location_isEqual(Ltemp, gameState->enemies->items[i].loc)) {
					Battle_init(&battle,gameState->enemies,gameState->enemies->items[i].id,gameState->player);
				}
			}
			i=0;
			while(i<gameState->powerUps->length) {
				if(Location_isEqual(Ltemp, gameState->powerUps->items[i].loc)) {
					Powerup_add(gameState->powerUps->items[i], gameState->player);
				}
			}
		}
	}
}