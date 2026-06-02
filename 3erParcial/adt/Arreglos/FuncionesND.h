#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>

using namespace std;

struct Producto {
    int codigo;
};

const int MAX = 10;

void agregarElemento(Producto lista[], int &n) {
    if (n < MAX) {
        int val;
        cout << "Ingresa el codigo del producto: ";
        cin >> val;
        lista[n].codigo = val;
        n++;
        cout << "Elemento agregado.\n";
    } else {
        cout << "Error: La lista esta llena.\n";
    }
}

void quitarElemento(Producto lista[], int &n) {
    if (n > 0) {
        cout << "Elemento con codigo " << lista[n - 1].codigo << " eliminado.\n";
        n--;
    } else {
        cout << "La lista esta vacia.\n";
    }
}

void mostrarLista(Producto lista[], int n) {
    if (n == 0) {
        cout << "La lista esta vacia.\n";
        return;
    }
    cout << "\nContenido de la lista:\n";
    for (int i = 0; i < n; i++) {
        cout << "[" << i << "]: Codigo " << lista[i].codigo << "\n";
    }
}

void verificarVacia(int n) {
    if (n == 0) {
        cout << "La lista esta vacia.\n";
    } else {
        cout << "La lista no esta vacia.\n";
    }
}

void verificarLlena(int n) {
    if (n == MAX) {
        cout << "La lista esta llena.\n";
    } else {
        cout << "La lista aun tiene espacio.\n";
    }
}

void mostrarTamano(int n) {
    cout << "Tama\244o actual: " << n << "\n";
}

#endif