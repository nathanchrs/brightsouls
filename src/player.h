#ifndef PLAYER_H
#define PLAYER_H

#include "boolean.h"
#include "location.h"
#include "io.h"
#include "move.h"

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
} Player;

void Player_load(Player *player, FILE *fin);

void Player_save(const Player *player, FILE *fout);

void Player_normalizeStats(Player *player);

void Player_deallocate(Player *player);

#endif