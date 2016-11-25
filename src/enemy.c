#include "enemy.h"
#include "stringutils.h"
#include "io.h"

void EnemyTypeArray_load(EnemyTypeArray *enemies, FILE *fin) {
	int n, i;
	char inp;
	Queue move;

	n = IO_readInteger(fin);
	Array_allocate(enemies, n);
	enemies->length = n;

	for (i = 0; i < n; i++) {
		enemies->items[i].name = IO_readString(fin);

		enemies->items[i].hp = IO_readInteger(fin);
		enemies->items[i].str = IO_readInteger(fin);
		enemies->items[i].def = IO_readInteger(fin);
		enemies->items[i].exp = IO_readInteger(fin);

		MoveQueueStack_load(&(enemies->items[i].moves), fin);
	}
}

void EnemyArray_load(EnemyArray *enemyTypes, FILE *fin) {
	int n, i;
	n = IO_readInteger(fin);
	Array_allocate(enemyTypes, n);
	enemyTypes->length = n;

	for (i = 0; i < n; i++) {
		enemyTypes->items[i].typeId = IO_readInteger(fin);
		enemyTypes->items[i].location.r = IO_readInteger(fin);
		enemyTypes->items[i].location.c = IO_readInteger(fin);
		enemyTypes->items[i].location.areaId = IO_readInteger(fin);
	}
}

void EnemyTypeArray_deallocate(EnemyTypeArray *enemyTypes) {
	int i;
	for (i = 0; i < enemyTypes->length; i++) {
		MoveQueueStack_deallocate(&(enemyTypes->items[i].moves));
	}
	Array_deallocate(enemyTypes);
}

void EnemyArray_deallocate(EnemyArray *enemies) {
	Array_deallocate(enemies);
}