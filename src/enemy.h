#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include "boolean.h"
#include "listlinier.h"
#include "queuelist.h"

typedef struct {
	int id;
	char *name;
	char type; //n : Normal, b : Boss

	int hp;
	int str;
	int def;
	int exp;

	List moveList;
	int moveCount; //n : 10, b : 20
} Enemy;

void Enemy_load(Enemy *enemy, int eId/*, FILE *fin*/);

#endif