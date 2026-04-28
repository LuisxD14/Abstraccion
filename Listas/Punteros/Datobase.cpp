#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int*> listaEnteros;
    int opcion = 0;

    while (opcion != 3) {
        cout << "\n--- MENU: DATO BASE (INT + PUNTEROS) ---\n";
        cout << "1. Crear y agregar numero\n";
        cout << "2. Mostrar numeros\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int* nuevo = new int;
            cout << "Ingresa el valor entero: ";
            cin >> *nuevo;
            listaEnteros.push_back(nuevo);
            cout << "Guardado en memoria dinamica.\n";
        } else if (opcion == 2) {
            for (int* n : listaEnteros) {
                cout << "Valor: " << *n << "\n";
            }
        }
    }

    for (int* n : listaEnteros) delete n;
    return 0;
}