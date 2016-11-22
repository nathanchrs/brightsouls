#include <assert.h>
#include <stdio.h>
#include "../src/battle.h"
#include "../src/stringutils.h"

void testBattle() {

	printf("  Testing Battle...\n");

	Battle battle;

	Player player;
	player.name = "Player 1";
	player.hp = 50;
	player.str = 12;
	player.def = 3;
	player.exp = 0;

	Enemy enemy;
	FILE *fin = fopen("../test/enemy.in", "r");
	assert(fin != NULL);
	Enemy_load(&enemy, fin);

	Battle_init(&battle, &enemy, 0, &player);
	assert(StringUtils_strcmpi(battle.enemy.name, "Enemy 1") == 0);
	assert(StringUtils_strcmpi(battle.enemy.type, "normal") == 0);
	assert(battle.enemy.moveCount == 10);
	assert(battle.enemy.hp == 50);
	assert(battle.enemy.str == 10);
	assert(battle.enemy.def == 5);
	assert(battle.enemy.exp == 25);
	assert(!IsEmpty(battle.enemy.moveList));

	assert(StringUtils_strcmpi(battle.player.name, "Player 1") == 0);
	assert(battle.player.str == 12);
	assert(battle.player.def == 3);
	assert(battle.player.exp == 0);
	printf("Stats :\n");
	printf(" %s hp : %d\n", battle.enemy.name, battle.enemy.hp);
	printf(" %s str : %d\n", battle.enemy.name, battle.enemy.str);
	printf(" %s def : %d\n", battle.enemy.name, battle.enemy.def);
	printf(" %s hp : %d\n", battle.player.name, battle.player.hp);
	printf(" %s str : %d\n", battle.player.name, battle.player.str);
	printf(" %s def : %d\n", battle.player.name, battle.player.def);
	while ((battle.round <= battle.enemy.moveCount) && (battle.player.hp > 0) && (battle.enemy.hp > 0))
	{
		Battle_showEnemyMove(Info(First(battle.enemy.moveList)));

		Queue_CreateEmpty(&battle.player.actionList);
		while (Queue_NbElmt(battle.player.actionList) < 4)
		{
			printf("Input action #%d: ", Queue_NbElmt(battle.player.actionList)+1);
			Battle_playerInput(&battle.player);
		}
		Battle_calcMove(&(battle.enemy), &battle.player);

		printf("Round %d :\n", battle.round);
		printf(" %s hp : %d\n", battle.enemy.name, battle.enemy.hp);
		printf(" %s hp : %d\n", battle.player.name, battle.player.hp);
		battle.round++;
	}
	if (battle.player.hp == 0 && battle.enemy.hp != 0)
		printf("%s won!\n", battle.enemy.name);
	else if (battle.enemy.hp == 0 && battle.player.hp != 0)
		printf("%s won!\n", battle.player.name);
	else
		printf("It's a draw!\n");

	printf("  Battle tested.\n");
}