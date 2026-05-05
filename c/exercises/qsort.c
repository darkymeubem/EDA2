#include <stdio.h>
#include <stdlib.h>
//void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));
int compararInts(const void *a, const void *b){
    int cA = *(const int*)a;
    int cB = *(const int*)b;
    if(cA > cB) return 1;
    else if(cA < cB) return -1;
    else return 0;
}

void printArray(int *arr, int n){
    for(int i =0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main(){
    int arr[] = {4,1,5,3,11,9,7,14,3};
    int n = (sizeof(arr)/sizeof(arr[0]));
    printArray(arr,n);
    qsort(arr, n, sizeof(int), compararInts);

    printArray(arr, n);
}
