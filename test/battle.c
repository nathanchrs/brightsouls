#include <assert.h>
#include <stdio.h>
#include "../src/battle.h"
#include "../src/stringutils.h"

void testBattle(Enemy *enemy, Player *player) {

	printf("  Testing Battle...\n");
	
	Battle battle;

	Battle_init(&battle, enemy, 0, player);
	assert(StringUtils_strcmpi(battle.enemy.name, "Enemy 1") == 0);
	assert(StringUtils_strcmpi(battle.enemy.type, "normal") == 0);
	assert(battle.enemy.moveCount == 10);
	assert(battle.enemy.hp == 50);
	assert(battle.enemy.str == 10);
	assert(battle.enemy.def == 5);
	assert(battle.enemy.exp == 25);
	printf("TES");
	assert(!IsEmpty(battle.enemy.moveList));
	int i, j;
	for (i=1; i<=battle.enemy.moveCount; i++)
	{
		Queue move;
		DelVFirst(&(battle.enemy.moveList), &move);
		printf("Move %d : ", i);
		for (j=0; j<4; j++)
		{
			char c;
			Queue_Del(&move, &c);
			printf("%c", c);
		}
		printf("\n");
	}
	printf("TES");
	assert(StringUtils_strcmpi(battle.player.name, "Player 1") == 0);
	assert(battle.player.str == 10);
	assert(battle.player.def == 3);
	assert(battle.player.exp == 0);

	printf("  Battle tested.\n");
}