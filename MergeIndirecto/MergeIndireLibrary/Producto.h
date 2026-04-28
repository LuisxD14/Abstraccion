#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>

class Producto {
private:
    std::string nombre;
    float precio;

public:
    Producto(std::string n = "", float p = 0.0) {
        nombre = n;
        precio = p;
    }

    float getPrecio() { return precio; }

    void mostrar() {
        std::cout << "- " << nombre << " : $" << precio << std::endl;
    }
};

#endif