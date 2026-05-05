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

/* 
 * Ajuste na lógica ehPreto:
 * Em LLRB, ponteiros NULL são considerados pretos.
 */
bool ehPreto(node *no) {
    if (no == NULL) return true; 
    return no->color == BLACK;
}

/* 
 * O ehVerm já estava correto, mas é o oposto lógico do ehPreto 
 */
bool ehVerm(node *no) {
    if (no == NULL) return false;
    return no->color == RED;
}

node *createnode(int data) {
    node *newnode = (node *)malloc(sizeof(node));
    if (newnode) {
        newnode->data = data;
        newnode->color = RED; // Novos nós sempre nascem vermelhos
        newnode->left = NULL;   
        newnode->right = NULL;
    }
    return newnode;
}

/* 
 * Inverte as cores do nó e de seus dois filhos.
 * Usado quando ambos os filhos são vermelhos.
 */
void sobe_cor(node *no) {
    if (no == NULL) return;
    no->color = RED;
    if (no->left) no->left->color = BLACK;
    if (no->right) no->right->color = BLACK;
}

node *rotacao_esq(node *no) {
    node *x = no->right;
    no->right = x->left;
    x->left = no;
    x->color = no->color;
    no->color = RED;
    return x;
}

node *rotacao_dir(node *no) {
    node *x = no->left;
    no->left = x->right;
    x->right = no;
    x->color = no->color;
    no->color = RED;
    return x;
}

/*
 * Mantém as propriedades da LLRB (Left-Leaning Red-Black)
 */
node *equilibra_apos_inserir(node *h) {
    if (h == NULL) return NULL;

    // Caso 1: Filho direito vermelho (inclinação incorreta) -> rotaciona esquerda
    if (ehVerm(h->right) && !ehVerm(h->left)) {
        h = rotacao_esq(h);
    }
    
    // Caso 2: Dois vermelhos seguidos à esquerda -> rotaciona direita
    if (ehVerm(h->left) && ehVerm(h->left->left)) {
        h = rotacao_dir(h);
    }
    
    // Caso 3: Ambos os filhos vermelhos -> sobe a cor (color flip)
    if (ehVerm(h->left) && ehVerm(h->right)) {
        sobe_cor(h);
    }

    return h;
}

node *insertNode(node *raiz, int x) {
    if (raiz == NULL) return createnode(x);

    if (x < raiz->data) {
        raiz->left = insertNode(raiz->left, x);
    } else if (x > raiz->data) {
        raiz->right = insertNode(raiz->right, x);
    }
    // duplicatas são ignoradas

    return equilibra_apos_inserir(raiz);
}

node *abb_inserir(node *raiz, int x) {
    raiz = insertNode(raiz, x);
    if (raiz != NULL) {
        raiz->color = BLACK; // A raiz deve ser sempre preta após a inserção
    }
    return raiz;
}

int altura_negra(node *no) {
    if (no == NULL) {
        return 1; // O nó NULL (folha externa) é preto
    }

    // Calculamos a altura do filho (pode ser qualquer um, escolhi esquerda)
    int altura_filho = altura_negra(no->left);

    // Se o nó atual for PRETO, incrementamos a altura vinda de baixo
    if (ehPreto(no)) {
        return 1 + altura_filho;
    } else {
        return altura_filho; // Nó vermelho não aumenta a altura negra
    }
}

int verifica_consistencia_negra(node *no) {
    if (no == NULL) return 1;

    int alt_esq = verifica_consistencia_negra(no->left);
    int alt_dir = verifica_consistencia_negra(no->right);

    // Se algum lado falhou ou as alturas são diferentes, a árvore está corrompida
    if (alt_esq == -1 || alt_dir == -1 || alt_esq != alt_dir) {
        return -1; 
    }

    // Se o nó atual é preto, soma 1, se é vermelho, apenas passa adiante
    return ehPreto(no) ? alt_esq + 1 : alt_esq;
}