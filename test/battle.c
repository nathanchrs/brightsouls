#include <assert.h>
#include "../src/io.h"
#include "../src/battle.h"
#include "../src/stringutils.h"

void testBattle(const char *executableDirectory) {

	printf("  Testing Battle...\n");

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
	assert(battle.enemyId == 0);
	assert(battle.enemyTypeId == 0);
	assert(battle.enemyHp == 50);
	assert(battle.enemyStr == 10);
	assert(battle.enemyDef == 5);
	assert(battle.enemyExp == 25);
	assert(!List_isEmpty(&battle.enemyMoves));

	assert(StringUtils_strcmpi(player.name, "Player 1") == 0);
	assert(player.str == 12);
	assert(player.def == 3);
	assert(player.exp == 0);

	MoveQueueStack mqs;
	List_initialize(&mqs);
	mqs = MoveQueueStack_clone(&battle.enemyMoves);
	List_initialize(&battle.playerMoveQueue);
	List_popFirst(&mqs, &battle.playerMoveQueue);

	while ((!List_isEmpty(&battle.enemyMoves)) && (player.hp > 0) && (battle.enemyHp > 0))
	{
		battle.battleLog = StringUtils_clone("");

		Battle_calcMove(&battle, &player);

		/*printf("Saving battle..\n");
		FILE *fout = IO_openFile(executableDirectory, "../test/battlesave.in");
		assert(fout != NULL);
		Battle_save(&battle, fout);
		IO_closeFile(fout);*/
		battle.round++;
	}

	Battle_deallocate(&battle);

	printf("  Battle tested.\n");
}