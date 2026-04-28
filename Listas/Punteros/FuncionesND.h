#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Personaje {
    string nombre;
    int nivel;
};

void mostrarMenu() {
    cout << "\n--- MENU: NUEVO TIPO DE DATO (STRUCT + PUNTEROS) ---\n";
    cout << "1. Crear y agregar personaje\n";
    cout << "2. Mostrar personajes\n";
    cout << "3. Salir\n";
    cout << "Opcion: ";
}

void agregarPersonaje(list<Personaje*> &lista) {
    Personaje* nuevo = new Personaje;
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevo->nombre);
    cout << "Nivel: ";
    cin >> nuevo->nivel;
    lista.push_back(nuevo);
    cout << "Guardado en memoria dinamica.\n";
}

void mostrarPersonajes(const list<Personaje*> &lista) {
    if (lista.empty()) {
        cout << "La lista de personajes esta vacia.\n";
    } else {
        for (Personaje* p : lista) {
            cout << "Personaje: " << p->nombre << " | Nivel: " << p->nivel << " (Dir: " << p << ")\n";
        }
    }
}

void liberarMemoriaPersonajes(list<Personaje*> &lista) {
    for (Personaje* p : lista) {
        delete p;
    }
    lista.clear();
    cout << "Memoria liberada correctamente.\n";
}