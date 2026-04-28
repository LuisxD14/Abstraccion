#include <cstdio>
#include "pilaLibreria.h"

void Pila::agregar(int valor) { datos.push(valor); }

void Pila::quitar() {
    if (!datos.empty())
        datos.pop();
    else
        puts("La pila esta vacia.");
}

void Pila::mostrar() const {
    if (datos.empty()) { puts("  [ pila vacia ]"); return; }
    std::stack<int> temp = datos;
    while (!temp.empty()) {
        printf("  | %d |\n", temp.top());
        temp.pop();
    }
}
