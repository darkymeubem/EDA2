#include <stdio.h>

int main(){
    int V, A;
    scanf("%d %d", &V, &A);
    int v1, v2;
    int grau[V];
    for(int i = 0; i < V; i++){
        grau[i] = 0;
    }
    while(scanf("%d %d", &v1, &v2) != EOF){
        grau[v1]++;
        grau[v2]++;
    }
    for(int i = 0; i < V; i++){
        printf("%d\n", grau[i]);
    }
    return 0;
}