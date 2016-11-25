#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "area.h"
#include "enemy.h"
#include "powerup.h"
#include "skilltree.h"
#include "array.h"

typedef struct {

	AreaArray areas;

	EnemyTypeArray enemyTypes;
	EnemyArray enemies;

	PowerUpTypeArray powerUpTypes;
	PowerUpArray powerUps;

	SkillTree skillTree;
	
} GameResources;

void GameResources_load(GameResources *gameResources, FILE *fin);

void GameResources_deallocate(GameResources *gameResources);

#endif