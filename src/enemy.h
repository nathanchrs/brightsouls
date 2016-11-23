#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include "boolean.h"
#include "listlinier.h"
#include "queuelist.h"
#include "array.h"
#include "location.h"

typedef struct {
	int id;
	char *name;

	int hp;
	int maxHp;
	int str;
	int def;
	int exp;

	List moveList;
	int moveCount; //n : 10, b : 20
} EnemyType;

typedef struct {
	EnemyType type;
	Location location;
} Enemy;

typedef ARRAY(Enemy) EnemyArray;
typedef ARRAY(EnemyType) EnemyTypeArray;

void EnemyType_loadArray(EnemyTypeArray *enemyTypes, FILE *fin);

void Enemy_loadArray(EnemyArray *enemies, FILE *fin);

void Enemy_randMovelist(EnemyType *enemyType);

#endif