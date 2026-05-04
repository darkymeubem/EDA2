#include <stdio.h>
#include <stdlib.h>

// 0 1 2 3 4 5  6 7 8 
// 3 6 7 8 9 11 3 5 7 

typedef struct{
    int *data;
    int n, tam;
}heap;

static void libera_heap(heap *fp) {
    if (!fp)
        return;
    free(fp->data);
    free(fp);
}

heap *criaHeap(int tam){
    heap *fp = (heap *) malloc(sizeof(heap));
    fp->data = (int *) malloc(tam * sizeof(int));
    fp->n = 0;
    fp->tam = tam;
    return fp;
}

int getLeftChildrenIndex(int x){
    return 2*x + 1;
}

int getRightChildrenIndex(int x){
    return 2*x + 2;
}

int getParentIndex(int x){
    return (x-1)/2;
}

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int has_left_child(heap *fp, int x) {
    return getLeftChildrenIndex(x) < fp->n;
}

int has_right_child(heap *fp, int x) {
    return getRightChildrenIndex(x) < fp->n;
}

void shift_up(heap *fp, int x) {
    int *arr = fp->data;
    while (x > 0) {
        int pai = getParentIndex(x);
        if (arr[x] <= arr[pai])
            break;
        swap(&arr[x], &arr[pai]);
        x = pai;
    }
}

void shift_down(heap *fp, int x) {
    int *arr = fp->data;
    while(has_left_child(fp, x)){
        int maior = getLeftChildrenIndex(x);
        if(has_right_child(fp, x) && arr[getLeftChildrenIndex(x)] < arr[getRightChildrenIndex(x)]){
            maior = getRightChildrenIndex(x);
        }
        if(arr[x] >= arr[maior]){
            break;
        }
        swap(&arr[x], &arr[maior]);
        x = maior;
    }
}

void insert(heap *fp, int x) {
    if (fp->n >= fp->tam)
        return;
    int idx = fp->n++;
    fp->data[idx] = x;
    shift_up(fp, idx);
}

int heap_pop(heap *fp) {
    if (fp->n == 0) {
        fprintf(stderr, "heap_pop: heap vazio\n");
        exit(EXIT_FAILURE);
    }
    int *arr = fp->data;
    int res = arr[0];
    arr[0] = arr[fp->n - 1];
    fp->n--;
    shift_down(fp, 0);
    return res;
}

void print_heap(heap *fp) {
    for (int i = 0; i < fp->n; i++)
        printf("%d ", fp->data[i]);
    printf("\n");
}

int main(void) {
    heap *h = criaHeap(16);
    int in[] = {3, 9, 1, 7, 4, 8};
    int n_in = (int)(sizeof in / sizeof in[0]);
    int esperado[] = {9, 8, 7, 4, 3, 1};
    for (int i = 0; i < n_in; i++)
        insert(h, in[i]);
    if (h->n != n_in) {
        printf("falhou: n apos insercoes: esperado %d, obteve %d\n", n_in, h->n);
        libera_heap(h);
        return 1;
    }
    printf("arranjo apos insercoes: ");
    print_heap(h);
    for (int i = 0; i < n_in; i++) {
        int v = heap_pop(h);
        if (v != esperado[i]) {
            printf("falhou na extracao %d: esperado %d, obteve %d\n", i, esperado[i], v);
            libera_heap(h);
            return 1;
        }
    }
    if (h->n != 0) {
        printf("falhou: heap deveria estar vazio (n=%d)\n", h->n);
        libera_heap(h);
        return 1;
    }
    printf("teste heap_max: ok (%d extracoes em ordem decrescente)\n", n_in);
    libera_heap(h);
    return 0;
}