#include <assert.h>
#include <stdio.h>
#include "../src/boolean.h"

void testArray();
void testList();
void testSkillTree();

int main () {

	printf("\nBRIGHTSOULS - UNIT TESTS\n===========\n");
	printf("Starting tests...\n");

	testArray();
	testList();
	testSkillTree();

	printf("Tests completed.\n\n");
	return 0;
}