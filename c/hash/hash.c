#include <stdlib.h>
#include <stdio.h>

// Tipo Abstrato de Dado
typedef struct celula {
    int dado; // Tipo de Informação que eu quero guardar
    int chave;
    struct celula *prox;
} celula;

typedef struct {
    celula **tab; // Vetor de ponteiros -> Array de Listas Encadeadas
    int M;
} hash;

/* Funções HASH
    hash *cria_hash(int M);
    void destruir_hash(hash *h);
    void inserir(hash *h, int ch);
    void remover(hash *h, int ch);
    celula *buscar(hash *h, int ch);
    int fhash(hash *h, int ch);
*/

// Funções Auxiliares de Lista Encadeada
void destroi_lista(celula *lista){
    return;
};
void inserir_lista(celula *lista, int ch){
    return;
};

hash *cria_hash(int M) {
    hash *h = malloc(sizeof(hash));
    h->M = M;

    h->tab = malloc(M * sizeof(celula*)); // Se utilizarmos o 'calloc' (Inicializa tudo como 0 (Null em C) ) o loop 'for' não é necessário
    for (int i = 0; i < M; i++) {
        h->tab[i] = NULL;
    }

    return h;
}

void destruir_hash(hash *h) {
    for (int i = 0; i < h->M; i++) {
        destroi_lista(h->tab[i]); // Recebe uma l.e com nó cabeça e desaloca todos os nós.
    }
    free(h->tab); 
    free(h);
}

int fhash(hash *h, int ch) {
    return ch % h->M;
}

void inserir(hash *h, int ch) {
    int pos = fhash(h, ch);
    inserir_lista(h->tab[pos], ch);

    // insere ch na lista encadeada, mas antes verifica se ela já não está na lista.
    // usar ABBRNE (ou outra autobalanceável).
    // manter a lista encadeada ordenada pela chave.
}

void inserir_BONUS(hash* h, int chave, int dado){
    int i = fhash(h, chave);

    celula* temp = h->tab[i];
    while(temp != NULL){ // Checa se ja tem chave EXATAMENTE igual -> Se tiver cancela operação
        if(temp->chave == chave) return;
        temp = temp->prox;
    }
    free(temp);

    // INSERE CELULA NO INICIO DA 'tab[i]' (Lista do código Hash) --> SEM ORDENAÇÃO
    celula* novo = malloc(sizeof(celula));
    novo->chave = chave;
    novo->dado = dado;
    novo->prox = h->tab[i];
    h->tab[i] = novo;
}

void print_hash_table(hash* h){
    for(int i = 0; i < h->M; i++){
        celula* lista_atual = h->tab[i];
        while(lista_atual != NULL){
            printf("\n Dado %d e Chave %d da Lista com o indice: %d", lista_atual->dado, lista_atual->chave, i);
            lista_atual = lista_atual->prox;
        }
        printf("\n\n --- Indo pra próxima lista do array: %d\n", i+1);
    }
}

int main() {
    
    hash *minha_hash = cria_hash(7); 
    
    // Se M=7, as chaves 1, 8 e 15 vão cair no mesmo índice (resto 1).
    inserir_BONUS(minha_hash, 1, 100);  // índice 1
    inserir_BONUS(minha_hash, 8, 200);  // índice 1 colisão
    inserir_BONUS(minha_hash, 15, 300); // índice 1 colisão
    
    inserir_BONUS(minha_hash, 5, 555);  // índice 5
    inserir_BONUS(minha_hash, 14, 777); // índice 0
    
    // Tentando inserir chave duplicada (deve ser ignorado pela sua verificação)
    inserir_BONUS(minha_hash, 8, 999);  
    
    printf("Imprimindo a Tabela Hash:\n");
    print_hash_table(minha_hash);
    printf("\n");

    return 0;
}
