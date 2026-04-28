#include "FuncionesND.h"

int main() {
    list<RegistroNivel> historial;
    int opcion = 0;

    while (opcion != 3) {
        menuPrincipal();
        cin >> opcion;

        if (opcion == 1) {
            agregarRegistro(historial);
        } else if (opcion == 2) {
            mostrarHistorial(historial);
        }
    }

    return 0;
}