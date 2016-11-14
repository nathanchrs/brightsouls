#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "boolean.h"

typedef struct {
	char *name;

	int hp;
	int str;
	int def;
	int exp;
} Player;

#endif