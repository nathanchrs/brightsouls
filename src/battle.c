#include "battle.h"
#include "stringutils.h"

void Battle_load(Battle *battle, FILE *fin) {
	battle->round = IO_readInteger(fin);
	battle->battleLog = IO_readString(fin);
	battle->currentPhase = IO_readInteger(fin);

	battle->enemyName = IO_readString(fin);
	battle->enemyId = IO_readInteger(fin);
	battle->enemyTypeId = IO_readInteger(fin);
	battle->enemyHp = IO_readInteger(fin);
	battle->enemyStr = IO_readInteger(fin);
	battle->enemyDef = IO_readInteger(fin);
	battle->enemyExp = IO_readInteger(fin);
	MoveQueueStack_load(&(battle->enemyMoves), fin);
	MoveQueue_load(&(battle->playerMoveQueue), fin);
}

void Battle_save(const Battle *battle, FILE *fout) {
	/*IO_writeInteger(fout, battle->round);
	IO_writeString(fout, battle->battleLog);

	IO_writeInteger(fout, battle->enemyTypeId);
	IO_writeInteger(fout, battle->enemyHp);
	IO_writeInteger(fout, battle->enemyStr);
	IO_writeInteger(fout, battle->enemyDef);
	IO_writeInteger(fout, battle->enemyExp);*/
	//MoveQueueStack_save(&(battle->enemyMoves), fout);
}

void Battle_deallocate(Battle *battle) {
	StringUtils_deallocate(battle->enemyName);
	StringUtils_deallocate(battle->battleLog);
	MoveQueueStack_deallocate(&(battle->enemyMoves));
	MoveQueue_deallocate(&(battle->playerMoveQueue));
}

void Battle_init(Battle *battle, const EnemyArray *enemies, const EnemyTypeArray *enemyTypes, int enemyId) {
	Battle_deallocate(battle);

	battle->round = 1;
	battle->battleLog = StringUtils_clone("");
	battle->currentPhase = BATTLE_ONGOING;
	battle->enemyId = enemyId;
	battle->enemyTypeId = enemies->items[enemyId].typeId;
	battle->enemyName = StringUtils_clone(enemyTypes->items[battle->enemyTypeId].name);
	battle->enemyHp = enemyTypes->items[battle->enemyTypeId].hp;
	battle->enemyExp = enemyTypes->items[battle->enemyTypeId].exp;
	battle->enemyStr = enemyTypes->items[battle->enemyTypeId].str;
	battle->enemyDef = enemyTypes->items[battle->enemyTypeId].def;
	battle->enemyMoves = MoveQueueStack_clone(&(enemyTypes->items[battle->enemyTypeId].moves));

	// Randomize order of enemy move sequences
	MoveQueueStack_permute(&(battle->enemyMoves));

	List_initialize(&(battle->playerMoveQueue));
}

void Battle_calcMove(Battle *battle, Player *player) {
	MoveQueue enemyActionlist;
	List_popFirst(&(battle->enemyMoves), &enemyActionlist);

	char *roundNumber = StringUtils_fromInt(battle->round, "%d");
	StringUtils_append(&(battle->battleLog), "Round #");
	StringUtils_append(&(battle->battleLog), roundNumber);
	StringUtils_append(&(battle->battleLog), ":\n");

	while ((!List_isEmpty(&enemyActionlist)) && (player->hp > 0) && (battle->enemyHp > 0)) {
		StringUtils_append(&(battle->battleLog), "> ");
		char enemyAction, playerAction;
		List_popFirst(&(enemyActionlist), &enemyAction);
		List_popFirst(&(battle->playerMoveQueue), &playerAction);
		Battle_calcAction(enemyAction, playerAction, battle, player);
	}
	// Round end || player->hp <= 0 ||  battle->enemyHp <= 0(dead)
	Battle_calcResult(battle, player);

	// Reset player move list
	List_deallocate(&(battle->playerMoveQueue));
	List_initialize(&(battle->playerMoveQueue));

	StringUtils_appendChar(&(battle->battleLog), '\n');
}

void Battle_calcAction(char enemyAction, char playerAction, Battle *battle, Player *player) {
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
			EnemyDmg = PlayerStr - EnemyDef
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

	enemyAction = (char) toupper((int) enemyAction);
	playerAction = (char) toupper((int) playerAction);

	if ((playerAction == 'A') && (enemyAction == 'A'))
	{
		playerDmg = (battle->enemyStr) - (player->def);
		enemyDmg = (player->str) - (battle->enemyDef);
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " and ");
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " attacked at the same time!\n");
	}
	else if ((playerAction == 'A') && (enemyAction == 'B'))
	{
		playerDmg = (battle->enemyDef) - (player->def);
		enemyDmg = 0;
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " blocked ");
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), "'s attack!\n");
	}
	else if ((playerAction == 'A') && (enemyAction == 'F'))
	{
		playerDmg = 0;
		enemyDmg = (player->str);
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " attacked ");
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " when flanking!\n");
	}
	else if ((playerAction == 'B') && (enemyAction == 'A'))
	{
		playerDmg = 0;
		enemyDmg = (player->def) - (battle->enemyDef);
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " blocked ");
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), "'s attack!\n");
	}
	else if ((playerAction == 'B') && (enemyAction == 'B'))
	{
		playerDmg = 0;
		enemyDmg = 0;
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " and ");
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " blocked at the same time!\n");
	}
	else if ((playerAction == 'B') && (enemyAction == 'F'))
	{
		playerDmg = (battle->enemyStr);
		enemyDmg = 0;
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " flanked ");
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " when blocking!\n");
	}
	else if ((playerAction == 'F') && (enemyAction == 'A'))
	{
		playerDmg = (battle->enemyStr);
		enemyDmg = 0;
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " attacked ");
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " when flanking!\n");
	}
	else if ((playerAction == 'F') && (enemyAction == 'B'))
	{
		playerDmg = 0;
		enemyDmg = (player->str);
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " flanked ");
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " when blocking!\n");
	}
	else if ((playerAction == 'F') && (enemyAction == 'F'))
	{
		playerDmg = (battle->enemyStr) - (player->def);
		enemyDmg = (player->str) - (battle->enemyDef);
		StringUtils_append(&(battle->battleLog), player->name);
		StringUtils_append(&(battle->battleLog), " and ");
		StringUtils_append(&(battle->battleLog), battle->enemyName);
		StringUtils_append(&(battle->battleLog), " flanked at the same time!\n");
	}

	if (playerDmg < 0) playerDmg = 0;
	if (enemyDmg < 0) enemyDmg = 0;

	// Reduce hp, minimum hp is 0 (Dead)
	player->hp -= playerDmg;
	battle->enemyHp -= enemyDmg;

	if ((player->hp) < 0) (player->hp) = 0;
	if ((battle->enemyHp) < 0) (battle->enemyHp) = 0;
}

/* Set battle phase according to player and enemy HP */
void Battle_calcResult(Battle *battle, Player *player) {
	if (player->hp <= 0) {
		battle->currentPhase = BATTLE_ENEMY_WIN; // player dead
	} else if (battle->enemyHp <= 0) {
		battle->currentPhase = BATTLE_PLAYER_WIN; // player alive, enemy dead
		player->exp += battle->enemyExp;
		Player_normalizeStats(player);
	} else if (battle->enemyMoves.length <= 0) {
		battle->currentPhase = BATTLE_DRAW; // both still alive, enemy out of moves
		player->exp += battle->enemyExp;
		Player_normalizeStats(player);
	}
	// other than that, battle is still ongoing (BATTLE_ONGOING)
}