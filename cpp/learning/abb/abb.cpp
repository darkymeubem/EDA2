#include <iostream>

using namespace std;

struct node {
    int data;
    node *esq;
    node *dir;
};

class ABB {
private:
    node* root;

    // Usando 'new' do C++ ao invés de 'malloc' do C. O código fica bem mais limpo.
    node* createABB(int x) {
        node* raiz = new node; 
        raiz->data = x;
        raiz->esq = nullptr;
        raiz->dir = nullptr;
        return raiz;
    }

    void insertNode(node*& raiz, int x) {
        if (raiz == nullptr) {
            raiz = createABB(x);
            return;
        }
        if (x < raiz->data)
            insertNode(raiz->esq, x);
        else if (x > raiz->data)
            insertNode(raiz->dir, x);
    }

    // Corrigido: Removido o "return raiz;" no final, já que a função é void.
    // Dica: Não precisa fazer swap (troca) usando variável 'temp', 
    // basta sobrescrever o valor da raiz com o valor do sucessor.
    void removerSucessor(node* raiz) {
        node* filho = raiz->dir;
        node* pai = raiz;
        
        while (filho->esq != nullptr) {
            pai = filho;
            filho = filho->esq;
        }
        
        raiz->data = filho->data; // Copia o valor do sucessor para o nó atual
        
        if (pai == raiz)
            pai->dir = filho->dir;
        else
            pai->esq = filho->dir;
            
        delete filho; // Usando 'delete' no lugar de 'free'
    }

    node* removeNode(node *raiz, int x){
        if(raiz == nullptr) {
            return nullptr; // Corrigido: Se a árvore for vazia ou o nó não existir, retorna nulo.
        }

        // Buscando nó
        if(x < raiz->data) {
            raiz->esq = removeNode(raiz->esq, x);
        }
        else if(x > raiz->data) {
            raiz->dir = removeNode(raiz->dir, x);
        }
        // Nó encontrado!
        else {
            // Caso 1 e 2: Apenas um filho ou nenhum (folha)
            if(raiz->esq == nullptr){
                node *ptr = raiz->dir;
                delete raiz; // Usando 'delete'
                return ptr;
            }
            else if(raiz->dir == nullptr){
                node *ptr = raiz->esq;
                delete raiz; // Usando 'delete'
                return ptr;
            }
            // Caso 3: Dois filhos
            else {
                removerSucessor(raiz);
                // Importante: A função removerSucessor não altera o endereço da 'raiz', 
                // apenas o seu conteúdo. Portanto, a raiz continua no mesmo lugar.
            }
        }
        
        return raiz; // Corrigido: Retorna a raiz atualizada para que a recursão reconecte a árvore.
    }
    void destroyTree(node *raiz){
        if(raiz != nullptr){
            destroyTree(raiz->esq);
            destroyTree(raiz->dir);
            delete raiz;
        }
    }
    int altura(node* raiz) {
        if (raiz == nullptr)
            return -1;
        int hEsq = altura(raiz->esq);
        int hDir = altura(raiz->dir);
        return 1 + (hEsq > hDir ? hEsq : hDir);
    }

public:
    ABB() : root(nullptr) {}
    ABB(int x) : root(createABB(x)) {}

    void insert(int x) { insertNode(root, x); }
    void remove(int x) { root = removeNode(root, x); }
    void destroy() { destroyTree(root); }
    int altura() { return altura(root); }
  
};
