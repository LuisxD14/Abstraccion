#ifndef PILA_LIBRERIA_STRUCT_H
#define PILA_LIBRERIA_STRUCT_H

#include <stack>

struct Persona {
    char nombre[50];
    int  edad;
};

class Pila {
    std::stack<Persona> datos;
public:
    void agregar(Persona p);
    void quitar();
    void mostrar() const;
    bool estaVacia() const;
    bool estaLlena() const;
    int obtenerTamano() const;
};

#endif
