#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

struct Estudiante {
    int boleta;
};

void agregarElemento(list<Estudiante> &miLista) {
    Estudiante e;
    cout << "Ingresa el numero de boleta: ";
    cin >> e.boleta;
    miLista.push_back(e);
    cout << "Elemento agregado.\n";
}

void quitarElemento(list<Estudiante> &miLista) {
    if (!miLista.empty()) {
        cout << "Estudiante con boleta " << miLista.back().boleta << " eliminado.\n";
        miLista.pop_back();
    } else {
        cout << "La lista esta vacia.\n";
    }
}

void mostrarLista(const list<Estudiante> &miLista) {
    if (miLista.empty()) {
        cout << "La lista esta vacia.\n";
        return;
    }
    cout << "\nContenido de la lista (Estudiantes):\n";
    int i = 0;
    for (const auto &e : miLista) {
        cout << "[" << i << "]: Boleta " << e.boleta << "\n";
        i++;
    }
}

void verificarVacia(const list<Estudiante> &miLista) {
    if (miLista.empty()) {
        cout << "La lista esta vacia.\n";
    } else {
        cout << "La lista no esta vacia.\n";
    }
}

void verificarLlena() {
    cout << "La libreria list es dinamica, no tiene limite de capacidad.\n";
}

void mostrarTamano(const list<Estudiante> &miLista) {
    cout << "Tama\244o actual: " << miLista.size() << "\n";
}

#endif