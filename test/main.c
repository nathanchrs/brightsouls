#include <assert.h>
#include <stdio.h>
#include "../src/boolean.h"

void testArray();
void testList();
void testSkillTree();

int main (int argc, char *argv[]) {

	printf("\nBRIGHTSOULS - UNIT TESTS\n===========\n");
	printf("Starting tests...\n");

	printf("%s\n", argv[0]);

	testArray();
	testList();
	testSkillTree();

	printf("Tests completed.\n\n");
	return 0;
}