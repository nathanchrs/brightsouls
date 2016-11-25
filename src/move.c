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
		Move_loadQueue(moveQueue, fin);
		List_pushLast(moves, moveQueue);
	}
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