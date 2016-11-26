#ifndef BATTLE_H
#define BATTLE_H

#include "io.h"
#include "boolean.h"
#include "enemy.h"
#include "player.h"
#include "move.h"

typedef struct {
	int round;
	int roundMax;
	char *battleLog;

	char *enemyName;
	int enemyHp;
	int enemyStr;
	int enemyDef;
	int enemyExp;
	MoveQueueStack enemyMoves;
	char *enemyMovesShow;
	char *enemyMovesHide;

	char *playerName;
	int playerHp;
	int playerStr;
	int playerDef;
	int playerExp;
	MoveQueue playerMoveQueue;
} Battle;

void Battle_load(Battle *battle, FILE *fin);

void Battle_save(const Battle *battle, FILE *fout);

void Battle_deallocate(Battle *battle);

void Battle_init(Battle *battle, const EnemyTypeArray *enemyTypes, int enemyTypeId);

void Battle_calcMove(Battle *battle);

void Battle_calcAction(char enemyAction, char playerAction, Battle *battle);

void Battle_playerInput(Battle *battle);

char *Battle_enemyMovesShow(Battle *battle);

char *Battle_enemyMovesHide(Battle *battle);

#endif