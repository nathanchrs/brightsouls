#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "boolean.h"
#include "location.h"
#include "listlinier.h"
#include "queuelist.h"

typedef struct {
	char *name;

	int hp;
	int maxHp;
	int str;
	int def;
	int exp;
	int maxExp;
	int level;

    Location location;
	List moveList;
	Queue actionList;
} Player;

void Player_load(Player *player, FILE *fin);

void Player_save(const Player *player, FILE *fout);

void Player_deallocate(Player *player);

#endif