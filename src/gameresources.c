#include "gameresources.h"
#include <stdio.h>

void GameResources_load(GameResources *gameResources, const char *filePath) {
	FILE *fin = fopen(filePath, "r");

	SkillTree_load(&(gameResources->skillTree), fin);

	fclose(fin);
}

void GameResources_deallocate(GameResources *gameResources) {
	SkillTree_deallocate(&(gameResources->skillTree));
}