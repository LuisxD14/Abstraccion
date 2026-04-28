#include <iostream>
#include "Ordenador.cpp"
using namespace std;

void encabezado() {
    cout << "\n   ORDENAMIENTO BURBUJA\n\n";
}

void pausar() {
    cout << "\n   Presiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void ejecutar(Ordenador* o) {
    o->cargar();
    o->ordenar();
    o->mostrar();
    pausar();
}

int main() {
    int op;

    do {
        encabezado();
        cout << "   1)  Ordenar enteros\n";
        cout << "   2)  Ordenar caracteres\n";
        cout << "   3)  Ordenar estudiantes\n";
        cout << "   0)  Salir\n\n";
        cout << "   Opcion: ";
        cin >> op;

        switch (op) {
        case 1: {
            OrdenadorInt o;
            ejecutar(&o);
            break;
        }
        case 2: {
            OrdenadorChar o;
            ejecutar(&o);
            break;
        }
        case 3: {
            OrdenadorEstudiante o;
            ejecutar(&o);
            break;
        }
        case 0:
            cout << "\n   Hasta luego.\n\n";
            break;
        default:
            cout << "\n   Opcion invalida.\n";
        }
    } while (op != 0);

    return 0;
}