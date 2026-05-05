#ifndef GRAPH_H
#define GRAPH_H

typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct grafo{
    int numVertices;
    int numArestas;
    No **listaAdj;
}grafo;

grafo *criarGrafo(int vertices);
void inserirAresta(grafo *g, int o, int d);
int grauVertice(grafo *g, int v);
int grauMaximo(grafo *g);
int numeroArestas(grafo *g);

#endif
