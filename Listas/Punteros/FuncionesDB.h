#include <iostream>
#include <list>

using namespace std;

void mostrarMenu() {
    cout << "\n--- MENU: DATO BASE (INT + PUNTEROS) ---\n";
    cout << "1. Crear y agregar numero\n";
    cout << "2. Mostrar numeros\n";
    cout << "3. Salir\n";
    cout << "Opcion: ";
}

void agregarNumeroPuntero(list<int*> &miLista) {
    int* nuevo = new int;
    cout << "Ingresa el valor entero: ";
    cin >> *nuevo;
    miLista.push_back(nuevo);
    cout << "Guardado en memoria dinamica.\n";
}

void mostrarListaPunteros(const list<int*> &miLista) {
    if (miLista.empty()) {
        cout << "La lista esta vacia.\n";
    } else {
        for (int* n : miLista) {
            cout << "Valor: " << *n << " (Direccion: " << n << ")\n";
        }
    }
}

void limpiarMemoria(list<int*> &miLista) {
    for (int* n : miLista) {
        delete n;
    }
    miLista.clear();
}