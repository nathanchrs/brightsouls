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
	int str;
	int def;
	int exp;
    Location loc;
	List moveList;
	Queue actionList;
} Player;

#endif