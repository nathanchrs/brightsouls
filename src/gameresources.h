#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "skilltree.h"
#include "boolean.h"
#include "array.h"

typedef struct {
	//EnemyType *enemyTypes;
	//PowerUpType *powerUpTypes;
	SkillTree skillTree;
	ARRAY(Area) areas;
} GameResources;

bool GameResources_load(GameResources *gameResources, const char *filePath);

void GameResources_deallocate(GameResources *gameResources);

#endif