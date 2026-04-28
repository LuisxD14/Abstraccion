#ifndef PILA_ARRAY_INT_H
#define PILA_ARRAY_INT_H

class Pila {
    int datos[100];
    int cantidad;
public:
    Pila();
    void agregar(int valor);
    void quitar();
    void mostrar() const;
};

#endif
