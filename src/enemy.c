#include "enemy.h"
#include "stringutils.h"

void EnemyTypeArray_load(EnemyTypeArray *enemyTypes, FILE *fin) {
	int n, i;
	n = IO_readInteger(fin);
	Array_allocate(enemyTypes, n);
	enemyTypes->length = n;

	for (i = 0; i < n; i++) {
		enemyTypes->items[i].name = IO_readString(fin);

		enemyTypes->items[i].hp = IO_readInteger(fin);
		enemyTypes->items[i].str = IO_readInteger(fin);
		enemyTypes->items[i].def = IO_readInteger(fin);
		enemyTypes->items[i].exp = IO_readInteger(fin);

		MoveQueueStack_load(&(enemyTypes->items[i].moves), fin);

		enemyTypes->items[i].image = IO_readString(fin);
	}
}

void EnemyArray_load(EnemyArray *enemies, FILE *fin) {
	int n, i;
	n = IO_readInteger(fin);
	Array_allocate(enemies, n);
	enemies->length = n;

	for (i = 0; i < n; i++) {
		enemies->items[i].typeId = IO_readInteger(fin);
		enemies->items[i].location.point.r = IO_readInteger(fin);
		enemies->items[i].location.point.c = IO_readInteger(fin);
		enemies->items[i].location.areaId = IO_readInteger(fin);
	}
}

/* Returns the index where an Enemy with the specified location is found, or -1 otherwise */
int EnemyArray_searchLocation(const EnemyArray *enemies, Location loc) {
	int i;
	for (i = 0; i < enemies->length; i++) {
		if (Location_isEqual(enemies->items[i].location, loc)) {
			return i;
		}
	}
	return -1;
}

void EnemyTypeArray_deallocate(EnemyTypeArray *enemyTypes) {
	int i;
	for (i = 0; i < enemyTypes->length; i++) {
		MoveQueueStack_deallocate(&(enemyTypes->items[i].moves));
		StringUtils_deallocate(enemyTypes->items[i].image);
	}
	Array_deallocate(enemyTypes);
}

void EnemyArray_deallocate(EnemyArray *enemies) {
	Array_deallocate(enemies);
}