#include <iostream>
#include <list>
#include "LibreriaND.h"

using namespace std;

int main() {
    list<Estudiante> miLista;
    int opcion;

    do {
        cout << "\n=== Men\241 de Lista ===\n";
        cout << "1. Agregar elemento\n";
        cout << "2. Quitar elemento\n";
        cout << "3. Mostrar lista\n";
        cout << "4. Verificar si esta vacia\n";
        cout << "5. Verificar si esta llena\n";
        cout << "6. Mostrar tama\244o de la lista\n";
        cout << "7. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarElemento(miLista);
                break;
            case 2:
                quitarElemento(miLista);
                break;
            case 3:
                mostrarLista(miLista);
                break;
            case 4:
                verificarVacia(miLista);
                break;
            case 5:
                verificarLlena();
                break;
            case 6:
                mostrarTamano(miLista);
                break;
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 7);

    return 0;
}