#include "gameresources.h"
#include "io.h"

void GameResources_load(GameResources *gameResources, FILE *fin) {
	/* Load skill tree */
	SkillTree_load(&(gameResources->skillTree), fin);

	/* Load area grids */
	Area_loadArray(&(gameResources->areas), fin);
}

void GameResources_deallocate(GameResources *gameResources) {
	SkillTree_deallocate(&(gameResources->skillTree));

	int i;
	for (i = 0; i < gameResources->areas.length; i++) {
		Area_deallocate(&(gameResources->areas.items[i]));
	}
	Array_deallocate(&(gameResources->areas));
}