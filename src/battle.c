#include "battle.h"

void Battle_load(Battle *battle, FILE *fin)
{

}

void Battle_save(const Battle *battle, FILE *fout)
{

}

void Battle_deallocate(Battle *battle)
{

}

void Battle_init(Battle *battle, const Enemy *enemy, int eId, Player *player)
{
	// Load enemy data
	printf("Loading enemy\n");
	battle->enemy = enemy->items[eId];
	//printf("Randoming enemy movelist\n");
	//Enemy_randMovelist(&(battle->enemy));

	// Load player data
	printf("Loading player data\n");
	battle->player = *player;
	printf("Emptying player movelist\n");
	CreateEmpty(&(battle->player.moveList));
	printf("Emptying player actionlist\n");
	Queue_CreateEmpty(&(battle->player.actionList));
	printf("Battle initialization done\n");
}

void Battle_playerInput(Player *player)
{
	char inp;
	scanf("%c", &inp);

	if ((inp == 'E') && (!Queue_IsEmpty(player->actionList)))
		Queue_Del(&(player->actionList), &inp);
	else if ((inp == 'A') || (inp == 'B') || (inp == 'F'))
		Queue_Add(&(player->actionList), inp);
}

void Battle_calcAction(char playerAction, char enemyAction, EnemyType *enemy, Player *player)
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