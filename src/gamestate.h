#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "boolean.h"
#include "array.h"
#include "location.h"
#include "enemy.h"
#include "powerup.h"
#include "io.h"
#include "battle.h"
#include "datetime.h"

typedef enum {
	EXPLORATION, BATTLE, CUTSCENE, SKILLTREE, GAMEOVER, CREDITS
} GamePhase;

typedef struct {
	DateTime lastSaveTime;

	bool requestInput;
	GamePhase currentPhase;
	char *message;

	LocationEdgeArray locationEdges;

	Player player;

	BoolArray isEnemyDefeated;
	BoolArray isPowerUpUsed;
	BoolArray isSkillUnlocked;
	Battle battle;

} GameState;

void GameState_load(GameState *gameState, FILE *fin);

void GameState_save(const GameState *gameState, FILE *fout);

void GameState_deallocate(GameState *gameState);

#endif