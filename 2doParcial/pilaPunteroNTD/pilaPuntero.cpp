#include <cstdio>
#include "pilaPuntero.h"

Pila::Pila() : cantidad(0) {}
Pila::~Pila() {
    for (int i = 0; i < cantidad; i++)
        delete datos[i];
}

void Pila::agregar(Persona* p) {
    if (cantidad < 100)
        datos[cantidad++] = p;
}

void Pila::quitar() {
    if (cantidad > 0)
        delete datos[--cantidad];
    else
        puts("La pila esta vacia.");
}

void Pila::mostrar() const {
    if (cantidad == 0) { puts("  [ pila vacia ]"); return; }
    for (int i = cantidad - 1; i >= 0; i--)
        printf("  | %s, %d anios |\n", datos[i]->nombre, datos[i]->edad);
}

bool Pila::estaVacia() const {
    return cantidad == 0;
}

bool Pila::estaLlena() const {
    return cantidad == 100;
}

int Pila::obtenerTamano() const {
    return cantidad;
}
