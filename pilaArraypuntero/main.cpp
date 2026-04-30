#include <cstdio>
#include "pilaPuntero.h"

int main() {
    Pila pila;
    int opcion, valor;

    do {
        puts("\n===== MENU PILA =====");
        puts("1. Agregar elemento");
        puts("2. Quitar elemento");
        puts("3. Mostrar pila");
        puts("4. Verificar si esta vacia");
        puts("5. Verificar si esta llena");
        puts("6. Mostrar tamanio de la pila");
        puts("7. Salir");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                pila.agregar(valor);
                break;
            case 2: pila.quitar(); break;
            case 3: pila.mostrar(); break;
            case 4:
                if (pila.estaVacia())
                    puts("La pila ESTA VACIA.");
                else
                    puts("La pila NO esta vacia.");
                break;
            case 5:
                if (pila.estaLlena())
                    puts("La pila ESTA LLENA.");
                else
                    puts("La pila NO esta llena.");
                break;
            case 6:
                printf("Tamanio de la pila: %d\n", pila.obtenerTamano());
                break;
            case 7: puts("Adios!"); break;
            default: puts("Opcion invalida.");
        }
    } while (opcion != 7);

    return 0;
}
