#include <iostream>
#include <list>

using namespace std;

void mostrarArregloBase(int arreglo[], int tamano) {
    cout << "\nContenido del arreglo (datos base int):\n";
    for (int i = 0; i < tamano; i++) {
        cout << "[" << i << "]: " << arreglo[i] << "\n";
    }
}

void agregarDatoALista(list<int> &miLista) {
    int dato;
    cout << "Ingresa un numero entero para la lista: ";
    cin >> dato;
    miLista.push_back(dato);
    cout << "Dato guardado.\n";
}

void mostrarContenidoLista(const list<int> &miLista) {
    cout << "\nElementos actuales en la lista:\n";
    if (miLista.empty()) {
        cout << "La lista no tiene elementos.\n";
    } else {
        for (int n : miLista) {
            cout << "Valor: " << n << "\n";
        }
    }
}