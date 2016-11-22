#include <assert.h>
#include <stdio.h>
#include "../src/boolean.h"
#include "../src/enemy.h"
#include "../src/player.h"

void testArray();
void testList();
void testSkillTree();
void testEnemy();
void testBattle();

int main (int argc, char *argv[]) {

	printf("\nBRIGHTSOULS - UNIT TESTS\n===========\n");
	printf("Starting tests...\n");

	printf("%s\n", argv[0]);

	testArray();
	testList();
	testSkillTree();
	testEnemy();
	testBattle();

	printf("Tests completed.\n\n");
	int x;
	scanf("%d", &x);
	return 0;
}