#ifndef LIST_H
#define LIST_H

/* Generic circular doubly-linked list */

#include <stdlib.h>

typedef struct ListNode {
	void *valuePointer;
	struct ListNode *prev;
	struct ListNode *next;
} ListNode;

#define LIST(T) struct { ListNode *head; size_t length; size_t itemSize; T buffer; }

#define ListNode_next(nodePointer) ((nodePointer)->next)
#define ListNode_prev(nodePointer) ((nodePointer)->prev)
#define ListNode_valuePointer(nodePointer) ((nodePointer)->valuePointer)
#define ListNode_value(nodePointer, type) (*((type*) ListNode_valuePointer(nodePointer))) // Read only

/* These can't be used internally since it uses the LIST(T) anonymous struct type */
#define List_first(listPointer) ((listPointer)->head)
#define List_last(listPointer) ((listPointer)->head != NULL ? ListNode_prev((listPointer)->head) : NULL)
#define List_isEmpty(listPointer) ((listPointer)->head == NULL)

#define List_initialize(listPointer) List_initialize_impl(&((listPointer)->head), &((listPointer)->length), &((listPointer)->itemSize), sizeof((listPointer)->buffer))
void List_initialize_impl(ListNode **head, size_t *length, size_t *itemSize, size_t newNodeSize);

#define List_pushFirst(listPointer, value) do { \
	(listPointer)->buffer = (value); \
	List_pushFirst_impl(&((listPointer)->head), &((listPointer)->length), &((listPointer)->itemSize), &((listPointer)->buffer)); \
} while (0)
void List_pushFirst_impl(ListNode **head, size_t *length, const size_t *itemSize, const void *buffer);

#define List_pushLast(listPointer, value) do { \
	(listPointer)->buffer = (value); \
	List_pushLast_impl(&((listPointer)->head), &((listPointer)->length), &((listPointer)->itemSize), &((listPointer)->buffer)); \
} while (0)
void List_pushLast_impl(ListNode **head, size_t *length, const size_t *itemSize, const void *buffer);

#define List_popFirst(listPointer, valuePointer) List_popFirst_impl(&((listPointer)->head), &((listPointer)->length), &((listPointer)->itemSize), (void *) (valuePointer))
void List_popFirst_impl(ListNode **head, size_t *length, const size_t *itemSize, void *valuePointer);

#define List_popLast(listPointer, valuePointer) List_popLast_impl(&((listPointer)->head), &((listPointer)->length), &((listPointer)->itemSize), (void *) (valuePointer))
void List_popLast_impl(ListNode **head, size_t *length, const size_t *itemSize, void *valuePointer);

#define List_rotate(listPointer, rotations) List_rotate_impl(&((listPointer)->head), rotations)
void List_rotate_impl(ListNode **head, int rotations);

#define List_deallocate(listPointer) List_deallocate_impl(&((listPointer)->head))
void List_deallocate_impl(ListNode **head);

#endif