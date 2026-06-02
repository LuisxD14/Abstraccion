#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int MAX = 5;

struct Producto {
    string nombre;
    float  precio;
};

struct Orden {
    int    id;
    string descripcion;
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


class ColaProducto : public ColaAbstracta {
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


class ColaOrdenAbstracta {
public:
    virtual void encolar(Orden o)   = 0;
    virtual void desencolar()       = 0;
    virtual void mostrar()    const = 0;
    virtual bool estaVacia()  const = 0;
    virtual bool estaLlena()  const = 0;
    virtual int  tamano()     const = 0;
    virtual Orden frente()    const = 0;
    virtual ~ColaOrdenAbstracta() {}
};


class ColaOrden : public ColaOrdenAbstracta {
private:
    queue<Orden> cola;

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

    Orden frente() const override {
        return cola.front();
    }

    void encolar(Orden o) override {
        if (estaLlena()) {
            cout << "\n   La cola esta llena.\n";
            return;
        }
        cola.push(o);
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
        queue<Orden> temp = cola;
        int pos = 1;
        while (!temp.empty()) {
            Orden o = temp.front();
            cout << "   [" << pos << "]  "
                 << "Orden #" << o.id
                 << "   " << o.descripcion << "\n";
            temp.pop();
            pos++;
        }
    }
};

#endif