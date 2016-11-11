#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#define ARRAY(T) struct { size_t capacity; size_t itemSize; T *items; }

#define Array_allocate(arrayPointer, initCapacity) Array_allocate_impl((void**) &((arrayPointer)->items), &((arrayPointer)->capacity), &((arrayPointer)->itemSize), sizeof(*((arrayPointer)->items)), initCapacity)
void Array_allocate_impl(void **items, size_t *capacity, size_t *itemSize, size_t newItemSize, size_t initCapacity);

#define Array_resize(arrayPointer, newCapacity) Array_resize_impl((void**) &((arrayPointer)->items), &((arrayPointer)->capacity), &((arrayPointer)->itemSize), newCapacity) 
void Array_resize_impl(void **items, size_t *capacity, const size_t *itemSize, size_t newCapacity);

#define Array_deallocate(arrayPointer) Array_deallocate_impl((void*) (arrayPointer)->items) 
void Array_deallocate_impl(void *items);

#endif