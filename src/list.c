#include "list.h"
#include <stdio.h>
#include "utilities.h"

ListNode* List_allocateNode(const size_t *itemSize, const void *valuePointer) {
	void *tmp = malloc(*itemSize);
	if (tmp != NULL) {
		ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
		newNode->valuePointer = tmp;
		copyRawBytes(newNode->valuePointer, valuePointer, *itemSize);
		newNode->prev = NULL;
		newNode->next = NULL;
		return newNode;
	} else {
		return NULL;
	}
}

void List_deallocateNode(ListNode *item) {
	free(item->valuePointer);
	free(item);
}

void List_initialize_impl(ListNode **head, size_t *length, size_t *itemSize, size_t newNodeSize) {
	*itemSize = newNodeSize;
	*length = 0;
	*head = (ListNode *) NULL;
}

void List_pushFirst_impl(ListNode **head, size_t *length, const size_t *itemSize, const void *buffer) {
	ListNode *newNode = List_allocateNode(itemSize, buffer);
	if (newNode != NULL) {
		if (*head == NULL) { // empty list
			*head = ListNode_next(newNode) = ListNode_prev(newNode) = newNode;
		} else {
			ListNode_next(newNode) = *head;
			ListNode_prev(newNode) = ListNode_prev(*head);
			ListNode_next(ListNode_prev(newNode)) = ListNode_prev(ListNode_next(newNode)) = newNode;
			*head = newNode;
		}
		(*length)++;
	}
}

void List_pushLast_impl(ListNode **head, size_t *length, const size_t *itemSize, const void *buffer) {
	List_pushFirst_impl(head, length, itemSize, buffer);
	*head = ListNode_next(*head);
}

void List_popFirst_impl(ListNode **head, size_t *length, const size_t *itemSize, void *valuePointer) {
	if (*head != NULL) {
		ListNode *poppedNode = *head;
		if (ListNode_next(*head) != *head) { // list has more than one element
			ListNode_next(ListNode_prev(*head)) = ListNode_next(*head);
			ListNode_prev(ListNode_next(*head)) = ListNode_prev(*head);
			*head = ListNode_next(*head);
		} else {
			*head = NULL;
		}
		copyRawBytes(valuePointer, poppedNode->valuePointer, *itemSize);
		(*length)--;
		List_deallocateNode(poppedNode);
	}
}

void List_popLast_impl(ListNode **head, size_t *length, const size_t *itemSize, void *valuePointer) {
	if (*head != NULL) {
		*head = ListNode_prev(*head);
		List_popFirst_impl(head, length, itemSize, valuePointer);
	}
}
