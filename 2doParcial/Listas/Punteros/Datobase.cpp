#include <iostream>
#include "FuncionesDB.h"

using namespace std;

int main() {
    Nodo* cabeza = nullptr;
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
                agregarElemento(cabeza);
                break;
            case 2:
                quitarElemento(cabeza);
                break;
            case 3:
                mostrarLista(cabeza);
                break;
            case 4:
                verificarVacia(cabeza);
                break;
            case 5:
                verificarLlena();
                break;
            case 6:
                mostrarTamano(cabeza);
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