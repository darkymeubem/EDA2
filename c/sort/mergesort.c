#include <stdio.h>

void merge(int A[], int low, int high, int mid)
{
    int i, j, k, c[5000];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (A[i] < A[j])
        {
            c[k] = A[i];
            k++;
            i++;
        }
        else
        {
            c[k] = A[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k] = A[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = A[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        A[i] = c[i];
    }
}


static void merge(int arr[], int left, int mid, int right) {
    int aux[right - left + 1];

    for (int i = left; i <= right; i++) {
        aux[i - left] = arr[i];
    }

    int i = 0;
    int j = mid - left + 1;
    int left_end = mid - left;
    int right_end = right - left;
    int k = left;

    while (i <= left_end && j <= right_end) {
        if (aux[i] <= aux[j]) {
            arr[k++] = aux[i++];
        } else {
            arr[k++] = aux[j++];
        }
    }

    while (i <= left_end) {
        arr[k++] = aux[i++];
    }

    while (j <= right_end) {
        arr[k++] = aux[j++];
    }
}

void merge_sort(int arr[], int left, int right) {
    if(left < right){
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    return;
}

static void print_array(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    printf("Antes: ");
    print_array(arr, n);

    merge_sort(arr, 0, n - 1);

    printf("Depois: ");
    print_array(arr, n);

    return 0;
}
