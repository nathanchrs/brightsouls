#ifndef MOVE_H
#define MOVE_H

#include "list.h"
#include "io.h"

#define MOVE_QUEUE_LENGTH 4

typedef LIST(char) MoveQueue;
typedef LIST(MoveQueue) MoveQueueStack;

void Move_loadQueue(MoveQueue *moveQueue, FILE *fin);

void MoveQueue_loadStack(MoveQueueStack *moves, FILE *fin);

void Move_saveQueue(const MoveQueue *moveQueue, FILE *fout);

void MoveQueue_saveStack(const MoveQueueStack *moves, FILE *fout);

#endif