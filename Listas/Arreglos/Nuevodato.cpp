#include <iostream>
#include <string>
#include <list>

using namespace std;

struct RegistroNivel {
    string nombreNivel;
    int puntajes[3];
    int puntajeTotal;
};

int main() {
    list<RegistroNivel> historial;
    int opcion = 0;

    while (opcion != 3) {
        cout << "\n=== MENU DE NIVELES ===\n";
        cout << "1. Registrar nuevo nivel y puntajes\n";
        cout << "2. Mostrar historial\n";
        cout << "3. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            RegistroNivel nuevoRegistro;
            cout << "Nombre del nivel: ";
            cin.ignore();
            getline(cin, nuevoRegistro.nombreNivel);

            nuevoRegistro.puntajeTotal = 0;
            
            for (int i = 0; i < 3; i++) {
                cout << "Ingresa el puntaje del intento " << (i + 1) << ": ";
                cin >> nuevoRegistro.puntajes[i];
                nuevoRegistro.puntajeTotal += nuevoRegistro.puntajes[i];
            }

            historial.push_back(nuevoRegistro);
            cout << "Nivel registrado con exito.\n";
        } else if (opcion == 2) {
            if (historial.empty()) {
                cout << "El historial esta vacio.\n";
            } else {
                for (RegistroNivel r : historial) {
                    cout << "\nNivel: " << r.nombreNivel << "\n";
                    cout << "Puntajes en los 3 intentos: ";
                    
                    for (int i = 0; i < 3; i++) {
                        cout << r.puntajes[i] << " ";
                    }
                    
                    cout << "\nPuntaje total: " << r.puntajeTotal << "\n";
                }
            }
        }
    }

    return 0;
}