#include "move.h"
#include "utilities.h"
#include "stringutils.h"

void MoveQueue_load(MoveQueue *moveQueue, FILE *fin) {
	List_initialize(moveQueue);
	char *input = IO_readString(fin);
	int i;
	for (i = 0; i < StringUtils_strlen(input); i++) {
		List_pushLast(moveQueue, input[i]);
	}
	StringUtils_deallocate(input);
}

void MoveQueueStack_load(MoveQueueStack *moves, FILE *fin) {
	List_initialize(moves);
	int n, i;
	n = IO_readInteger(fin);
	for (i = 0; i < n; i++) {
		MoveQueue moveQueue;
		MoveQueue_load(&moveQueue, fin);
		List_pushLast(moves, moveQueue);
	}
}

MoveQueue MoveQueue_clone(MoveQueue *moveQueue) {
	MoveQueue newMoveQueue;
	List_initialize(&newMoveQueue);
	int i;
	for (i = 0; i < moveQueue->length; i++) {
		char tmp;
		List_popFirst(moveQueue, &tmp);
		List_pushLast(&newMoveQueue, tmp);
		List_pushLast(moveQueue, tmp);
	}
	return newMoveQueue;
}

MoveQueueStack MoveQueueStack_clone(MoveQueueStack *moves) {
	MoveQueueStack newMoves;
	List_initialize(&newMoves);
	int i;
	for (i = 0; i < moves->length; i++) {
		MoveQueue tmp;
		List_popFirst(moves, &tmp);
		List_pushLast(&newMoves, MoveQueue_clone(&tmp));
		List_pushLast(moves, tmp);
	}
	return newMoves;
}

void MoveQueueStack_permute(MoveQueueStack *moves) {
	MoveQueue swap;
	int i;
	for (i = 0; i < moves->length; i++) {
		List_rotate(moves, getRandomInt(1, moves->length));
		List_popFirst(moves, &swap);
		List_rotate(moves, getRandomInt(1, moves->length));
		List_pushFirst(moves, swap);
	}
}

void MoveQueue_deallocate(MoveQueue *moveQueue) {
	List_deallocate(moveQueue);
}

void MoveQueueStack_deallocate(MoveQueueStack *moves) {
	int i;
	MoveQueue tmp;
	for (i = 0; i < moves->length; i++) {
		List_popFirst(moves, &tmp);
		List_deallocate(&tmp);
	}
	List_deallocate(moves);
}