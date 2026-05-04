#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    RED,
    BLACK
} Color;

typedef struct node {
    int data;
    Color color;
    struct node *left;
    struct node *right;
} node;

node *rotacao_esq(node *no);
node *rotacao_dir(node *no);

void swap(node *a, node *b){
    node temp = *a;
    *a = *b;
    *b = temp;
}

//raiz da arvore é PRETA
node* criaABB(int x){
    node* raiz = malloc(sizeof(node));
    raiz->data = x;
    raiz->color = BLACK;
    raiz->left = NULL;   
    raiz->right = NULL;
    return raiz;
}


node *createnode(int data) {
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->color = RED;
    newnode->left = NULL;   
    newnode->right = NULL;
    return newnode;
}


bool ehVerm(node *no) {
    return no != NULL && no->color == RED;
}



bool ehPreto(node *no) {
    return no == NULL || no->color == BLACK;
}

void sobe_cor(node *no) {
    if (no == NULL) {
        return;
    }
    if (ehVerm(no->left) && ehVerm(no->right)) {
        no->color = RED;
        no->left->color = BLACK;
        no->right->color = BLACK;
    }
}

 nível recebe o `h` já atualizado pelos filhos; você só devolve o novo `h`.
 */
static node *equilibra_apos_inserir(node *h) {
    if (h == NULL) {
        return NULL;
    }
    if (ehVerm(h->right) && !ehVerm(h->left)) {
        h = rotacao_esq(h);
    }
    if (ehVerm(h->left) && ehVerm(h->left->left)) {
        h = rotacao_dir(h);
    }
    if (ehVerm(h->left) && ehVerm(h->right)) {
        sobe_cor(h);
    }
    return h;
}


node *rotacao_esq(node *no) {
    node *a = no->right;
    a->color = no->color;
    no->color = RED;

    node *beta = a->left;
    a->left = no;
    no->right = beta;

    return a;

    
}
node *rotacao_dir(node *no){
    node *a = no->left;
    a->color = no->color;
    no->color = RED;
 
    node *beta = a->right;
    a->right = no;
    no->left = beta;

    return a;
}



node *insertNode(node *raiz, int x) {
    if (raiz == NULL) {
        return createnode(x);
    }
    if (x < raiz->data) {
        raiz->left = insertNode(raiz->left, x);
    } else if (x > raiz->data) {
        raiz->right = insertNode(raiz->right, x);
    }


    return equilibra_apos_inserir(raiz);
}

node *abb_inserir(node *raiz, int x) {
    raiz = insertNode(raiz, x);
    if (raiz != NULL) {
        raiz->color = BLACK;
    }
    return raiz;
}