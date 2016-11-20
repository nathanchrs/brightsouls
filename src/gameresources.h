#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "skilltree.h"
#include "boolean.h"

typedef struct {
	//EnemyType *enemyTypes;
	//PowerUpType *powerUpTypes;
	SkillTree skillTree;
	//Area *areas;
} GameResources;

bool GameResources_load(GameResources *gameResources, const char *filePath);

void GameResources_deallocate(GameResources *gameResources);

#endif