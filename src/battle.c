#include "battle.h"
#include "stdlib.h"
#include "stringutils.h"
/*
typedef struct {
	int enemyId;
	char *enemyName;
	char enemyType; //n : Normal, b : Boss

	int enemyHp;
	int enemyStr;
	int enemyDef;
	int enemyExp;

	Stack moveList;
	int moveCount; //n : 10, b : 20
	char enemyMovelist[20][4];
} Battle;
*/
void Battle_load(Battle *battle, FILE *fin)
{

}

void Battle_save(const Battle *battle, FILE *fout)
{

}

void Battle_deallocate(Battle *battle)
{

}

void Battle_loadEnemy(Battle *battle, int eId)
{
	battle->enemyId = eId;
	battle_loadEnemyStat(battle);
	Battle_loadEnemyMove(battle);
}

void Battle_loadEnemyStat(Battle *battle)
{
	
}

void Battle_loadEnemyMove(Battle *battle)
{
	srand(time(NULL));
	int i, j;
	int moveCount = battle->moveCount;
	char moveList[4];
	CreateEmpty(&(battle->moveList));

	// TODO : Randomize moveList, maybe using List -> pop
	for (i=moveCount; i>0; i--)
	{
		//int loadMove = rand() % i;
		int hideMove = rand() % 6;
		int hm1, hm2;

		for (j=0; j<4; j++)
		{
			//moveList[j] = battle->enemyMovelist[loadMove][j];
			moveList[j] = battle->enemyMovelist[i][j];
		}

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
		moveList[hm1] = (char) tolower((int) moveList[hm1]);
		moveList[hm2] = (char) tolower((int) moveList[hm2]);

		char *pushMove = "";
		for (j=0; j<4; j++)
		{
			pushMove += moveList[j];
		}

		Push(&(battle->moveList), pushMove);
	}
}