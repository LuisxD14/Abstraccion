#include <cstdio>
#include "mergesort.h"

int main() {
    int arr[100];
    int n, opcion;

    puts("=== Merge Sort ===");
    printf("Cuantos numeros quieres ingresar: ");
    scanf("%d", &n);

    printf("Ingresa los numeros:\n");
    for (int i = 0; i < n; i++) {
        printf("  [%d]: ", i + 1);
        scanf("%d", &arr[i]);
    }

    do {
        puts("\n1. Ver arreglo actual");
        puts("2. Ordenar con Merge Sort");
        puts("3. Salir");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Arreglo: ");
                mostrar(arr, n);
                break;
            case 2:
                mergeSort(arr, 0, n - 1);
                printf("Ordenado: ");
                mostrar(arr, n);
                break;
            case 3:
                puts("Adios!");
                break;
            default:
                puts("Opcion invalida.");
        }
    } while (opcion != 3);

    return 0;
}
