#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Item {
    string etiqueta;
    int id;
};

void menuComplejo() {
    cout << "\n--- INTERFAZ: NUEVO TIPO DE DATO ---\n";
    cout << "1. Insertar item\n";
    cout << "2. Listar items\n";
    cout << "3. Salir\n";
    cout << "Seleccion: ";
}

void ejecutarProgramaComplejo() {
    list<Item> miLista;
    int op = 0;
    while (op != 3) {
        menuComplejo();
        cin >> op;
        if (op == 1) {
            Item nuevo;
            cout << "Etiqueta: ";
            cin.ignore();
            getline(cin, nuevo.etiqueta);
            cout << "ID: ";
            cin >> nuevo.id;
            miLista.push_back(nuevo);
        } else if (op == 2) {
            for (const auto& i : miLista) {
                cout << "[" << i.id << "] " << i.etiqueta << endl;
            }
        }
    }
}