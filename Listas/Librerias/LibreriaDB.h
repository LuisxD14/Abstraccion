#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <list>

using namespace std;

void agregarElemento(list<int> &miLista) {
    int valor;
    cout << "Ingresa un numero entero: ";
    cin >> valor;
    miLista.push_back(valor);
    cout << "Elemento agregado.\n";
}

void quitarElemento(list<int> &miLista) {
    if (!miLista.empty()) {
        cout << "Elemento " << miLista.back() << " eliminado.\n";
        miLista.pop_back();
    } else {
        cout << "La lista esta vacia.\n";
    }
}

void mostrarLista(const list<int> &miLista) {
    if (miLista.empty()) {
        cout << "La lista esta vacia.\n";
        return;
    }
    cout << "\nContenido de la lista:\n";
    int i = 0;
    for (int n : miLista) {
        cout << "[" << i << "]: " << n << "\n";
        i++;
    }
}

void verificarVacia(const list<int> &miLista) {
    if (miLista.empty()) {
        cout << "La lista esta vacia.\n";
    } else {
        cout << "La lista no esta vacia.\n";
    }
}

void verificarLlena() {
    cout << "La libreria list usa memoria dinamica, no tiene limite fijo.\n";
}

void mostrarTamano(const list<int> &miLista) {
    cout << "Tama\244o actual: " << miLista.size() << "\n";
}

#endif