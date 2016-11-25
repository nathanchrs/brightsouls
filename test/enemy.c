#include <assert.h>
#include <stdio.h>
#include "../src/stringutils.h"
#include "../src/enemy.h"

void testEnemy(const char *executableDirectory) {

	printf("  Testing Enemy...\n");

	Enemy enemy;

	FILE *fin = IO_openFile(executableDirectory, '../test/enemy.in');
	assert(fin != NULL);
	Enemy_load(&enemy, fin);
	IO_closeFile(fin);
	
	assert(enemy.length == 3);

	assert(StringUtils_strcmpi(enemy.items[0].name, "Enemy 1") == 0);
	assert(StringUtils_strcmpi(enemy.items[0].type, "normal") == 0);
	assert(enemy.items[0].moveCount == 10);
	assert(enemy.items[0].hp == 50);
	assert(enemy.items[0].str == 10);
	assert(enemy.items[0].def == 5);
	assert(enemy.items[0].exp == 25);
	int i, j;
	printf("Enemy 1 : \n");
	for (i=1; i<=enemy.items[0].moveCount; i++)
	{
		Queue move;
		DelVFirst(&(enemy.items[0].moveList), &move);
		printf("Move %d : ", i);
		for (j=0; j<4; j++)
		{
			char c;
			Queue_Del(&move, &c);
			printf("%c", c);
		}
		printf("\n");
	}

	assert(StringUtils_strcmpi(enemy.items[1].name, "Enemy 2") == 0);
	assert(StringUtils_strcmpi(enemy.items[1].type, "normal") == 0);
	assert(enemy.items[1].moveCount == 10);
	assert(enemy.items[1].hp == 50);
	assert(enemy.items[1].str == 10);
	assert(enemy.items[1].def == 5);
	assert(enemy.items[1].exp == 25);
	Enemy_randMovelist(&(enemy.items[1]));
	printf("Enemy 2 : \n");
	for (i=1; i<=enemy.items[1].moveCount; i++)
	{
		Queue move;
		DelVFirst(&(enemy.items[1].moveList), &move);
		printf("Move %d : ", i);
		for (j=0; j<4; j++)
		{
			char c;
			Queue_Del(&move, &c);
			printf("%c", c);
		}
		printf("\n");
	}

	assert(StringUtils_strcmpi(enemy.items[2].name, "Boss 1") == 0);
	assert(StringUtils_strcmpi(enemy.items[2].type, "boss") == 0);
	assert(enemy.items[2].moveCount == 20);
	assert(enemy.items[2].hp == 500);
	assert(enemy.items[2].str == 100);
	assert(enemy.items[2].def == 50);
	assert(enemy.items[2].exp == 250);
	printf("Boss 1 : \n");
	for (i=1; i<=enemy.items[2].moveCount; i++)
	{
		Queue move;
		DelVFirst(&(enemy.items[2].moveList), &move);
		printf("Move %d : ", i);
		for (j=0; j<4; j++)
		{
			char c;
			Queue_Del(&move, &c);
			printf("%c", c);
		}
		printf("\n");
	}

	printf("  Enemy tested.\n");
}