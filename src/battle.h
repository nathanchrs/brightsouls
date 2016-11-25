#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include "boolean.h"
#include "enemy.h"
#include "player.h"

typedef struct {
	EnemyType enemyType;
	int enemyCurrentHp;
	int enemyCurrentStr;
	int enemyCurrentDef;
	int enemyCurrentExp;
	MoveQueueStack enemyCurrentMoves;

	MoveQueue playerMoveQueue;

	int round;
	char *battleLog;
} Battle;

void Battle_load(Battle *battle, FILE *fin);

void Battle_save(const Battle *battle, FILE *fout);

void Battle_deallocate(Battle *battle);

void Battle_init(Battle *battle, const EnemyType *enemyType, Player *player);

#endif