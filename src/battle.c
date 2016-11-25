#include "battle.h"
#include "stringutils.h"

void Battle_load(Battle *battle, FILE *fin) {
	battle->round = IO_readInteger(fin);
	battle->battleLog = IO_readString(fin);

	battle->enemyTypeId = IO_readInteger(fin);
	battle->enemyHp = IO_readInteger(fin);
	battle->enemyStr = IO_readInteger(fin);
	battle->enemyDef = IO_readInteger(fin);
	battle->enemyExp = IO_readInteger(fin);

	MoveQueueStack_load(&(battle->enemyMoves), fin);
	MoveQueue_load(&(battle->playerMoveQueue), fin);
}

void Battle_save(const Battle *battle, FILE *fout) {

}

void Battle_deallocate(Battle *battle) {
	StringUtils_deallocate(battle->battleLog);
	MoveQueueStack_deallocate(&(battle->enemyMoves));
	MoveQueue_deallocate(&(battle->playerMoveQueue));
}

void Battle_init(Battle *battle, const EnemyTypeArray *enemyTypes, int enemyTypeId) {
	Battle_deallocate(battle);

	battle->round = 0;
	battle->battleLog = "";
	battle->enemyTypeId = enemyTypeId;
	battle->enemyHp = enemyTypes->items[enemyTypeId].hp;
	battle->enemyExp = enemyTypes->items[enemyTypeId].exp;
	battle->enemyStr = enemyTypes->items[enemyTypeId].str;
	battle->enemyDef = enemyTypes->items[enemyTypeId].def;
	battle->enemyMoves = MoveQueueStack_clone(&(enemyTypes->items[enemyTypeId].moves));

	MoveQueueStack_permute(&(battle->enemyMoves));
}

/*
void Battle_playerInput(Player *player)
{
	char inp, dummy;
	scanf("%c", &inp);
	scanf("%c", &dummy);
	if ((inp == 'E') && (!Queue_IsEmpty(player->actionList)))
		Queue_Del(&(player->actionList), &inp);
	else if ((inp == 'A') || (inp == 'B') || (inp == 'F'))
		Queue_Add(&(player->actionList), inp);
}

void Battle_showEnemyMove(Queue enemyActionlist)
{
	char c, ct;
	Queue eAl;
	Queue_CreateEmpty(&eAl);

	Queue_CopyList(enemyActionlist, &eAl);
	
	printf("Current enemy move : ");
	while (!Queue_IsEmpty(eAl))
	{
		Queue_Del(&eAl, &c);
		ct = (char) tolower((int) c);
		if (c == ct)
			printf("# ");
		else
			printf("%c ", c);
	}
	printf("\n");
}
*/

void Battle_calcMove(Battle *battle)
{
	MoveQueue enemyActionlist;
	List_initialization(&enemyActionlist);
	List_popFirst(&(battle->enemyMoves), &enemyActionlist);
	
	while ((!List_isEmpty(enemyActionlist)) && (battle->playerHp > 0) && (battle->enemyHp > 0))
	{
		char enemyAction, playerAction;
		List_popFirst(&(enemyActionlist), &enemyAction);
		List_popFirst(&(playerMoveQueue), &playerAction);
		printf("Calculating action enemy(%c) & player(%c)\n", enemyAction, playerAction);
		Battle_calcAction(enemyAction, playerAction, battle);
	}
	// Round end || battle->playerHp <= 0 (dead)

	List_initialization(&(player->actionList));
}

void Battle_calcAction(char enemyAction, char playerAction, Battle *battle)
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

	enemyAction = (char) toupper((int) enemyAction);
	playerAction = (char) toupper((int) playerAction);

	if ((playerAction == 'A') && (enemyAction == 'A'))
	{
		playerDmg = (battle->enemyStr) - (battle->playerDef);
		enemyDmg = (battle->playerStr) - (battle->enemyDef);
	}
	else if ((playerAction == 'A') && (enemyAction == 'B'))
	{
		playerDmg = (battle->enemyDef) - (battle->playerDef);
		enemyDmg = 0;
	}
	else if ((playerAction == 'A') && (enemyAction == 'F'))
	{
		playerDmg = 0;
		enemyDmg = (battle->playerStr);
	}
	else if ((playerAction == 'B') && (enemyAction == 'A'))
	{
		playerDmg = 0;
		enemyDmg = (battle->playerDef) - (battle->enemyDef);
	}
	else if ((playerAction == 'B') && (enemyAction == 'B'))
	{
		playerDmg = 0;
		enemyDmg = 0;
	}
	else if ((playerAction == 'B') && (enemyAction == 'F'))
	{
		playerDmg = (battle->enemyStr);
		enemyDmg = 0;
	}
	else if ((playerAction == 'F') && (enemyAction == 'A'))
	{
		playerDmg = (battle->enemyStr);
		enemyDmg = 0;
	}
	else if ((playerAction == 'F') && (enemyAction == 'B'))
	{
		playerDmg = 0;
		enemyDmg = (battle->playerStr);
	}
	else if ((playerAction == 'F') && (enemyAction == 'F'))
	{
		playerDmg = (battle->enemyStr) - (battle->playerDef);
		enemyDmg = (battle->playerStr) - (battle->enemyDef);
	}

	printf("Player Damaged : %d\n", playerDmg);
	printf("Enemy Damaged : %d\n", enemyDmg);

	if (playerDmg < 0)
		playerDmg = 0;
	if (enemyDmg < 0)
		enemyDmg = 0;

	// Reduce hp, minimum hp is 0 (Dead)
	battle->playerHp -= playerDmg;
	battle->enemyHp -= enemyDmg;

	if ((battle->playerHp) < 0)
		(battle->playerHp) = 0;
	if ((battle->enemyHp) < 0)
		(battle->enemyHp) = 0;
}