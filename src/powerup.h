#ifndef POWERUP_H
#define POWERUP_H

#include "boolean.h"
#include "location.h"
#include "array.h"
#include "player.h"

typedef struct {
    char *powerUpName;
    int hpUp;
    int expUp;
    int strUp;
    int defUp;
} PowerUpType;

typedef struct {
	PowerUpType type;
	Location location;
	bool available;
} PowerUp;

typedef ARRAY(PowerUp) PowerUpArray;
typedef ARRAY(PowerUpType) PowerUpTypeArray;

void PowerUp_loadArray(PowerUpArray *powerUps, FILE *fin);

void PowerUpType_loadArray(PowerUpTypeArray *powerUpTypes, FILE *fin);

void PowerUp_use(const PowerUp *powerUp, Player *player);

#endif