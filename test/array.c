#include <assert.h>
#include <stdio.h>
#include "../src/array.h"

void testArray() {

	printf("  Testing Array...\n");

	int i;

	ARRAY(int) intArray;
	Array_allocate(&intArray, 5);
	assert(intArray.capacity == 5);
	for (i = 0; i < intArray.capacity; i++) intArray.items[i] = i;
	for (i = 0; i < intArray.capacity; i++) assert(intArray.items[i] == i);
	
	Array_resize(&intArray, 3);
	assert(intArray.capacity == 3);
	assert(intArray.items[2] == 2);
	assert(intArray.items[0] == 0);

	ARRAY(long long) longlongArray;
	Array_allocate(&longlongArray, 5);
	assert(longlongArray.capacity == 5);
	for (i = 0; i < longlongArray.capacity; i++) longlongArray.items[i] = i;
	for (i = 0; i < longlongArray.capacity; i++) assert(longlongArray.items[i] == i);

	printf("  Array tested.\n");
}