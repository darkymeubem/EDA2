#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "node.h"

typedef struct {
    NoFila *front;
    NoFila *rear;
    int size;
} Queue;

void initQueue(Queue *q);
bool isEmpty(Queue *q);
bool enqueue(Queue *q, int item);
int dequeue(Queue *q);
void freeQueue(Queue *q);

#endif
