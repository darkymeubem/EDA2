#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int data;
    struct No* esquerda;
    struct No* direita;
} No;

typedef struct Pilha {
    No** itens;
    int topo;
    int capacidade;
} Pilha;

Pilha* criaPilha(int capacidade) {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->itens = (No**)malloc(capacidade * sizeof(No*));
    p->topo = -1;
    p->capacidade = capacidade;
    return p;
}

int isEmpty(Pilha* p) {
    return p->topo == -1;
}

void push(Pilha* p, No* n) {
    p->topo++;
    p->itens[p->topo] = n;
}

void pop(Pilha* p) {
    if (!isEmpty(p)) p->topo--;
}

No* peek(Pilha* p) {
    if (!isEmpty(p)) return p->itens[p->topo];
    return NULL;
}

void posOrdem(No* raiz) {
    if (raiz == NULL) return;

    Pilha* p = criaPilha(100); // ajuste capacidade conforme necessário
    No* atual = raiz;
    No* ultimoVisitado = NULL;

    while (atual != NULL || !isEmpty(p)) {
        // desce à esquerda
        while (atual != NULL) {
            push(p, atual);
            atual = atual->esquerda;
        }

        No* topo = peek(p);

        // se não tem filho direito ou já processou o direito
        if (topo->direita == NULL || topo->direita == ultimoVisitado) {
            printf("%d ", topo->data);
            pop(p);
            ultimoVisitado = topo;
        } else {
            // ainda falta processar a direita
            atual = topo->direita;
        }
    }
}

int main() {
    // criando uma árvore simples
    No* a = (No*)malloc(sizeof(No)); a->data = 1;
    No* b = (No*)malloc(sizeof(No)); b->data = 2;
    No* c = (No*)malloc(sizeof(No)); c->data = 3;
    No* d = (No*)malloc(sizeof(No)); d->data = 4;

    a->esquerda = b; a->direita = c;
    c->direita = d;
    d->esquerda = d->direita = NULL;
    b->esquerda = b->direita = NULL;
    c->esquerda = NULL;

    printf("Pos-ordem: ");
    posOrdem(a);
    printf("\n");

    return 0;
}