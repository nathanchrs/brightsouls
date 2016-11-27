#include "gameresources.h"
#include "stringutils.h"

void GameResources_load(GameResources *gameResources, FILE *fin) {
	AreaArray_load(&(gameResources->areas), fin);
	EnemyTypeArray_load(&(gameResources->enemyTypes), fin);
	EnemyArray_load(&(gameResources->enemies), fin);
	PowerUpTypeArray_load(&(gameResources->powerUpTypes), fin);
	PowerUpArray_load(&(gameResources->powerUps), fin);
	SkillTree_load(&(gameResources->skillTree), fin);

	gameResources->playerImage = IO_readString(fin);
}

void GameResources_deallocate(GameResources *gameResources) {
	AreaArray_deallocate(&(gameResources->areas));
	EnemyTypeArray_deallocate(&(gameResources->enemyTypes));
	EnemyArray_deallocate(&(gameResources->enemies));
	PowerUpTypeArray_deallocate(&(gameResources->powerUpTypes));
	PowerUpArray_deallocate(&(gameResources->powerUps));
	SkillTree_deallocate(&(gameResources->skillTree));

	StringUtils_deallocate(gameResources->playerImage);
}