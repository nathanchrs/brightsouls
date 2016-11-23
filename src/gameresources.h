#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "skilltree.h"
#include "boolean.h"
#include "array.h"
#include "area.h"

typedef struct {
	//EnemyType *enemyTypes;
	//PowerUpType *powerUpTypes;
	SkillTree skillTree;
	AreaArray areas;
    Powerup powerup;
} GameResources;

bool GameResources_load(GameResources *gameResources, const char *filePath);

void GameResources_deallocate(GameResources *gameResources);

#endif