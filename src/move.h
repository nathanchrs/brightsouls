#ifndef MOVE_H
#define MOVE_H

#include "list.h"
#include "io.h"

#define MOVE_QUEUE_LENGTH 4

typedef LIST(char) MoveQueue;
typedef LIST(MoveQueue) MoveQueueStack;

void MoveQueue_load(MoveQueue *moveQueue, FILE *fin);

void MoveQueueStack_load(MoveQueueStack *moves, FILE *fin);

void MoveQueue_save(const MoveQueue *moveQueue, FILE *fout);

void MoveQueueStack_save(const MoveQueueStack *moves, FILE *fout);

void MoveQueueStack_permute(MoveQueueStack *moves);

void MoveQueue_deallocate(MoveQueue *moveQueue);

void MoveQueueStack_deallocate(MoveQueueStack *moves);

#endif