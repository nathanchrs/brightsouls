#include <assert.h>
#include <stdio.h>
#include "../src/stringutils.h"
#include "../src/enemy.h"

void testEnemy(const char *executableDirectory) {

	printf("  Testing Enemy...\n");

	EnemyTypeArray enemyType;

	FILE *fin = IO_openFile(executableDirectory, "../test/enemy.in");
	assert(fin != NULL);
	EnemyTypeArray_load(&enemyType, fin);
	IO_closeFile(fin);
	
	assert(enemyType.length == 2);

	assert(StringUtils_strcmpi(enemyType.items[0].name, "Jenis musuh 1") == 0);
	assert(enemyType.items[0].hp == 10);
	assert(enemyType.items[0].str == 9);
	assert(enemyType.items[0].def == 8);
	assert(enemyType.items[0].exp == 7);

	MoveQueue mq;
	List_initialize(&mq);	
	char m;

	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[0].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');

	assert(StringUtils_strcmpi(enemyType.items[1].name, "Jenis musuh kedua") == 0);
	assert(enemyType.items[1].hp == 11);
	assert(enemyType.items[1].str == 12);
	assert(enemyType.items[1].def == 13);
	assert(enemyType.items[1].exp == 14);

	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'B');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'F');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'F');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');
	List_popFirst(&(enemyType.items[1].moves), &mq);
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'B');
		List_popFirst(&mq, &m);
		assert(m == 'A');
		List_popFirst(&mq, &m);
		assert(m == 'A');

	/*
	int i, j;
	printf("Enemy 1 : \n");
	for (i=1; i<=enemyType.items[0].moveCount; i++)
	{
		Queue move;
		DelVFirst(&(enemyType.items[0].moveList), &move);
		printf("Move %d : ", i);
		for (j=0; j<4; j++)
		{
			char c;
			Queue_Del(&move, &c);
			printf("%c", c);
		}
		printf("\n");
	}

	assert(StringUtils_strcmpi(enemyType.items[1].name, "Enemy 2") == 0);
	assert(StringUtils_strcmpi(enemyType.items[1].type, "normal") == 0);
	assert(enemyType.items[1].moveCount == 10);
	assert(enemyType.items[1].hp == 50);
	assert(enemyType.items[1].str == 10);
	assert(enemyType.items[1].def == 5);
	assert(enemyType.items[1].exp == 25);
	Enemy_randMovelist(&(enemyType.items[1]));
	printf("Enemy 2 : \n");
	for (i=1; i<=enemyType.items[1].moveCount; i++)
	{
		Queue move;
		DelVFirst(&(enemyType.items[1].moveList), &move);
		printf("Move %d : ", i);
		for (j=0; j<4; j++)
		{
			char c;
			Queue_Del(&move, &c);
			printf("%c", c);
		}
		printf("\n");
	}

	assert(StringUtils_strcmpi(enemyType.items[2].name, "Boss 1") == 0);
	assert(StringUtils_strcmpi(enemyType.items[2].type, "boss") == 0);
	assert(enemyType.items[2].moveCount == 20);
	assert(enemyType.items[2].hp == 500);
	assert(enemyType.items[2].str == 100);
	assert(enemyType.items[2].def == 50);
	assert(enemyType.items[2].exp == 250);
	printf("Boss 1 : \n");
	for (i=1; i<=enemyType.items[2].moveCount; i++)
	{
		Queue move;
		DelVFirst(&(enemyType.items[2].moveList), &move);
		printf("Move %d : ", i);
		for (j=0; j<4; j++)
		{
			char c;
			Queue_Del(&move, &c);
			printf("%c", c);
		}
		printf("\n");
	}
	*/

	printf("  Enemy tested.\n");
}