#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include "boolean.h"
#include "enemy.h"
#include "player.h"

typedef struct {
	EnemyType enemy;
	Player player;

	int round;
} Battle;

void Battle_load(Battle *battle, FILE *fin);

void Battle_save(const Battle *battle, FILE *fout);

void Battle_deallocate(Battle *battle);

void Battle_init(Battle *battle, const Enemy *enemy, int eId, Player *player);

void Battle_playerInput(Player *player);

void Battle_calcAction(char playerAction, char enemyAction, EnemyType *enemy, Player *player);

#endif