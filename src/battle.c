#include "battle.h"
#include "stdlib.h"
#include "stringutils.h"

/*
typedef struct {
	Enemy enemy;
	Player player;

	int round;
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

void Battle_init(Battle *battle, int eId)
{
	// Load enemy data
	Enemy_load(&(battle->enemy), eId);
	Battle_randMovelist(&(battle->enemy));
	// Load player data

}

void Battle_randMovelist(Enemy *enemy)
{
	srand(time(NULL));
	int i, j;
	int moveCount = enemy->moveCount;
	Queue actions;
	Queue_CreateEmpty(&actions);

	// TODO : Randomize which move list to pop
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

void Battle_calcAction(char playerAction, char enemyAction, Enemy *enemy, Player *player)
{
	// Calculate damage
	/*
		a = Attack
		b = Block
		f = Flank

		a > f
		f > b
		b > a

		Same action :
			Attack/Flank :
			PlayerDmg = EnemyStr - PlayerDef
			EnemyDmg = PlayerStr - EnemeyDef
			Block :
			PlayerDmg = EnemyDmg = 0
		Win action :
			Attack/Flank :
			WinnerDmg = 0
			LoserDmg = WinnerStr
			Block :
			WinnerDmg = 0
			LoserDmg = WinnerDef - LoserDef
		
		Minimum damage = 0
	*/
	int playerDmg, enemyDmg;

	if ((playerAction == 'a') && (enemyAction == 'a'))
	{
		playerDmg = (enemy->str) - (player->def);
		enemyDmg = (player->str) - (enemy->def);
	}
	else if ((playerAction == 'a') && (enemyAction == 'b'))
	{
		playerDmg = (enemy->def) - (player->def);
		enemyDmg = 0;
	}
	else if ((playerAction == 'a') && (enemyAction == 'f'))
	{
		playerDmg = 0;
		enemyDmg = (player->str);
	}
	else if ((playerAction == 'b') && (enemyAction == 'a'))
	{
		playerDmg = 0;
		enemyDmg = (player->def) - (enemy->def);
	}
	else if ((playerAction == 'b') && (enemyAction == 'b'))
	{
		playerDmg = 0;
		enemyDmg = 0;
	}
	else if ((playerAction == 'b') && (enemyAction == 'f'))
	{
		playerDmg = (enemy->str);
		enemyDmg = 0;
	}
	else if ((playerAction == 'f') && (enemyAction == 'a'))
	{
		playerDmg = (enemy->str);
		enemyDmg = 0;
	}
	else if ((playerAction == 'f') && (enemyAction == 'b'))
	{
		playerDmg = 0;
		enemyDmg = (player->str);
	}
	else if ((playerAction == 'f') && (enemyAction == 'f'))
	{
		playerDmg = (enemy->str) - (player->def);
		enemyDmg = (player->str) - (enemy->def);
	}

	if (playerDmg < 0)
		playerDmg = 0;
	if (enemyDmg < 0)
		enemyDmg = 0;

	// Reduce hp, minimum hp is 0 (Dead)
	player->hp -= playerDmg;
	enemy->hp -= enemyDmg;

	if ((player->hp) < 0)
		(player->hp) = 0;
	if ((enemy->hp) < 0)
		(enemy->hp) = 0;
}