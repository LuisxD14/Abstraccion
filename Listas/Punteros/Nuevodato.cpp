#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Personaje {
    string nombre;
    int nivel;
};

int main() {
    list<Personaje*> listaPersonajes;
    int opcion = 0;

    while (opcion != 3) {
        cout << "\n--- MENU: NUEVO TIPO DE DATO (STRUCT + PUNTEROS) ---\n";
        cout << "1. Crear y agregar personaje\n";
        cout << "2. Mostrar personajes\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Personaje* nuevo = new Personaje;
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nuevo->nombre);
            cout << "Nivel: ";
            cin >> nuevo->nivel;
            listaPersonajes.push_back(nuevo);
            cout << "Guardado en memoria dinamica.\n";
        } else if (opcion == 2) {
            for (Personaje* p : listaPersonajes) {
                cout << "Personaje: " << p->nombre << " | Nivel: " << p->nivel << "\n";
            }
        }
    }

    for (Personaje* p : listaPersonajes) delete p;
    return 0;
}