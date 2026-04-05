#include "queue.h"

#include <stdlib.h>

void initQueue(Queue *q) {
    if (q == NULL) return;

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

bool isEmpty(Queue *q){
    return q == NULL || q->size == 0;
}

bool enqueue(Queue *q, int item){
    if (q == NULL) return false;

    NoFila *novoNo = criarNoFila(item);
    if (novoNo == NULL) return false;

    if (q->rear == NULL) {
        q->front = novoNo;
        q->rear = novoNo;
    } else {
        q->rear->prox = novoNo;
        q->rear = novoNo;
    }

    q->size++;

    return true;
}

int dequeue(Queue *q){
    if (q == NULL || isEmpty(q)) return -1;

    NoFila *removido = q->front;
    int valor = removido->valor;
    q->front = removido->prox;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    q->size--;
    free(removido);

    return valor;
}

void freeQueue(Queue *q) {
    if (q == NULL) return;

    NoFila *atual = q->front;
    while (atual != NULL) {
        NoFila *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}
