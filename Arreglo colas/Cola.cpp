#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <string>
using namespace std;


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

const int MAX = 5;

class Cola : public ColaAbstracta {
private:
    Producto arreglo[MAX];
    int inicio;
    int fin;
    int cantidad;

public:
    Cola() : inicio(0), fin(0), cantidad(0) {}

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
            cout << "\n  [!] La cola esta llena. No se puede encolar.\n";
            return;
        }
        arreglo[fin] = p;
        fin = (fin + 1) % MAX; 
        cantidad++;
    }

    void desencolar() override {
        if (estaVacia()) {
            cout << "\n  [!] La cola esta vacia. No hay nada que desencolar.\n";
            return;
        }
        cout << "\n  >> Producto eliminado: " << arreglo[inicio].nombre << "\n";
        inicio = (inicio + 1) % MAX;
        cantidad--;
    }

    void mostrar() const override {
        if (estaVacia()) {
            cout << "\n  La cola esta vacia.\n";
            return;
        }
        cout << "\n  Pos  Nombre                  Precio\n";
        cout << "  ---  ----------------------  --------\n";
        for (int i = 0; i < cantidad; i++) {
            int idx = (inicio + i) % MAX;
            cout << "  [" << i + 1 << "]  "
                 << arreglo[idx].nombre;
        
            int pad = 22 - (int)arreglo[idx].nombre.size();
            for (int s = 0; s < pad; s++) cout << ' ';
            cout << "$ " << arreglo[idx].precio << "\n";
        }
    }
};

#endif