#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Producto.h"

class Inventario {
private:
    Producto* listaProductos;
    int capacidadMax;
    int cantidadActual;

    void merge(int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        Producto* L = new Producto[n1];
        Producto* R = new Producto[n2];

        for (int i = 0; i < n1; i++) L[i] = listaProductos[inicio + i];
        for (int j = 0; j < n2; j++) R[j] = listaProductos[medio + 1 + j];

        int i = 0, j = 0, k = inicio;

        while (i < n1 && j < n2) {
            if (L[i].getPrecio() <= R[j].getPrecio()) {
                listaProductos[k] = L[i];
                i++;
            } else {
                listaProductos[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            listaProductos[k] = L[i];
            i++; k++;
        }

        while (j < n2) {
            listaProductos[k] = R[j];
            j++; k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSortRecursivo(int inicio, int fin) {
        if (inicio >= fin) return;
        int medio = inicio + (fin - inicio) / 2;
        mergeSortRecursivo(inicio, medio);
        mergeSortRecursivo(medio + 1, fin);
        merge(inicio, medio, fin);
    }

public:
    Inventario(int capacidad) {
        capacidadMax = capacidad;
        cantidadActual = 0;
        listaProductos = new Producto[capacidadMax];
    }

    ~Inventario() {
        delete[] listaProductos;
    }

    void agregarProducto(std::string nombre, float precio) {
        if (cantidadActual < capacidadMax) {
            listaProductos[cantidadActual] = Producto(nombre, precio);
            cantidadActual++;
        }
    }

    void mostrarInventario() {
        for (int i = 0; i < cantidadActual; i++) {
            listaProductos[i].mostrar();
        }
    }

    void ordenarPorPrecio() {
        if (cantidadActual > 1) {
            mergeSortRecursivo(0, cantidadActual - 1);
        }
    }
};

#endif