#include <assert.h>
#include "../src/io.h"
#include "../src/battle.h"
#include "../src/stringutils.h"

void testBattle(const char *executableDirectory) {

	printf("  Testing Battle...\n");

	/*EnemyArray enemies;

	FILE *fin = IO_openFile(executableDirectory, "../test/enemy.in"-7);
	assert(fin != NULL);
	Enemy_loadArray(&enemies, fin);
	IO_closeFile(fin);
	*/

	Battle battle;

	FILE *fin = IO_openFile(executableDirectory, "../test/battle.in");
	assert(fin != NULL);
	Battle_load(&battle, fin);
	IO_closeFile(fin);	

	Player player;
	player.name = "Player 1";
	player.hp = 50;
	player.str = 12;
	player.def = 3;
	player.exp = 0;

	//Battle_init(&battle, &(enemies.items[0]), 0, &player);

	assert(battle.round == 1);
	assert(StringUtils_strcmpi(battle.battleLog, "BattleLog") == 0);
	assert(battle.currentPhase == BATTLE_ONGOING);

	assert(StringUtils_strcmpi(battle.enemyName, "Jenis musuh 1") == 0);
	assert(battle.enemyHp == 50);
	assert(battle.enemyStr == 10);
	assert(battle.enemyDef == 5);
	assert(battle.enemyExp == 25);
	assert(!List_isEmpty(&battle.enemyMoves));

	assert(StringUtils_strcmpi(player.name, "Player 1") == 0);
	assert(player.str == 12);
	assert(player.def == 3);
	assert(player.exp == 0);
	printf("Stats :\n");
	printf(" %s hp : %d\n", battle.enemyName, battle.enemyHp);
	printf(" %s str : %d\n", battle.enemyName, battle.enemyStr);
	printf(" %s def : %d\n", battle.enemyName, battle.enemyDef);
	printf(" %s hp : %d\n", player.name, player.hp);
	printf(" %s str : %d\n", player.name, player.str);
	printf(" %s def : %d\n", player.name, player.def);
	while ((!List_isEmpty(&battle.enemyMoves)) && (player.hp > 0) && (battle.enemyHp > 0))
	{
		printf("Enemy moves hide : %s\n", Battle_enemyMovesHide(&battle));
		printf("Enemy moves show : %s\n", Battle_enemyMovesShow(&battle));
		battle.battleLog = "";

		List_initialize(&battle.playerMoveQueue);
		int i;
		for (i=1; i<=4; i++)
		{
			printf("Input action #%d: ", i);
			Battle_playerInput(&battle);
		}
		Battle_calcMove(&battle, &player);

		printf("Round %d :\n", battle.round);
		printf(" %s hp : %d\n", battle.enemyName, battle.enemyHp);
		printf(" %s hp : %d\n", player.name, player.hp);
		printf("%s", battle.battleLog);

		/*printf("Saving battle..\n");
		FILE *fout = IO_openFile(executableDirectory, "../test/battlesave.in");
		assert(fout != NULL);
		Battle_save(&battle, fout);
		IO_closeFile(fout);*/
		battle.round++;
	}
	printf("Result : %d\n", battle.currentPhase);

	printf("  Battle tested.\n");
}