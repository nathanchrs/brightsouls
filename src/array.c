#include "array.h"
#include "utilities.h"

#define ARRAY_ALLOC_BLOCK_SIZE 8

#define ARRAY_GET_ELEMENT_ADDRESS(base, index, itemSize) ((void *) (unsigned long) base + (unsigned long) (index*itemSize))

void Array_allocate_impl(void **items, size_t *length, size_t *capacity, size_t *itemSize, size_t newItemSize, size_t initCapacity) {
	*itemSize = newItemSize;
	*length = 0;

	*items = malloc(initCapacity * newItemSize);
	if (*items == NULL) {
		*capacity = 0;
	} else {
		*capacity = initCapacity;
	}
}

void Array_resize_impl(void **items, size_t *length, size_t *capacity, const size_t *itemSize, size_t newCapacity) {
	*items = realloc(*items, newCapacity * (*itemSize));
	if (*items == NULL) {
		*length = 0;
		*capacity = 0;
	} else {
		*capacity = newCapacity;
		if (*length > newCapacity) *length = newCapacity;
	}
}

void Array_pushBack_impl(void **items, size_t *length, size_t *capacity, const size_t *itemSize, const void *buffer) {
	if ((*length) <= (*capacity)) Array_resize_impl(items, length, capacity, itemSize, (*capacity) + ARRAY_ALLOC_BLOCK_SIZE);
	copyRawBytes(ARRAY_GET_ELEMENT_ADDRESS(*items, *length, *itemSize), buffer, *itemSize);
	(*length)++;
}

void Array_popBack_impl(void **items, size_t *length, size_t *capacity, const size_t *itemSize, void *valuePointer) {
	if ((*length) > 0) (*length)--;
	copyRawBytes(valuePointer, ARRAY_GET_ELEMENT_ADDRESS(*items, *length, *itemSize), *itemSize);
}

void Array_deallocate_impl(void *items, size_t *length, size_t *capacity) {
	free(items);
	*capacity = *length = 0;
}