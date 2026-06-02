#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
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
    queue<Producto> cola;

public:
    bool estaVacia() const override {
        return cola.empty();
    }

    bool estaLlena() const override {
        return (int)cola.size() == MAX;
    }

    int tamano() const override {
        return (int)cola.size();
    }

    Producto frente() const override {
        return cola.front();
    }

    void encolar(Producto p) override {
        if (estaLlena()) {
            cout << "\n   La cola esta llena.\n";
            return;
        }
        cola.push(p);
    }

    void desencolar() override {
        if (estaVacia()) {
            cout << "\n   La cola esta vacia.\n";
            return;
        }
        cola.pop();
    }

    void mostrar() const override {
        if (estaVacia()) {
            cout << "\n   La cola esta vacia.\n";
            return;
        }
        queue<Producto> temp = cola; 
        int pos = 1;
        while (!temp.empty()) {
            Producto p = temp.front();
            cout << "   [" << pos << "]  "
                 << p.nombre
                 << "   $" << p.precio << "\n";
            temp.pop();
            pos++;
        }
    }
};

#endif