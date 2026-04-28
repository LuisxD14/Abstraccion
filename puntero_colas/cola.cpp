#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <string>
using namespace std;

const int MAX = 5;


struct Producto {
    string nombre;
    float  precio;
};


class ColaAbstracta {
public:
    virtual void encolar(Producto p)  = 0;
    virtual void desencolar()         = 0;
    virtual void mostrar()      const = 0;
    virtual bool estaVacia()    const = 0;
    virtual bool estaLlena()    const = 0;
    virtual int  tamano()       const = 0;
    virtual Producto frente()   const = 0;
    virtual ~ColaAbstracta() {}
};


class Cola : public ColaAbstracta {
private:
    Producto* arreglo;  
    int inicio;
    int fin;
    int cantidad;

public:

    Cola() : inicio(0), fin(0), cantidad(0) {
        arreglo = new Producto[MAX];
    }

    ~Cola() {
        delete[] arreglo;
    }

    bool estaVacia() const override {
        return cantidad == 0;
    }

    bool estaLlena() const override {
        return cantidad == MAX;
    }

    int tamano() const override {
        return cantidad;
    }

    Producto frente() const override {
        return arreglo[inicio];
    }

    void encolar(Producto p) override {
        if (estaLlena()) {
            cout << "\n   La cola esta llena.\n";
            return;
        }
        arreglo[fin] = p;
        fin = (fin + 1) % MAX;
        cantidad++;
    }

    void desencolar() override {
        if (estaVacia()) {
            cout << "\n   La cola esta vacia.\n";
            return;
        }
        inicio = (inicio + 1) % MAX;
        cantidad--;
    }

    void mostrar() const override {
        if (estaVacia()) {
            cout << "\n   La cola esta vacia.\n";
            return;
        }
        for (int i = 0; i < cantidad; i++) {
            int idx = (inicio + i) % MAX;
            cout << "   [" << i + 1 << "]  "
                 << arreglo[idx].nombre
                 << "   $" << arreglo[idx].precio << "\n";
        }
    }
};

#endif