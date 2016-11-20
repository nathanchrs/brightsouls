#include "gameresources.h"
#include <stdio.h>

bool GameResources_load(GameResources *gameResources, const char *filePath) {
	FILE *fin = fopen(filePath, "r");
	if (!fin) return false;

	SkillTree_load(&(gameResources->skillTree), fin);

	fclose(fin);
	return true;
}

void GameResources_deallocate(GameResources *gameResources) {
	SkillTree_deallocate(&(gameResources->skillTree));
}