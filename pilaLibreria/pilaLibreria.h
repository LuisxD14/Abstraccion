#ifndef PILA_LIBRERIA_INT_H
#define PILA_LIBRERIA_INT_H

#include <stack>

class Pila {
    std::stack<int> datos;
public:
    void agregar(int valor);
    void quitar();
    void mostrar() const;
    bool estaVacia() const;
    bool estaLlena() const;
    int obtenerTamano() const;
};

#endif
