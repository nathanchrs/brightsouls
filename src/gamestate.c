#include "gamestate.h"
#include "array.h"
#include "boolean.h"
#include "stringutils.h"
#include <stdio.h>

typedef ARRAY(bool) BoolArray;

/* Load a boolean array from string of 0's and 1's in file */
void loadBoolArray(BoolArray *array, FILE *fin) {
	StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
	char *input = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
	size_t inputLen = StringUtils_strlen(input);
	Array_allocate(array, inputLen);
	for (i = 0; i < inputLen; i++) {
		if (input[i] == '0') Array_pushBack(array, false);
		else if (input[i] == '1') Array_pushBack(array, true);
	}
	StringUtils_deallocate(input);
}

bool GameState_load(GameState *gameState, const char *filePath) {
	FILE *fin = fopen(filePath, "r");
	if (!fin) return false;
	int inp;

	// DateTime_load(&(gameState->lastSaveTime), fin);
	
	fscanf(fin, "%d", &inp);
	gameState->requestInput = inp;

	fscanf(fin, "%d", &inp);
	gameState->currentPhase = inp;

	// StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
	// gameState->message = StringUtils_scan(fin, STRINGUTILS_NEWLINE);

	Location_loadEdgeArray(&(gameState->locationEdges), fin);

	loadBoolArray(&(gameState->isEnemyDefeated));
	loadBoolArray(&(gameState->isPowerUpUsed));
	loadBoolArray(&(gameState->isSkillUnlocked));

	fclose(fin);
	return true;
}

void GameState_deallocate(GameState *gameState) {
	StringUtils_deallocate(gameState->message);
	Array_deallocate(&(gameState->isSkillUnlocked));
	Array_deallocate(&(gameState->locationEdges));
}