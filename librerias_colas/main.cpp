#include <iostream>
#include <string>
#include "libcola.cpp"
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
        cout << "   1)  Encolar producto\n";
        cout << "   2)  Desencolar producto\n";
        cout << "   3)  Ver cola\n";
        cout << "   4)  Ver frente\n";
        cout << "   5)  Esta vacia?\n";
        cout << "   6)  Esta llena?\n";
        cout << "   7)  Tamano\n";
        cout << "   0)  Salir\n\n";
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
        }
        case 2:
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
            if (!cola.estaVacia()) {
                Producto f = cola.frente();
                cout << "\n   Frente: " << f.nombre << "   $" << f.precio << "\n";
            } else {
                cout << "\n   La cola esta vacia.\n";
            }
            pausar();
            break;
        case 5:
            cout << "\n   " << (cola.estaVacia() ? "Si esta vacia." : "No esta vacia.") << "\n";
            pausar();
            break;
        case 6:
            cout << "\n   " << (cola.estaLlena() ? "Si esta llena." : "No esta llena.") << "\n";
            pausar();
            break;
        case 7:
            cout << "\n   Elementos: " << cola.tamano() << " / " << MAX << "\n";
            pausar();
            break;
        case 0:
            cout << "\n   Hasta luego.\n\n";
            break;
        default:
            cout << "\n   Opcion invalida.\n";
            pausar();
        }
    } while (op != 0);

    return 0;
}