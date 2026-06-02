#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>

using namespace std;

const int MAX = 10;

void agregarElemento(int lista[], int &n) {
    if (n < MAX) {
        int dato;
        cout << "Ingresa un numero entero: ";
        cin >> dato;
        lista[n] = dato;
        n++;
        cout << "Elemento agregado.\n";
    } else {
        cout << "Error: La lista esta llena.\n";
    }
}

void quitarElemento(int lista[], int &n) {
    if (n > 0) {
        cout << "Elemento " << lista[n - 1] << " eliminado.\n";
        n--;
    } else {
        cout << "La lista esta vacia.\n";
    }
}

void mostrarLista(int lista[], int n) {
    if (n == 0) {
        cout << "La lista esta vacia.\n";
        return;
    }
    cout << "\nContenido de la lista:\n";
    for (int i = 0; i < n; i++) {
        cout << "[" << i << "]: " << lista[i] << "\n";
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