#include "battle.h"
#include "stringutils.h"

void Battle_load(Battle *battle, GameState *gamestate, FILE *fin) {
	battle->round = IO_readInteger(fin);
	battle->roundMax = IO_readInteger(fin);
	battle->battleLog = IO_readString(fin);

	battle->enemyName = IO_readString(fin);
	battle->enemyHp = IO_readInteger(fin);
	battle->enemyStr = IO_readInteger(fin);
	battle->enemyDef = IO_readInteger(fin);
	battle->enemyExp = IO_readInteger(fin);
	MoveQueueStack_load(&(battle->enemyMoves), fin);
	MoveQueue mq;
	List_initialize(&mq);
	int i;
	for (i=1; i<round; i++)
		List_popFirst(&(battle->enemyMoves), &mq);
	battle->enemyMovesShow = Battle_enemyMovesShow(battle);
	battle->enemyMovesHide = Battle_enemyMovesHide(battle);
/*
	gamestate->player.name = IO_readString(fin);
	gamestate->player.hp = IO_readInteger(fin);
	gamestate->player.str = IO_readInteger(fin);
	gamestate->player.def = IO_readInteger(fin);
	gamestate->player.exp = IO_readInteger(fin);*/
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

	battle->round = 1;
	//battle->roundMax = 10;
	battle->battleLog = "";
	battle->enemyName = enemyTypes->items[enemyTypeId].name;
	battle->enemyHp = enemyTypes->items[enemyTypeId].hp;
	battle->enemyExp = enemyTypes->items[enemyTypeId].exp;
	battle->enemyStr = enemyTypes->items[enemyTypeId].str;
	battle->enemyDef = enemyTypes->items[enemyTypeId].def;
	battle->enemyMoves = MoveQueueStack_clone(&(enemyTypes->items[enemyTypeId].moves));

	MoveQueueStack_permute(&(battle->enemyMoves));
}


void Battle_playerInput(Battle *battle)
{
	char inp, dummy;
	scanf("%c", &inp);
	scanf("%c", &dummy);
	if ((inp == 'E') && (!List_isEmpty(&(battle->playerMoveQueue))))
		List_popLast(&(battle->playerMoveQueue), &inp);
	else if ((inp == 'A') || (inp == 'B') || (inp == 'F'))
		List_pushLast(&(battle->playerMoveQueue), inp);
}

char *Battle_enemyMovesShow(Battle *battle)
{
	char s[8];

	char c;
	MoveQueueStack mqs;
	List_initialize(&mqs);
	MoveQueue eAl;
	List_initialize(&eAl);

	mqs = MoveQueueStack_clone(&(battle->enemyMoves));
	List_popFirst(&mqs, &eAl);
	
	int i; i = 0;
	while (!List_isEmpty(&eAl))
	{
		List_popFirst(&eAl, &c);
		s[i] = c;
		i++;
		s[i] = ' ';
		i++;
	}
	char *sr = s;
	return sr;
}

char *Battle_enemyMovesHide(Battle *battle)
{
	char s[8];

	char c, ct;
	MoveQueueStack mqs;
	List_initialize(&mqs);
	MoveQueue eAl;
	List_initialize(&eAl);

	mqs = MoveQueueStack_clone(&(battle->enemyMoves));
	List_popFirst(&mqs, &eAl);
	
	int i; i = 0;
	while (!List_isEmpty(&eAl))
	{
		List_popFirst(&eAl, &c);
		ct = (char) tolower((int) c);
		if (c == ct)
		{
			s[i] = '#';
			i++;
			s[i] = ' ';
			i++;
		}
		else
		{
			s[i] = c;
			i++;
			s[i] = ' ';
			i++;
		}
	}
	char *sr = s;
	return sr;
}

void Battle_calcMove(Battle *battle, GameState *gamestate)
{
	MoveQueue enemyActionlist;
	List_initialize(&enemyActionlist);
	List_popFirst(&(battle->enemyMoves), &enemyActionlist);
	
	while ((!List_isEmpty(&enemyActionlist)) && (gamestate->player.hp > 0) && (battle->enemyHp > 0))
	{
		char enemyAction, playerAction;
		List_popFirst(&(enemyActionlist), &enemyAction);
		List_popFirst(&(battle->playerMoveQueue), &playerAction);
		Battle_calcAction(enemyAction, playerAction, battle);
	}
	// Round end || gamestate->player.hp <= 0 (dead)

	List_initialize(&(battle->playerMoveQueue));
}

void Battle_calcAction(char enemyAction, char playerAction, Battle *battle, GameState *gamestate)
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
		playerDmg = (battle->enemyStr) - (gamestate->player.def);
		enemyDmg = (gamestate->player.str) - (battle->enemyDef);
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " and ");
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " attacked at the same time!\n");
	}
	else if ((playerAction == 'A') && (enemyAction == 'B'))
	{
		playerDmg = (battle->enemyDef) - (gamestate->player.def);
		enemyDmg = 0;
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " blocked ");
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, "'s attack!\n");
	}
	else if ((playerAction == 'A') && (enemyAction == 'F'))
	{
		playerDmg = 0;
		enemyDmg = (gamestate->player.str);
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " attacked ");
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " when flanking!\n");
	}
	else if ((playerAction == 'B') && (enemyAction == 'A'))
	{
		playerDmg = 0;
		enemyDmg = (gamestate->player.def) - (battle->enemyDef);
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " blocked ");
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, "'s attack!\n");
	}
	else if ((playerAction == 'B') && (enemyAction == 'B'))
	{
		playerDmg = 0;
		enemyDmg = 0;
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " and ");
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " blocked at the same time!\n");
	}
	else if ((playerAction == 'B') && (enemyAction == 'F'))
	{
		playerDmg = (battle->enemyStr);
		enemyDmg = 0;
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " flanked ");
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " when blocking!\n");
	}
	else if ((playerAction == 'F') && (enemyAction == 'A'))
	{
		playerDmg = (battle->enemyStr);
		enemyDmg = 0;
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " attacked ");
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " when flanking!\n");
	}
	else if ((playerAction == 'F') && (enemyAction == 'B'))
	{
		playerDmg = 0;
		enemyDmg = (gamestate->player.str);
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " flanked ");
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " when blocking!\n");
	}
	else if ((playerAction == 'F') && (enemyAction == 'F'))
	{
		playerDmg = (battle->enemyStr) - (gamestate->player.def);
		enemyDmg = (gamestate->player.str) - (battle->enemyDef);
		battle->battleLog = StringUtils_concat(battle->battleLog, gamestate->player.name);
		battle->battleLog = StringUtils_concat(battle->battleLog, " and ");
		battle->battleLog = StringUtils_concat(battle->battleLog, battle->enemyName);
		battle->battleLog = StringUtils_concat(battle->battleLog, " flanked at the same time!\n");
	}

	if (playerDmg < 0)
		playerDmg = 0;
	if (enemyDmg < 0)
		enemyDmg = 0;

	// Reduce hp, minimum hp is 0 (Dead)
	gamestate->player.hp -= playerDmg;
	battle->enemyHp -= enemyDmg;

	if ((gamestate->player.hp) < 0)
		(gamestate->player.hp) = 0;
	if ((battle->enemyHp) < 0)
		(battle->enemyHp) = 0;
}