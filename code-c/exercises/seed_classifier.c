#include <stdio.h>
#include <stdlib.h>

typedef struct seed{
    long int id;
    long int q;
}seed;

long int valor(seed s, char c){
    if(c == 'i') return s.id;
    return s.q;
}
int cmp(long int a, long int b){
    if(a < b) return -1;
    if(a > b) return 1;
    return 0;
}
void swap(seed *a, seed *b){
    seed temp = *a;
    *a = *b;
    *b = temp;
}

int cmp_seed_id(const void *a, const void *b){
    const seed *sa = (const seed*)a;
    const seed *sb = (const seed*)b;
    if (sa->id < sb->id) return -1;
    if (sa->id > sb->id) return 1;
    return 0;
}

int median_of_three(seed *arr, int low, int high, char c) {
    int mid = low + (high - low) / 2;
    long int a = valor(arr[low], c);
    long int b = valor(arr[mid], c);
    long int d = valor(arr[high], c);
    // Retorna o índice do valor mediano
    if ((a <= b && b <= d) || (d <= b && b <= a)) return mid;
    if ((b <= a && a <= d) || (d <= a && a <= b)) return low;
    return high;
}

int separa_medina(int esq, int dir, seed *arr, char c){
    int pivot_index = median_of_three(arr, esq, dir, c);
    swap(&arr[dir], &arr[pivot_index]);

    long int pivot = valor(arr[dir], c);
    int i = esq;
    for(int j = esq; j < dir; j++)
    {
        if (valor(arr[j], c) < pivot ||
            (valor(arr[j], c) == pivot && cmp(arr[j].id, arr[dir].id) < 0)) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    //colocando pivo na posição certa
    swap(&arr[i], &arr[dir]);
    return i;
}

void quickSelect(seed *arr, int esq, int dir, int k, char c){
    if(esq < dir){
        int pivo = separa_medina(esq, dir, arr, c);
        if(k < pivo) quickSelect(arr, esq, pivo - 1, k, c);
        else if(k > pivo) quickSelect(arr, pivo + 1, dir, k, c);
    }
}
int main(){
    int k;
    scanf("%d", &k);

    int cap = 1024;      
    int n = 0;          
    seed *v = malloc((size_t)cap * sizeof(seed));
    if (!v) return 1;

    while (scanf("%ld %ld", &v[n].id, &v[n].q) == 2) {
        n++;
        if (n == cap) {
            cap *= 2;
            seed *tmp = realloc(v, (size_t)cap * sizeof(seed));
            if (!tmp) {
                free(v);
                return 1;
            }
            v = tmp;
        }
    }

    if (k > n) k = n;
    if (k > 0 && n > 0) {
        quickSelect(v, 0, n-1, k - 1, 'q');
    }
    qsort(v, (size_t)k, sizeof(seed), cmp_seed_id);

    for(int i =0; i < k; i++){
        printf("%ld %ld\n", v[i].id, v[i].q);
    }
    free(v);
    return 0;
}