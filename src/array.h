#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#define ARRAY(T) struct { T *items; size_t length; size_t capacity; size_t itemSize; T buffer; }

#define Array_first(arrayPointer) (((arrayPointer)->items)[0])
#define Array_last(arrayPointer) (((arrayPointer)->items)[((arrayPointer)->length - 1)])
#define Array_isEmpty(arrayPointer) ((arrayPointer)->length == 0)

#define Array_allocate(arrayPointer, initCapacity) Array_allocate_impl((void**) &((arrayPointer)->items), &((arrayPointer)->length), &((arrayPointer)->capacity), &((arrayPointer)->itemSize), sizeof((arrayPointer)->buffer), initCapacity)
void Array_allocate_impl(void **items, size_t *length, size_t *capacity, size_t *itemSize, size_t newItemSize, size_t initCapacity);

#define Array_resize(arrayPointer, newCapacity) Array_resize_impl((void**) &((arrayPointer)->items), &((arrayPointer)->length), &((arrayPointer)->capacity), &((arrayPointer)->itemSize), newCapacity) 
void Array_resize_impl(void **items, size_t *length, size_t *capacity, const size_t *itemSize, size_t newCapacity);

#define Array_pushBack(arrayPointer, value) do { \
	(arrayPointer)->buffer = (value); \
	Array_pushBack_impl((void**) &((arrayPointer)->items), &((arrayPointer)->length), &((arrayPointer)->capacity), &((arrayPointer)->itemSize), (void *) &((arrayPointer)->buffer)); \
} while (0)
void Array_pushBack_impl(void **items, size_t *length, size_t *capacity, const size_t *itemSize, const void *buffer);

#define Array_popBack(arrayPointer, valuePointer) Array_popBack_impl((void**) &((arrayPointer)->items), &((arrayPointer)->length), &((arrayPointer)->capacity), &((arrayPointer)->itemSize), (void *) (valuePointer))
void Array_popBack_impl(void **items, size_t *length, size_t *capacity, const size_t *itemSize, void *valuePointer);

#define Array_deallocate(arrayPointer) Array_deallocate_impl((void*) (arrayPointer)->items, &((arrayPointer)->length), &((arrayPointer)->capacity))
void Array_deallocate_impl(void *items, size_t *length, size_t *capacity);

#endif