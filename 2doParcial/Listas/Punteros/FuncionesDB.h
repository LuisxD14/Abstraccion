#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

void agregarElemento(Nodo*& cabeza) {
    int valor;
    cout << "Ingresa un numero entero: ";
    cin >> valor;

    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = nullptr;

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
    cout << "Elemento agregado.\n";
}

void quitarElemento(Nodo*& cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    if (cabeza->siguiente == nullptr) {
        cout << "Elemento " << cabeza->dato << " eliminado.\n";
        delete cabeza;
        cabeza = nullptr;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        cout << "Elemento " << temp->siguiente->dato << " eliminado.\n";
        delete temp->siguiente;
        temp->siguiente = nullptr;
    }
}

void mostrarLista(Nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }
    cout << "\nContenido de la lista:\n";
    Nodo* temp = cabeza;
    int i = 0;
    while (temp != nullptr) {
        cout << "[" << i << "]: " << temp->dato << "\n";
        temp = temp->siguiente;
        i++;
    }
}

void verificarVacia(Nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
    } else {
        cout << "La lista no esta vacia.\n";
    }
}

void verificarLlena() {
    cout << "Al usar punteros, la lista es dinamica y no se llena.\n";
}

void mostrarTamano(Nodo* cabeza) {
    int contador = 0;
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        contador++;
        temp = temp->siguiente;
    }
    cout << "Tama\244o actual: " << contador << "\n";
}

#endif