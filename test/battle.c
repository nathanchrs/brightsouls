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

	//Battle_init(&battle, &(enemies.items[0]), 0, &player);

	assert(battle.round == 1);
	assert(battle.roundMax == 10);
	assert(StringUtils_strcmpi(battle.battleLog, "BattleLog") == 0);

	assert(StringUtils_strcmpi(battle.enemyName, "Jenis musuh 1") == 0);
	assert(battle.enemyHp == 50);
	assert(battle.enemyStr == 10);
	assert(battle.enemyDef == 5);
	assert(battle.enemyExp == 25);
	assert(!List_isEmpty(&battle.enemyMoves));

	assert(StringUtils_strcmpi(battle.playerName, "Player 1") == 0);
	assert(battle.playerStr == 12);
	assert(battle.playerDef == 3);
	assert(battle.playerExp == 0);
	printf("Stats :\n");
	printf(" %s hp : %d\n", battle.enemyName, battle.enemyHp);
	printf(" %s str : %d\n", battle.enemyName, battle.enemyStr);
	printf(" %s def : %d\n", battle.enemyName, battle.enemyDef);
	printf(" %s hp : %d\n", battle.playerName, battle.playerHp);
	printf(" %s str : %d\n", battle.playerName, battle.playerStr);
	printf(" %s def : %d\n", battle.playerName, battle.playerDef);
	while ((battle.round <= battle.roundMax) && (battle.playerHp > 0) && (battle.enemyHp > 0))
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
		Battle_calcMove(&battle);

		printf("Round %d/%d :\n", battle.round, battle.roundMax);
		printf(" %s hp : %d\n", battle.enemyName, battle.enemyHp);
		printf(" %s hp : %d\n", battle.playerName, battle.playerHp);
		printf("%s", battle.battleLog);
		battle.round++;
	}
	if (battle.playerHp == 0 && battle.enemyHp != 0)
		printf("%s won!\n", battle.enemyName);
	else if (battle.enemyHp == 0 && battle.playerHp != 0)
		printf("%s won!\n", battle.playerName);
	else
		printf("It's a draw!\n");

	printf("  Battle tested.\n");
}