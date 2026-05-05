#include <stdio.h>
#include <string.h>


void invert(char vec[], char result[]) {
    int n = strlen(vec);
    int x = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        result[x++] = vec[i];
    }
    result[x] = '\0'; 
}

void encryption(char vec[]) {
    int N = strlen(vec);
    char temp[1000];

    
    for (int i = 0; i < N; i++) {
        if(vec[i] >=65 && vec[i] <123)         vec[i] = ( vec[i] + 3 - 32) % 96 + 32;

    }

    
    invert(vec, temp);
    strcpy(vec, temp); 

   
    int meio = N / 2;
    for (int i = meio; i < N; i++) {
        vec[i] = vec[i] - 1;
    }
}

int main() {
    int N;
    char vec[1000];

    
    if (scanf("%d", &N) != 1) return 0;
    
    
    getchar(); 

    for (int i = 0; i < N; i++) {
        
        if (fgets(vec, 1000, stdin)) {
            
            vec[strcspn(vec, "\n")] = 0;

            encryption(vec);
            printf("%s\n", vec);
        }
    }

    return 0;
}