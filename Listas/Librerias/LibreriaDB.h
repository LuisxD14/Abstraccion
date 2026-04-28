#include <iostream>
#include <list>

using namespace std;

typedef float DatoBase;

void menuBase() {
    cout << "\n--- INTERFAZ: DATO BASE ---\n";
    cout << "1. Insertar valor\n";
    cout << "2. Listar valores\n";
    cout << "3. Salir\n";
    cout << "Seleccion: ";
}

void ejecutarProgramaBase() {
    list<DatoBase> miLista;
    int op = 0;
    while (op != 3) {
        menuBase();
        cin >> op;
        if (op == 1) {
            DatoBase nuevo;
            cout << "Ingresa valor decimal: ";
            cin >> nuevo;
            miLista.push_back(nuevo);
        } else if (op == 2) {
            for (const auto& i : miLista) {
                cout << "Valor: " << i << endl;
            }
        }
    }
}