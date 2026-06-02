#include <cstdio>
#include "mergesort.h"

void merge(int arr[], int izq, int mid, int der) {
    int n1 = mid - izq + 1;
    int n2 = der - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[izq + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = izq;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int izq, int der) {
    if (izq < der) {
        int mid = (izq + der) / 2;
        mergeSort(arr, izq, mid);
        mergeSort(arr, mid + 1, der);
        merge(arr, izq, mid, der);
    }
}

void mostrar(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    puts("");
}
