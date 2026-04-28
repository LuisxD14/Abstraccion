#include <cstdio>
#include "pilaPuntero.h"

Pila::Pila() : cantidad(0) { datos = new int[100]; }
Pila::~Pila() { delete[] datos; }

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
