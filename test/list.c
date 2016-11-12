#include <assert.h>
#include <stdio.h>
#include "../src/list.h"

void testList() {

	printf("  Testing List...\n");

	int elmt;

	LIST(int) intList;
	List_initialize(&intList);
	assert(intList.length == 0);
	assert(List_isEmpty(&intList));

	List_pushLast(&intList, 2);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 2);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 2);
	assert(intList.length == 1);

	List_pushFirst(&intList, 1);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 1);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 2);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(List_first(&intList)))) == 2);
	assert(*((int*) ListNode_valuePointer(ListNode_next(List_first(&intList)))) == 2);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_prev(List_first(&intList))))) == 1);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_prev(List_first(&intList))))) == 1);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_next(List_first(&intList))))) == 1);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_next(List_first(&intList))))) == 1);
	assert(intList.length == 2);

	List_pushLast(&intList, 3);
	assert(intList.length == 3);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 1);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_prev(List_first(&intList))))) == 2);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_prev(List_first(&intList))))) == 1);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_next(List_first(&intList))))) == 1);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_next(List_first(&intList))))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_next(ListNode_next(List_first(&intList)))))) == 2);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_next(ListNode_next(List_first(&intList)))))) == 1);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_next(ListNode_prev(List_first(&intList)))))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_next(ListNode_prev(List_first(&intList)))))) == 2);

	List_pushLast(&intList, 4);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 1);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 4);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_prev(List_first(&intList))))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_prev(List_first(&intList))))) == 1);
	assert(intList.length == 4);

	List_pushLast(&intList, 5);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 1);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 5);
	assert(*((int*) ListNode_valuePointer(ListNode_next(List_first(&intList)))) == 2);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_prev(List_first(&intList))))) == 1);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_prev(List_first(&intList))))) == 4);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_prev(List_first(&intList))))) == 1);

	assert(intList.length == 5);

	List_popLast(&intList, &elmt);
	assert(elmt == 5);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 1);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 4);


	assert(intList.length == 4);

	List_popFirst(&intList, &elmt);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 2);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 4);
	assert(intList.length == 3);
	assert(elmt == 1);

	List_popFirst(&intList, &elmt);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 3);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 4);
	assert(intList.length == 2);
	assert(elmt == 2);

	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_prev(List_first(&intList))))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_prev(List_first(&intList))))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_next(List_first(&intList))))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_next(List_first(&intList))))) == 3);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_next(ListNode_next(List_first(&intList)))))) == 4);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_next(ListNode_next(List_first(&intList)))))) == 4);
	assert(*((int*) ListNode_valuePointer(ListNode_prev(ListNode_next(ListNode_prev(List_first(&intList)))))) == 4);
	assert(*((int*) ListNode_valuePointer(ListNode_next(ListNode_next(ListNode_prev(List_first(&intList)))))) == 4);

	List_popLast(&intList, &elmt);
	assert(intList.length == 1);
	assert(elmt == 4);
	assert(*((int*) ListNode_valuePointer(List_first(&intList))) == 3);
	assert(*((int*) ListNode_valuePointer(List_last(&intList))) == 3);	

	List_popFirst(&intList, &elmt);
	assert(List_isEmpty(&intList));
	assert(intList.length == 0);
	assert(elmt == 3);

	printf("  List tested.\n");
}