#include <cstdio>
#include "pilaArray.h"

int main() {
    Pila pila;
    int opcion;

    do {
        puts("\n1. Ver pila");
        puts("2. Agregar persona");
        puts("3. Quitar");
        puts("4. Salir");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: pila.mostrar(); break;
            case 2: {
                Persona p;
                printf("Nombre: ");
                scanf("%s", p.nombre);
                printf("Edad: ");
                scanf("%d", &p.edad);
                pila.agregar(p);
                break;
            }
            case 3: pila.quitar(); break;
            case 4: puts("Adios!"); break;
            default: puts("Opcion invalida.");
        }
    } while (opcion != 4);

    return 0;
}
