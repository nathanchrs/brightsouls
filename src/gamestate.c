#include "gamestate.h"
#include "stringutils.h"

void GameState_load(GameState *gameState, FILE *fin) {
	
	// DateTime_load(&(gameState->lastSaveTime), fin);
	
	gameState->requestInput = IO_readInteger(fin);
	gameState->currentPhase = IO_readInteger(fin);

	gameState->message = IO_readString(fin);

	LocationEdgeArray_load(&(gameState->locationEdges), fin);

	Player_load(&(gameState->player), fin);

	gameState->isEnemyDefeated = IO_readBoolArray(fin);
	gameState->isPowerUpUsed = IO_readBoolArray(fin);
	gameState->isSkillUnlocked = IO_readBoolArray(fin);

	Battle_load(&(gameState->battle), fin);
}

void GameState_deallocate(GameState *gameState) {
	StringUtils_deallocate(gameState->message);
	LocationEdgeArray_deallocate(&(gameState->locationEdges));
	Player_deallocate(&(gameState->player));
	Array_deallocate(&(gameState->isEnemyDefeated));
	Array_deallocate(&(gameState->isPowerUpUsed));
	Array_deallocate(&(gameState->isSkillUnlocked));
	Battle_deallocate(&(gameState->battle));
}
