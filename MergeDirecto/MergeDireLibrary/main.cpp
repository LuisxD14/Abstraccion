#include <iostream>
#include "Inventario.h"

using namespace std;

int main() {
    int n;
    cout << "Cuantos productos desea registrar? ";
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

    cout << "\n--- LISTA SIN ORDENAR ---" << endl;
    miTienda.mostrarInventario();

    miTienda.ordenarPorPrecio();

    cout << "\n--- LISTA ORDENADA POR PRECIO ---" << endl;
    miTienda.mostrarInventario();

    return 0;
}