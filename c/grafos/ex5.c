#include <stdio.h>

int main(){
    int V, A;
    scanf("%d %d", &V, &A);
    int v1, v2;
    int matrix[V][V];

    for(int i = 0; i < V; i++){
        
        for(int j = 0; j < V; j++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 0; i < A; i++){
        scanf("%d %d", &v1, &v2);
        matrix[v1][v2] = 1;
        matrix[v2][v1] = 1;

    }
    int a;
    scanf("%d", &a);
    
    for(int i =0; i < V; i++){
        if(matrix[a][i] == 1){
            printf("%d ", i);
        }
    }
   
    return 0;
}