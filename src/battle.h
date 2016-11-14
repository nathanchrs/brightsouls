#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include "boolean.h"
#include "stackt.h"

typedef struct {
	int enemyId;
	char *enemyName;
	char enemyType; //n : Normal, b : Boss

	int enemyHp;
	int enemyStr;
	int enemyDef;
	int enemyExp;

	Stack moveList;
	int moveCount; //n : 10, b : 20
	char enemyMovelist[20][4];
} Battle;

void Battle_load(Battle *battle, FILE *fin);

void Battle_save(const Battle *battle, FILE *fout);

void Battle_deallocate(Battle *battle);

void Battle_loadEnemy(Battle *battle, int eId);

void Battle_loadEnemyMove(Battle *battle);

#endif