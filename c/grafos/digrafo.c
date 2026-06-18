#include <stdio.h>
#include <stdlib.h>

int main() {
    int V, A;
    scanf("%d %d", &V, &A);
    int v1, v2;
    int grau1[V];
    int grau2[V];
    for(int i = 0; i < V; i++){
        grau1[i] = 0;
        grau2[i] = 0;
    }

    for(int i =0; i < A;i++){
        scanf("%d %d", &v1, &v2);
        grau2[v1]++;
        grau1[v2]++;
    }

    for(int i = 0; i < V; i++){
        printf("%d %d\n", grau1[i], grau2[i]);
    }

    
    
    return 0;
}