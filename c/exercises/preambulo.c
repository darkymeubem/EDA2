#include <stdio.h>
#include <string.h>

typedef struct EDA {
    int count;
    char letra;
    int posicao;
} EDA;

static EDA aux[100000];

/* Retorna 1 se a deve vir antes de b na ordenação final. */
static int vem_antes(EDA a, EDA b) {
    if (a.count != b.count) return a.count > b.count;   /* count desc */
    return a.posicao < b.posicao;                       /* estável no empate */
}

static void merge_sort(EDA v[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort(v, l, m);
    merge_sort(v, m + 1, r);

    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (vem_antes(v[i], v[j])) aux[k++] = v[i++];
        else aux[k++] = v[j++];
    }
    while (i <= m) aux[k++] = v[i++];
    while (j <= r) aux[k++] = v[j++];
    for (i = l; i <= r; i++) v[i] = aux[i];
}

int main(void) {
    static char string[100001];
    if (scanf("%100000s", string) != 1) return 0;
    int n = (int)strlen(string);
    static EDA eda[100000];
    int pos = 0;

    /* Monta blocos consecutivos: ex. "aabbbcaaaa" -> aa, bbb, c, aaaa */
    for (int i = 0; i < n; ) {
        int inicio = i;
        int qtd = 1;
        while (i + 1 < n && string[i + 1] == string[i]) {
            qtd++;
            i++;
        }
        eda[pos].letra = string[inicio];
        eda[pos].posicao = inicio;
        eda[pos].count = qtd;
        pos++;
        i++;
    }

    if (pos > 1) {
        merge_sort(eda, 0, pos - 1);
    }

    for (int i = 0; i < pos; i++) {
        printf("%d %c %d\n", eda[i].count, eda[i].letra, eda[i].posicao);
    }
    return 0;
}
