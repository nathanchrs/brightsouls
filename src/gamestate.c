#include "gamestate.h"
#include "stringutils.h"
#include <stdio.h>

bool GameState_load(GameState *gameState, const char *filePath) {
	FILE *fin = fopen(filePath, "r");
	if (!fin) return false;
	int i;

	// Load isSkillUnlocked from string of 0's and 1's
	StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
	char *isSkillUnlockedInput = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
	size_t isSkillUnlockedInputLen = StringUtils_strlen(isSkillUnlockedInput);
	Array_allocate(&(gameState->isSkillUnlocked), isSkillUnlockedInputLen);
	gameState->isSkillUnlocked.length = isSkillUnlockedInputLen;
	for (i = 0; i<isSkillUnlockedInputLen; i++) {
		gameState->isSkillUnlocked.items[i] = isSkillUnlockedInput[i] == '1';
	}

	StringUtils_deallocate(isSkillUnlockedInput);
	fclose(fin);
	return true;
}

void GameState_deallocate(GameState *gameState) {
	StringUtils_deallocate(gameState->message);
	Array_deallocate(&(gameState->isSkillUnlocked));
}