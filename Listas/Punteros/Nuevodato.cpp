#include "FuncionesND.h"

int main() {
    list<Personaje*> listaPersonajes;
    int opcion = 0;

    while (opcion != 3) {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            agregarPersonaje(listaPersonajes);
        } else if (opcion == 2) {
            mostrarPersonajes(listaPersonajes);
        }
    }

    liberarMemoriaPersonajes(listaPersonajes);
    return 0;
}