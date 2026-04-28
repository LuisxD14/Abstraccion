#ifndef PILA_PUNTERO_INT_H
#define PILA_PUNTERO_INT_H

class Pila {
    int* datos;
    int  cantidad;
public:
    Pila();
    ~Pila();
    void agregar(int valor);
    void quitar();
    void mostrar() const;
};

#endif
