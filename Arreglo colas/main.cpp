#include <iostream>
#include <string>
#include <iomanip>
#include "Cola.cpp"
using namespace std;


void encabezado() {
    cout << "\n";
    cout << "  SISTEMA DE COLA DE PRODUCTOS   (MAX:" << MAX << ")  \n";
}

void menu() {
    cout << "   1)  Encolar producto\n";
    cout << "   2)  Desencolar producto\n";
    cout << "   3)  Ver cola completa\n";
    cout << "   4)  Ver producto en frente\n";
    cout << "   5)  Verificar si esta vacia\n";
    cout << "   6)  Verificar si esta llena\n";
    cout << "   7)  Capacidad usada\n";
    cout << "   0)  Salir\n";
    cout << "  >> Opcion: ";
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
            cout << "\n  Nuevo producto \n";
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
            cout << "\n Cola actual \n";
            cola.mostrar();
            pausar();
            break;

        case 4:     
            if (!cola.estaVacia()) {
                Producto f = cola.frente();
                cout << "\n  Frente -> " << f.nombre
                     << "  |  $ " << f.precio << "\n";
            } else {
                cout << "\n  La cola esta vacia.\n";
            }
            pausar();
            break;

        case 5:     
            cout << "\n  La cola " 
                 << (cola.estaVacia() ? "SI esta vacia." : "NO esta vacia.")
                 << "\n";
            pausar();
            break;

        case 6:     
            cout << "\n  La cola "
                 << (cola.estaLlena() ? "SI esta llena." : "NO esta llena.")
                 << "\n";
            pausar();
            break;

        case 7:     
            cout << "\n  Elementos en cola : " << cola.tamano()
                 << " / " << MAX << "\n";
            pausar();
            break;

        case 0:
            cout << "\n  Hasta luego.\n\n";
            break;

        default:
            cout << "\n  Opcion invalida.\n";
            pausar();
        }

    } while (opcion != 0);

    return 0;
}