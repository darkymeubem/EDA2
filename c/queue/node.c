#include "node.h"

#include <stdlib.h>

NoFila *criarNoFila(int valor) {
    NoFila *novoNo = (NoFila *) malloc(sizeof(NoFila));
    if (novoNo == NULL) return NULL;

    novoNo->valor = valor;
    novoNo->prox = NULL;
    return novoNo;
}
