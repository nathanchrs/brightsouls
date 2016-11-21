#include <assert.h>
#include <stdio.h>
#include "../src/boolean.h"
#include "../src/enemy.h"
#include "../src/player.h"

void testArray();
void testList();
void testSkillTree();
void testEnemy(Enemy *enemy);
void testBattle(Enemy *enemy, Player *player);

int main (int argc, char *argv[]) {

	printf("\nBRIGHTSOULS - UNIT TESTS\n===========\n");
	printf("Starting tests...\n");

	printf("%s\n", argv[0]);

	testArray();
	testList();
	testSkillTree();

	Enemy enemy;
	Player player;
	player.name = "Player 1";
	player.str = 10;
	player.def = 3;
	player.exp = 0;
	testEnemy(&enemy);
	//testBattle(&enemy, &player);

	printf("Tests completed.\n\n");
	int x;
	scanf("%d", &x);
	return 0;
}