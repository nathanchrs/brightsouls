#include "enemy.h"
#include "stringutils.h"
#include "io.h"

void Enemy_loadArray(EnemyArray *enemies, FILE *fin) {
	int n, i;
	char inp;
	Queue move;

	n = IO_readInteger(fin);
	Array_allocate(enemies, n);
	enemies->length = n;

	for (i = 0; i < n; i++) {
		enemies->items[i].name = IO_readString(fin);
		enemies->items[i].type = IO_readInteger(fin);

		enemies->items[i].hp = IO_readInteger(fin);
		enemies->items[i].str = IO_readInteger(fin);
		enemies->items[i].def = IO_readInteger(fin);
		enemies->items[i].exp = IO_readInteger(fin);

		MoveQueue_loadStack(&(enemies->items[i].moves), fin);
	}
}
