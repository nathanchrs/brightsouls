#include "enemy.h"
#include "stringutils.h"
#include "time.h"
#include "stdlib.h"

void Enemy_load(Enemy *enemy, FILE *fin)
{
	int n, i, j, k;
	char inp;
	Queue move;
	fscanf(fin, "%d", &n);
	Array_allocate(enemy, n);
	enemy->length = n;
	for (i = 0; i < n; i++) {
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		enemy->items[i].name = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		enemy->items[i].type = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
		if (StringUtils_strcmpi(enemy->items[i].type, "normal") == 0)
			enemy->items[i].moveCount = 10;
		else if (StringUtils_strcmpi(enemy->items[i].type, "boss") == 0)
			enemy->items[i].moveCount = 20;
		else
			enemy->items[i].moveCount = 0;
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		fscanf(fin, "%d", &(enemy->items[i].hp));
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		fscanf(fin, "%d", &(enemy->items[i].str));
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		fscanf(fin, "%d", &(enemy->items[i].def));
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		fscanf(fin, "%d", &(enemy->items[i].exp));
		CreateEmpty(&(enemy->items[i].moveList));
		for (j = 0; j < enemy->items[i].moveCount; j++)
		{
			Queue_CreateEmpty(&move);
			StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
			for (k = 0; k < 4; k++)
			{
				inp = fgetc(fin);
				Queue_Add(&move, inp);
			}
			InsVLast(&(enemy->items[i].moveList), move);
		}
	}
}

void Enemy_randMovelist(EnemyType *enemy)
{
	srand(time(NULL));
	int i, j;
	int moveCount = enemy->moveCount;
	Queue actions;
	Queue_CreateEmpty(&actions);

	for (i=moveCount; i>0; i--)
	{
		//Take out a random move list
		int loadMove = rand() % i;
		if (loadMove == 0)
			DelVFirst(&(enemy->moveList), &actions);
		else
		{
			address P = First(enemy->moveList);
			address Pt;
			for (j=0; j<loadMove-1; j++)
			{
				P = Next(P);
			}
			// Delete Next(P)
			DelAfter(&(enemy->moveList), &Pt, P);
			actions = Info(Pt);
		}
		// actions = popped queue

		//Randomize actions and hide 2 of them
		int hideMove = rand() % 6;
		int hm1, hm2;

		switch(hideMove)
		{
			case 0 :
				hm1 = 0;
				hm2 = 1;
			case 1 :
				hm1 = 0;
				hm2 = 2;
			case 2 :
				hm1 = 0;
				hm2 = 3;
			case 3 :
				hm1 = 1;
				hm2 = 2;
			case 4 :
				hm1 = 1;
				hm2 = 3;
			case 5 :
				hm1 = 2;
				hm2 = 3;
		}

		for (j=0; j<4; j++)
		{
			if ((j == hm1) || (j == hm2))
			{
				char c;
				Queue_Del(&actions, &c);
				c = (char) tolower((int) c);
				Queue_Add(&actions, c);
			}
		}

		//Push back the move list that was taken out
		InsVLast(&(enemy->moveList), actions);
	}
}