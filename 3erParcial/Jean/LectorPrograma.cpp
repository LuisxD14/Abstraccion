
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string nombrePrograma(int op) {
    if (op == 1) return "fibonacci";
    if (op == 2) return "matrices";
    if (op == 3) return "sierpinski";
    if (op == 4) return "polvo_de_cantor";
    return "";
}

string extensionArchivo(int op) {
    if (op == 1) return "txt";
    if (op == 2) return "json";
    if (op == 3) return "xml";
    if (op == 4) return "csv";
    return "";
}

void leerArchivo(const string& nombre) {
    ifstream archivo(nombre);
    if (!archivo) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        cout << linea << '\n';
    }
}

int main() {
    int opcionPrograma, opcionFormato;

    do {
        cout << "\nMenu principal\n";
        cout << "1 Fibonacci\n";
        cout << "2 Matrices\n";
        cout << "3 Triangulo de Sierpinski\n";
        cout << "4 Polvo de Cantor\n";
        cout << "5 Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcionPrograma;

        if (opcionPrograma == 5) {
            break;
        }

        cout << "\nMenu de formato\n";
        cout << "1 txt\n";
        cout << "2 json\n";
        cout << "3 xml\n";
        cout << "4 csv\n";
        cout << "Elige un formato: ";
        cin >> opcionFormato;

        string base = nombrePrograma(opcionPrograma);
        string ext = extensionArchivo(opcionFormato);

        if (base.empty() || ext.empty()) {
            cout << "Opcion no valida\n";
            continue;
        }

        string archivo = base + "." + ext;
        cout << "\nContenido de " << archivo << "\n";
        leerArchivo(archivo);

    } while (true);

    return 0;
}
