#include <cstdio>
#include "pilaArray.h"

Pila::Pila() : cantidad(0) {}

void Pila::agregar(int valor) {
    if (cantidad < 100)
        datos[cantidad++] = valor;
}

void Pila::quitar() {
    if (cantidad > 0)
        cantidad--;
    else
        puts("La pila esta vacia.");
}

void Pila::mostrar() const {
    if (cantidad == 0) { puts("  [ pila vacia ]"); return; }
    for (int i = cantidad - 1; i >= 0; i--)
        printf("  | %d |\n", datos[i]);
}
