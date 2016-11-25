#include "gameresources.h"

void GameResources_load(GameResources *gameResources, FILE *fin) {
	AreaArray_load(&(gameResources->areas), fin);
	EnemyTypeArray_load(&(gameResources->enemyTypes), fin);
	EnemyArray_load(&(gameResources->enemies), fin);
	PowerUpTypeArray_load(&(gameResources->enemyTypes), fin);
	PowerUpArray_load(&(gameResources->enemies), fin);
	SkillTree_load(&(gameResources->skillTree), fin);
}

void GameResources_deallocate(GameResources *gameResources) {
	AreaArray_deallocate(&(gameResources->areas));
	EnemyTypeArray_deallocate(&(gameResources->enemyTypes));
	EnemyArray_deallocate(&(gameResources->enemies));
	PowerUpTypeArray_deallocate(&(gameResources->enemyTypes));
	PowerUpArray_deallocate(&(gameResources->enemies));
	SkillTree_deallocate(&(gameResources->skillTree));
}