#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "boolean.h"
#include "array.h"
#include "location.h"

typedef enum {
	EXPLORATION, BATTLE, CUTSCENE, SKILLTREE, GAMEOVER, CREDITS
} GamePhase;

typedef struct {
	// DateTime lastSaveTime;

	bool requestInput;
	GamePhase currentPhase;
	char *message;

	ARRAY(LocationEdge) locationEdges;
	
/*
	Player player;

	Enemy *enemies;
	PowerUp *powerUps;

	AreaMap areaMap;
	Battle currentBattle;
*/
	ARRAY(bool) isSkillUnlocked;
	
} GameState;

bool GameState_load(GameState *gameState, const char *filePath);

void GameState_save(const GameState *gameState, const char *filePath);

void GameState_deallocate(GameState *gameState);

#endif