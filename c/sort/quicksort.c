#include <stdio.h>

static void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* Particiona v[esq..dir] com pivô v[dir] (esquema de Lomuto).
   Coloca o pivô na posição de retorno; à esquerda ficam valores <= pivô. */
int separa(int *v, int esq, int dir) {
    int pivo = v[dir];
    int i = esq;
    for (int j = esq; j < dir; j++) {
        if (v[j] <= pivo) {
            troca(&v[i], &v[j]);
            i++;
        }
    }
    troca(&v[i], &v[dir]);
    return i;
}

void quickSort(int *v, int esq, int dir) {
    if (esq < dir) {
        int p = separa(v, esq, dir);
        quickSort(v, esq, p - 1);
        quickSort(v, p + 1, dir);
    }
}

int main(void) {
    int v[] = {7, 2, 9, 1, 5, 3, 8};
    int n = (int)(sizeof v / sizeof v[0]);

    quickSort(v, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    putchar('\n');
    return 0;
}
