#include <iostream>
#include <string>
#include "cola.cpp" 
using namespace std;

void encabezado() {
    cout << "\n   COLA DE PRODUCTOS   (MAX: " << MAX << ")\n\n";
}

void pausar() {
    cout << "\n   Presiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    Cola cola;
    int op;

    do {
        encabezado();
        cout << "   1)  Agregar producto\n";
        cout << "   2)  Quitar producto\n";
        cout << "   3)  Ver cola\n";
        cout << "   4)  Esta vacia?\n";
        cout << "   5)  Esta llena?\n";
        cout << "   6)  Tamano\n";
        cout << "   7)  Salir\n\n";
        cout << "   Opcion: ";
        cin >> op;

        switch (op) {
        case 1: {
            Producto p;
            cout << "\n   Nombre  : "; cin.ignore(); getline(cin, p.nombre);
            cout << "   Precio  : $"; cin >> p.precio;
            cola.encolar(p);
            cout << "\n   Producto encolado.\n";
            pausar();
            break;
        } case 2:
            if (!cola.estaVacia()) {
                cout << "\n   Eliminado: " << cola.frente().nombre << "\n";
                cola.desencolar();
            } else {
                cout << "\n   La cola esta vacia.\n";
            }
            pausar();
            break;
        case 3:
            cout << "\n";
            cola.mostrar();
            pausar();
            break;
        case 4:
            cout << "\n   " << (cola.estaVacia() ? "Si esta vacia." : "No esta vacia.") << "\n";
            pausar();
            break;
        case 5:
            cout << "\n   " << (cola.estaLlena() ? "Si esta llena." : "No esta llena.") << "\n";
            pausar();
            break;
        case 6:
            cout << "\n   Elementos: " << cola.tamano() << " / " << MAX << "\n";
            pausar();
            break;
        case 7:
            cout << "\n   Hasta luego.\n\n";
            break;
        default:
            cout << "\n   Opcion invalida.\n";
            pausar();
        }
    } while (op != 7); 

    return 0;
}
