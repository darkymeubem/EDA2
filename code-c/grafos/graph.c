#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

#include "graph.h"
#include "../queue/queue.h"

grafo *criarGrafo(int vertices){
    grafo *g = malloc(sizeof(grafo));
    if (g == NULL) return NULL;

    g->numVertices = vertices;
    g->numArestas = 0;

    g->listaAdj = (No**) malloc(vertices * sizeof(No *));
    if (g->listaAdj == NULL) {
        free(g);
        return NULL;
    }

    for(int i =0; i < vertices; i++){
        g->listaAdj[i] = NULL;
    }

    return g;
}

static No *criarNo(int vertice) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->vertice = vertice;
    novo->prox = NULL;
    return novo;
}

// essa função insere no começo e tem custo O(1) -- Grafo não direcionado
// o e d são os valores dos vertices (nós)
void inserirAresta(grafo *g, int o, int d){
    if (g == NULL) return;
    if(o < d) return; //evita duplicata

    No *origem = criarNo(o);
    No *destino = criarNo(d);
    if (origem == NULL || destino == NULL) {
        free(origem);
        free(destino);
        return;
    }

    //insere na origem
    origem->prox = g->listaAdj[d];
    g->listaAdj[d] = origem;

    //insere no destino o: d -> d: o
    destino->prox = g->listaAdj[o];
    g->listaAdj[o] = destino;

    g->numArestas++;

}
//Custo O(k): k é o numero de vizinhos
int grauVertice(grafo *g, int v){
    No *node = g->listaAdj[v];
    int grau = 0;
    while(node != NULL){
        grau++;
        node = node->prox;
    }
    return grau;

}

int grauMaximo(grafo *g){
    int max = 0;
    for(int i =0; i < g->numVertices; i++){
        int grau = grauVertice(g, i);
        if(max < grau) max = grau;
    }
    return max;
}

int numeroArestas(grafo *g){
    return g->numArestas;
}

// raiz é o vertice de onde a bfs começa
void bfs(grafo *g){
    if(g == NULL) return;
    int visitado[g->numVertices];
    for(int i =0; i < g->numVertices; i++){
        visitado[i] = 0;
    }
    Queue *f;
    initQueue(f);


    for(int s = 0; s < g->numVertices; s++){
        if(!visitado[s]){
            visitado[s] = 1;
            enqueue(f,s);

            while(!isEmpty(f)){
                int u = dequeue(f);
                printf("%d -> ", u);
                No *aux = g->listaAdj[u];
                while(aux != NULL){
                    if(!visitado[aux->vertice]){
                        visitado[aux->vertice] = 1;
                        enqueue(f, aux->vertice);
                    }

                    aux = aux ->prox;

                }
            }
        }
    }
}