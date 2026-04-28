#include <cstdio>
#include "pilaLibreria.h"

int main() {
    Pila pila;
    int opcion, valor;

    do {
        puts("\n1. Ver pila");
        puts("2. Agregar");
        puts("3. Quitar");
        puts("4. Salir");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: pila.mostrar(); break;
            case 2:
                printf("Valor: ");
                scanf("%d", &valor);
                pila.agregar(valor);
                break;
            case 3: pila.quitar(); break;
            case 4: puts("Adios!"); break;
            default: puts("Opcion invalida.");
        }
    } while (opcion != 4);

    return 0;
}
