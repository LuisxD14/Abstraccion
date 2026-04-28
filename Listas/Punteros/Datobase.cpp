#include "FuncionesDB.h"

int main() {
    list<int*> listaEnteros;
    int opcion = 0;

    while (opcion != 3) {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            agregarNumeroPuntero(listaEnteros);
        } else if (opcion == 2) {
            mostrarListaPunteros(listaEnteros);
        }
    }

    limpiarMemoria(listaEnteros);
    return 0;
}