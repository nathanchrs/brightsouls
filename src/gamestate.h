#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "boolean.h"
#include "stdio.h"

typedef enum {
	EXPLORATION, BATTLE, CUTSCENE, SKILLTREE, GAMEOVER, CREDITS
} GamePhase;

typedef struct {
	// DateTime lastSaveTime;

	bool requestInput;
	GamePhase currentPhase;
/*
	Player player;

	Enemy *enemies;
	PowerUp *powerUps;

	AreaMap areaMap;
	Battle currentBattle;
	bool *isSkillActive;
*/
} GameState;

void GameState_load(GameState *gameState, const char *filePath);

void GameState_save(const GameState *gameState, const char *filePath);

void GameState_deallocate(GameState *gameState);

#endif