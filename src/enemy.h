#ifndef ENEMY_H
#define ENEMY_H

#include "io.h"
#include "boolean.h"
#include "list.h"
#include "array.h"
#include "location.h"
#include "move.h"

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

/* Returns the index where an Enemy with the specified location is found, or -1 otherwise */
int EnemyArray_searchLocation(const EnemyArray *enemies, Location loc);

void EnemyTypeArray_deallocate(EnemyTypeArray *enemyTypes);

void EnemyArray_deallocate(EnemyArray *enemies);

#endif