#ifndef PILA_PUNTERO_STRUCT_H
#define PILA_PUNTERO_STRUCT_H

struct Persona {
    char nombre[50];
    int  edad;
};

class Pila {
    Persona* datos[100];
    int cantidad;
public:
    Pila();
    ~Pila();
    void agregar(Persona* p);
    void quitar();
    void mostrar() const;
};

#endif
