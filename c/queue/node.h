#ifndef NODE_H
#define NODE_H

typedef struct NoFila {
    int valor;
    struct NoFila *prox;
} NoFila;

NoFila *criarNoFila(int valor);

#endif
