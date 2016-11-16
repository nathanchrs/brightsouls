#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "skilltree.h"

typedef struct {
	//EnemyType *enemyTypes;
	//PowerUpType *powerUpTypes;
	SkillTree skillTree;
	//Area *areas;
} GameResources;

void GameResources_load(GameResources *gameResources, const char *filePath);

void GameResources_deallocate(GameResources *gameResources);

#endif