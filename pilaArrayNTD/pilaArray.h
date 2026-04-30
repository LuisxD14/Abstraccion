#ifndef PILA_ARRAY_STRUCT_H
#define PILA_ARRAY_STRUCT_H

struct Persona {
    char nombre[50];
    int  edad;
};

class Pila {
    Persona datos[100];
    int cantidad;
public:
    Pila();
    void agregar(Persona p);
    void quitar();
    void mostrar() const;
    bool estaVacia() const;
    bool estaLlena() const;
    int obtenerTamano() const;
};

#endif
