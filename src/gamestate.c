#include "gamestate.h"
#include "stringutils.h"

void GameState_load(GameState *gameState, FILE *fin) {
	
	// DateTime_load(&(gameState->lastSaveTime), fin);
	
	gameState->requestInput = IO_readInteger(fin);
	gameState->currentPhase = IO_readInteger(fin);

	gameState->message = IO_readString(fin);

	Location_loadEdgeArray(&(gameState->locationEdges), fin);

	gameState->isEnemyDefeated = IO_readBoolArray(fin);
	gameState->isPowerUpUsed = IO_readBoolArray(fin);
	gameState->isSkillUnlocked = IO_readBoolArray(fin);
}

void GameState_deallocate(GameState *gameState) {
	StringUtils_deallocate(gameState->message);
	Array_deallocate(&(gameState->isSkillUnlocked));
	Array_deallocate(&(gameState->locationEdges));
}