#ifndef POWERUP_H
#define POWERUP_H

#include "boolean.h"
#include "location.h"
#include "array.h"
#include "player.h"

typedef struct {
    char *powerName;
    Location loc;
    char *type;
    int bonus;
    bool available;
} PowerType;

/*
    example :
    Powerup P;
    P.type = "exp"; // exp, str, hp, etc
    P.bonus = 100; // exp + 100
 */

typedef ARRAY(PowerType) Powerup;

void Powerup_load(Powerup *powerup, FILE *fin);

void Powerup_add(PowerType powerup, Player *player);

#endif