#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "stdio.h"

typedef struct {
	EnemyType *enemyTypes;
	PowerUpType *powerUpTypes;
	Skill *skills;
	Area *areas;
} GameResources;

void GameResources_load(GameResources *gameResources, const char *filePath);

void GameResources_deallocate(GameResources *gameResources);

EnemyType GameResources_getEnemyType(const GameResources *gameResources, const int id);

PowerUpType GameResources_getPowerUpType(const GameResources *gameResources, const int id);

Skill GameResources_getSkill(const GameResources *gameResources, const int id);

Area GameResources_getArea(const GameResources *gameResources, const int id);

#endif