#ifndef STRINGINTHASHMAP_H
#define STRINGINTHASHMAP_H

#include <stdlib.h>

typedef struct {
	char *key;
	int value;
} StringIntHashMapElement;

typedef struct {
	size_t capacity;
	size_t size;
	StringIntHashMapElement *items;
} StringIntHashMap;

// Hash map addressing scheme: open addressing - linear next element
// Auto-resize;

StringIntHashMap StringIntHashMap_allocate(const size_t initialSize);

void StringIntHashMap_deallocate(StringIntHashMap *hmap);

void StringIntHashMap_resizeCapacity(StringIntHashMap *hmap, const size_t newSize);

void StringIntHashMap_set(const StringIntHashMap *hmap, const char *key, int value);

int StringIntHashMap_get(StringIntHashMap *hmap, const char *key, int defaultValue);

bool StringIntHashMap_keyExists(StringIntHashMap *hmap, const char *key);

#endif