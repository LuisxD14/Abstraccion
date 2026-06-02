#include <iostream>
#include <string>
#include <iomanip>
#include "Cola.cpp"
using namespace std;

void encabezado() {
    cout << "\n";
    cout << "=== Menu de Cola ===\n";
}

void menu() {
    cout << "1. Agregar producto\n";
    cout << "2. Quitar producto\n";
    cout << "3. Mostrar cola\n";
    cout << "4. Verificar si esta vacia\n";
    cout << "5. Verificar si esta llena\n";
    cout << "6. Mostrar tamano de la cola\n";
    cout << "7. Salir\n";
    cout << "Elige una opcion: ";
}

void pausar() {
    cout << "\n  Presiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    Cola cola;
    int opcion;

    do {
        encabezado();
        menu();
        cin >> opcion;

        switch (opcion) {

        case 1: {
            Producto p;
            cout << "\n  Nuevo producto\n";
            cout << "  Nombre : "; cin.ignore(); getline(cin, p.nombre);
            cout << "  Precio : $ "; cin >> p.precio;
            cola.encolar(p);
            cout << "\n  Producto encolado.\n";
            pausar();
            break;
        }

        case 2:
            cola.desencolar();
            pausar();
            break;

        case 3:
            cout << "\n  Cola actual\n";
            cola.mostrar();
            pausar();
            break;

        case 4:
            cout << "\n  La cola "
                 << (cola.estaVacia() ? "SI esta vacia." : "NO esta vacia.")
                 << "\n";
            pausar();
            break;

        case 5:
            cout << "\n  La cola "
                 << (cola.estaLlena() ? "SI esta llena." : "NO esta llena.")
                 << "\n";
            pausar();
            break;

        case 6:
            cout << "\n  Elementos en cola : " << cola.tamano()
                 << " / " << MAX << "\n";
            pausar();
            break;

        case 7:
            cout << "\n  Hasta luego.\n\n";
            break;

        default:
            cout << "\n  Opcion invalida.\n";
            pausar();
        }

    } while (opcion != 7);

    return 0;
}