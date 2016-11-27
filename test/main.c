#include <assert.h>
#include <stdio.h>
#include "../src/battle.h"
#include "../src/stringutils.h"
#include "../src/boolean.h"
#include "../src/enemy.h"
#include "../src/player.h"
#include "../src/powerup.h"
#include "../src/utilities.h"

void testArray(const char *executableDirectory);
void testList(const char *executableDirectory);
void testSkillTree(const char *executableDirectory);
//void testPowerUp(const char *executableDirectory);
void testEnemy(const char *executableDirectory);
void testBattle(const char *executableDirectory);

int main (int argc, char *argv[]) {

	printf("\nBRIGHTSOULS - UNIT TESTS\n===========\n");
	printf("Starting tests...\n");

	char *executableDirectory = getExecutableDirectory(argv[0]);

	testArray(executableDirectory);
	testList(executableDirectory);
	testSkillTree(executableDirectory);
	//testPowerUp(executableDirectory);
	testEnemy(executableDirectory);
	testBattle(executableDirectory);
	
	StringUtils_deallocate(executableDirectory);
	printf("Tests completed.\n\n");
	return 0;
}