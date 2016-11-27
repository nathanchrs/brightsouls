#ifndef BATTLE_H
#define BATTLE_H

#include "io.h"
#include "boolean.h"
#include "enemy.h"
#include "player.h"
#include "move.h"

typedef enum {
	BATTLE_ONGOING,
	BATTLE_PLAYER_WIN,
	BATTLE_ENEMY_WIN,
	BATTLE_DRAW
} BattlePhase;

typedef struct {
	int round;
	char *battleLog;
	BattlePhase currentPhase;

	char *enemyName;
	int enemyId;
	int enemyTypeId;
	int enemyHp;
	int enemyStr;
	int enemyDef;
	int enemyExp;
	MoveQueueStack enemyMoves;

	MoveQueue playerMoveQueue;
} Battle;

void Battle_load(Battle *battle, FILE *fin);

void Battle_save(const Battle *battle, FILE *fout);

void Battle_deallocate(Battle *battle);

void Battle_init(Battle *battle, const EnemyArray *enemies, const EnemyTypeArray *enemyTypes, int enemyId);

void Battle_calcMove(Battle *battle, Player *player);

void Battle_calcAction(char enemyAction, char playerAction, Battle *battle, Player *player);

void Battle_calcResult(Battle *battle, Player *player);

#endif