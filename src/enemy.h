#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include "boolean.h"
#include "list.h"
#include "array.h"
#include "location.h"

typedef struct {
	char *name;

	int hp;
	int str;
	int def;
	int exp;

	MoveQueueStack moves;
} EnemyType;

typedef struct {
	int typeId;
	Location location;
} Enemy;

typedef ARRAY(Enemy) EnemyArray;
typedef ARRAY(EnemyType) EnemyTypeArray;

void EnemyTypeArray_load(EnemyTypeArray *enemyTypes, FILE *fin);

void EnemyArray_load(EnemyArray *enemies, FILE *fin);

void EnemyTypeArray_deallocate(EnemyTypeArray *enemyTypes);

void EnemyArray_deallocate(EnemyArray *enemies);

#endif