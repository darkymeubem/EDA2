#include <stdio.h>
#include <stdlib.h>

typedef struct pilha{
    int topo;
    int *data;
    int size;
}pilha;

pilha* criarPilha(int size){
    pilha *p = malloc(sizeof(pilha));
    p->topo = -1;
    p->size = size;
    p->data = malloc(sizeof(int) * size);
    return p;
}

void push(pilha *p, int value){
    if(p->topo < p->size - 1){
        p->topo++;
        p->data[p->topo] = value;
    }
}
int pop(pilha *p){
    if(p->topo >= 0){
        int value = p->data[p->topo];
        p->topo--;
        return value;
    }
    return -1; // pilha vazia
}

int isEmpty(pilha *p){
    return p->topo == -1;
}

int main(){
    int V, A;
    scanf("%d %d", &V, &A);
    int v1, v2;
    int matrix[V][V];
    int visitado[V];
    for(int i = 0; i < V; i++){
        visitado[i] = 0;
        for(int j = 0; j < V; j++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 0; i < A; i++){
        scanf("%d %d", &v1, &v2);
        matrix[v1][v2] = 1;
        matrix[v2][v1] = 1;

    }
    scanf("%d %d", &v1, &v2);
    pilha *p = criarPilha(V * V);
    push(p, v1);
    
    while(!isEmpty(p)){
        int vertice = pop(p);
        if(vertice == v2){
            printf("SIM\n");
            free(p->data);
            free(p);
            return 0;
        }
        if(visitado[vertice] == 0){
            visitado[vertice] = 1;
            for(int i =0; i < V; i++){
                if(matrix[vertice][i] == 1){
                    push(p, i);
                }
            }

        }
    }

    printf("NAO\n");
    free(p->data);
    free(p);
   
    return 0;
}