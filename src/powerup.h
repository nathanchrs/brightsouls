#ifndef POWERUP_H
#define POWERUP_H

#include "boolean.h"
#include "location.h"
#include "array.h"
#include "player.h"

typedef struct {
    char *name;
    int hpUp;
    int expUp;
    int strUp;
    int defUp;
} PowerUpType;

typedef struct {
	int typeId;
	Location location;
} PowerUp;

typedef ARRAY(PowerUp) PowerUpArray;
typedef ARRAY(PowerUpType) PowerUpTypeArray;

void PowerUpTypeArray_load(PowerUpTypeArray *powerUpTypes, FILE *fin);

void PowerUpArray_load(PowerUpArray *powerUps, FILE *fin);

void PowerUp_use(const PowerUpTypeArray *powerUpTypes, const PowerUp *powerUp, Player *player);

/* Returns the index where a PowerUp with the specified location is found, or -1 otherwise */
int PowerUpArray_searchLocation(const PowerUpArray *powerUps, Location loc);

void PowerUpTypeArray_deallocate(PowerUpTypeArray *powerUpTypes);

void PowerUpArray_deallocate(PowerUpArray *powerUps);

#endif