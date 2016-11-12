#include <assert.h>
#include <stdio.h>
#include "../src/array.h"

void testArray() {

	printf("  Testing Array...\n");

	int i, elmt;

	ARRAY(int) intArray;
	Array_allocate(&intArray, 5);
	assert(Array_isEmpty(&intArray));
	assert(intArray.length == 0);
	assert(intArray.capacity == 5);

	Array_pushBack(&intArray, 0);
	for (i = 1; i < 10; i++) Array_pushBack(&intArray, i);
	assert(intArray.length == 10);
	assert(intArray.capacity >= intArray.length);
	for (i = 0; i < 10; i++) assert(intArray.items[i] == i);

	Array_popBack(&intArray, &elmt);
	assert(elmt == 9);
	assert(intArray.length == 9);

	Array_popBack(&intArray, &elmt);
	assert(elmt == 8);
	assert(intArray.length == 8);

	Array_resize(&intArray, 3);
	assert(intArray.capacity == 3);
	assert(intArray.length == 3);
	assert(intArray.items[2] == 2);
	assert(intArray.items[0] == 0);

	ARRAY(long long) longlongArray;
	Array_allocate(&longlongArray, 5);
	assert(longlongArray.length == 0);
	assert(longlongArray.capacity == 5);
	for (i = 0; i < longlongArray.capacity; i++) longlongArray.items[i] = i;
	for (i = 0; i < longlongArray.capacity; i++) assert(longlongArray.items[i] == i);

	printf("  Array tested.\n");
}