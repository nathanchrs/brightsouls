#include "gameresources.h"
#include <stdio.h>

bool GameResources_load(GameResources *gameResources, const char *filePath) {
	FILE *fin = fopen(filePath, "r");
	if (!fin) return false;

	/* Load skill tree */
	SkillTree_load(&(gameResources->skillTree), fin);

	/* Load area grids */
	Area_loadArray(&(gameResources->areas), fin);

	fclose(fin);
	return true;
}

void GameResources_deallocate(GameResources *gameResources) {
	SkillTree_deallocate(&(gameResources->skillTree));

	int i;
	for (i = 0; i < gameResources->areas.length; i++) {
		Area_deallocate(&(gameResources->areas.items[i]));
	}
	Array_deallocate(&(gameResources->areas));
}