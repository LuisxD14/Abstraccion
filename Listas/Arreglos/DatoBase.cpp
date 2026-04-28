#include "FuncionesDB.h"

int main() {
    list<int> listaNumeros;
    int valoresFijos[5] = {10, 20, 30, 40, 50};
    int opcion = 0;

    while (opcion != 4) {
        cout << "\n--- INTERFAZ DE DATOS BASE ---\n";
        cout << "1. Ver valores base del arreglo\n";
        cout << "2. Agregar numero a la lista\n";
        cout << "3. Ver todos los numeros en la lista\n";
        cout << "4. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            mostrarArregloBase(valoresFijos, 5);
        } 
        else if (opcion == 2) {
            agregarDatoALista(listaNumeros);
        } 
        else if (opcion == 3) {
            mostrarContenidoLista(listaNumeros);
        }
    }

    return 0;
}