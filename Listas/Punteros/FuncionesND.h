#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>

using namespace std;

struct Vehiculo {
    int id;
};

struct Nodo {
    Vehiculo dato;
    Nodo* siguiente;
};

void agregarElemento(Nodo*& cabeza) {
    int valor;
    cout << "Ingresa el ID del vehiculo: ";
    cin >> valor;

    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato.id = valor;
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
        cout << "Vehiculo con ID " << cabeza->dato.id << " eliminado.\n";
        delete cabeza;
        cabeza = nullptr;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        cout << "Vehiculo con ID " << temp->siguiente->dato.id << " eliminado.\n";
        delete temp->siguiente;
        temp->siguiente = nullptr;
    }
}

void mostrarLista(Nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }
    cout << "\nContenido de la lista (Vehiculos):\n";
    Nodo* temp = cabeza;
    int i = 0;
    while (temp != nullptr) {
        cout << "[" << i << "]: ID " << temp->dato.id << "\n";
        temp = temp->siguiente;
        i++;
    }
}

void verificarVacia(Nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
    } else {
        cout << "La lista contiene elementos.\n";
    }
}

void verificarLlena() {
    cout << "La lista usa memoria dinamica, no tiene un limite de llenado.\n";
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