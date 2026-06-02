#include <iostream>
#include <string>
#include "cola.cpp"
using namespace std;

void encabezado(const string& tipo) {
    cout << "\n   COLA DE " << tipo << "   (MAX: " << MAX << ")\n\n";
}

void pausar() {
    cout << "\n   Presiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void manejarProductos() {
    ColaProducto cola;
    int op;

    do {
        encabezado("PRODUCTOS");
        cout << "   1)  Agregar producto\n";
        cout << "   2)  Quitar producto\n";
        cout << "   3)  Ver cola\n";
        cout << "   4)  Esta vacia?\n";
        cout << "   5)  Esta llena?\n";
        cout << "   6)  Tamano\n";
        cout << "   7)  Volver\n\n";
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
        case 7: break;
        default:
            cout << "\n   Opcion invalida.\n";
            pausar();
        }
    } while (op != 7);
}

void manejarOrdenes() {
    ColaOrden cola;
    int op;

    do {
        encabezado("ORDENES");
        cout << "   1)  Agrar orden\n";
        cout << "   2)  Quitar orden\n";
        cout << "   3)  Ver cola\n";
        cout << "   4)  Esta vacia?\n";
        cout << "   5)  Esta llena?\n";
        cout << "   6)  Tamano\n";
        cout << "   7)  Volver\n\n";
        cout << "   Opcion: ";
        cin >> op;

        switch (op) {
        case 1: {
            Orden o;
            cout << "\n   ID orden     : "; cin >> o.id;
            cout << "   Descripcion  : "; cin.ignore(); getline(cin, o.descripcion);
            cola.encolar(o);
            cout << "\n   Orden encolada.\n";
            pausar();
            break;
        }
        case 2:
            if (!cola.estaVacia()) {
                cout << "\n   Eliminada: Orden #" << cola.frente().id << "\n";
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
        case 7: break;
        default:
            cout << "\n   Opcion invalida.\n";
            pausar();
        }
    } while (op != 7);
}
int main() {
    int op;

    do {
        cout << "\n   MENU PRINCIPAL\n\n";
        cout << "   1)  Cola de Productos\n";
        cout << "   2)  Cola de Ordenes\n";
        cout << "   0)  Salir\n\n";
        cout << "   Opcion: ";
        cin >> op;

        switch (op) {
        case 1: manejarProductos(); break;
        case 2: manejarOrdenes();   break;
        case 0: cout << "\n   Hasta luego.\n\n"; break;
        default: cout << "\n   Opcion invalida.\n";
        }
    } while (op != 0);

    return 0;
}
