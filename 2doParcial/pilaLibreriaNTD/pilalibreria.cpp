#include <cstdio>
#include "pilalibreria.h"

void Pila::agregar(Persona p) { datos.push(p); }

void Pila::quitar() {
    if (!datos.empty())
        datos.pop();
    else
        puts("La pila esta vacia.");
}

void Pila::mostrar() const {
    if (datos.empty()) { puts("  [ pila vacia ]"); return; }
    std::stack<Persona> temp = datos;
    while (!temp.empty()) {
        printf("  | %s, %d anios |\n", temp.top().nombre, temp.top().edad);
        temp.pop();
    }
}

bool Pila::estaVacia() const {
    return datos.empty();
}

bool Pila::estaLlena() const {
    return false;
}

int Pila::obtenerTamano() const {
    return datos.size();
}
