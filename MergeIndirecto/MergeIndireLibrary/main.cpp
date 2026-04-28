#include <iostream>
#include "Inventario.h"

using namespace std;

int main() {
    int n;
    cout << "Cuantos productos registrara? ";
    cin >> n;

    Inventario miTienda(n);

    for (int i = 0; i < n; i++) {
        string nombre;
        float precio;
        cout << "\nProducto " << i + 1 << endl;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Precio: ";
        cin >> precio;
        miTienda.agregarProducto(nombre, precio);
    }

    miTienda.ordenarPorPrecio();

    cout << "\n--- INVENTARIO ORDENADO (LIBRERIAS + INDIRECTO) ---" << endl;
    miTienda.mostrarInventarioOrdenado();

    return 0;
}