#include "array.h"

void Array_allocate_impl(void **items, size_t *capacity, size_t *itemSize, size_t newItemSize, size_t initCapacity) {
	*itemSize = newItemSize;

	*items = malloc(initCapacity * newItemSize);
	if (*items == NULL) {
		*capacity = 0;
	} else {
		*capacity = initCapacity;
	}
}

void Array_resize_impl(void **items, size_t *capacity, const size_t *itemSize, size_t newCapacity) {
	*items = realloc(*items, newCapacity * (*itemSize));
	if (*items == NULL) {
		*capacity = 0;
	} else {
		*capacity = newCapacity;
	}
}

void Array_deallocate_impl(void *items) {
	free(items);
}