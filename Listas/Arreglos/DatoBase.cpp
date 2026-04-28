#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() {
    list<int> listaNumeros;
    int valoresFijos[5] = {10, 20, 30, 40, 50};
    int opcion = 0;
    int datoUsuario;

    while (opcion != 4) {
        cout << "\n--- INTERFAZ DE DATOS BASE ---\n";
        cout << "1. Ver valores base del arreglo\n";
        cout << "2. Agregar numero a la lista\n";
        cout << "3. Ver todos los numeros en la lista\n";
        cout << "4. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "\nContenido del arreglo (datos base int):\n";
            for (int i = 0; i < 5; i++) {
                cout << "[" << i << "]: " << valoresFijos[i] << "\n";
            }
        } 
        else if (opcion == 2) {
            cout << "Ingresa un numero entero para la lista: ";
            cin >> datoUsuario;
            listaNumeros.push_back(datoUsuario);
            cout << "Dato guardado.\n";
        } 
        else if (opcion == 3) {
            cout << "\nElementos actuales en la lista:\n";
            if (listaNumeros.empty()) {
                cout << "La lista no tiene elementos.\n";
            } else {
                for (int n : listaNumeros) {
                    cout << "Valor: " << n << "\n";
                }
            }
        }
    }

    return 0;
}