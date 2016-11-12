#include <assert.h>
#include <stdio.h>
#include "../src/boolean.h"

void testArray();
void testList();

int main () {

	printf("\nBRIGHTSOULS - UNIT TESTS\n===========\n");
	printf("Starting tests...\n");

	testArray();
	testList();

	printf("Tests completed.\n\n");
	return 0;
}