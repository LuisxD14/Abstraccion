#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

class ConexionNodo2Nodo {
private:
    string nodoInicial;
    string nodoFinal;
    string aristaConexion;
    double tiempo;
    double costo;

public:
    ConexionNodo2Nodo() : tiempo(0.0), costo(0.0) {}

    ConexionNodo2Nodo(string init, string fin, string arista, double t, double c) {
        nodoInicial = init;
        nodoFinal = fin;
        aristaConexion = arista;
        tiempo = t;
        costo = c;
    }

    string getNodoInicial() const { return nodoInicial; }
    string getNodoFinal() const { return nodoFinal; }
    string getAristaConexion() const { return aristaConexion; }
    double getTiempo() const { return tiempo; }
    double getCosto() const { return costo; }

    string to_string_format() const {
        stringstream ss;
        ss << nodoInicial << "," << nodoFinal << "," << aristaConexion << "," << tiempo << "," << costo;
        return ss.str();
    }

    bool from_string_format(const string& linea) {
        stringstream ss(linea);
        string t_str, c_str;

        if (getline(ss, nodoInicial, ',') &&
            getline(ss, nodoFinal, ',') &&
            getline(ss, aristaConexion, ',') &&
            getline(ss, t_str, ',') &&
            getline(ss, c_str, ',')) {

            try {
                tiempo = stod(t_str);
                costo = stod(c_str);
                return true;
            } catch (...) {
                return false;
            }
        }
        return false;
    }
};

class Digrafo {
private:
    set<string> nodos;
    set<string> aristas;
    vector<ConexionNodo2Nodo> rutas;

public:
    void agregarRuta(const string& init, const string& fin, const string& arista, double t, double c) {
        if (t < 0 || c < 0) {
            cout << "Error: Datos invalidos." << endl;
            return;
        }

        ConexionNodo2Nodo nuevaConexion(init, fin, arista, t, c);
        rutas.push_back(nuevaConexion);

        nodos.insert(init);
        nodos.insert(fin);
        aristas.insert(arista);

        cout << "Ruta agregada." << endl;
    }

    void mostrarDigrafo() const {
        cout << "Nodos: { ";
        for (const auto& n : nodos) cout << n << " ";
        cout << "}" << endl;

        cout << "Aristas: { ";
        for (const auto& a : aristas) cout << a << " ";
        cout << "}" << endl;

        cout << left << setw(12) << "Origen" << setw(12) << "Destino"
             << setw(15) << "Arista" << setw(10) << "Tiempo" << setw(10) << "Costo" << endl;

        for (const auto& r : rutas) {
            cout << left << setw(12) << r.getNodoInicial()
                 << setw(12) << r.getNodoFinal()
                 << setw(15) << r.getAristaConexion()
                 << setw(10) << r.getTiempo()
                 << setw(10) << r.getCosto() << endl;
        }
    }

    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            for (const auto& r : rutas) {
                archivo << r.to_string_format() << endl;
            }
            archivo.close();
            cout << "Archivo actualizado." << endl;
        } else {
            cout << "Error al guardar." << endl;
        }
    }

    void leerDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            return;
        }

        rutas.clear();
        nodos.clear();
        aristas.clear();

        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            ConexionNodo2Nodo conexion;
            if (conexion.from_string_format(linea)) {
                rutas.push_back(conexion);
                nodos.insert(conexion.getNodoInicial());
                nodos.insert(conexion.getNodoFinal());
                aristas.insert(conexion.getAristaConexion());
            } else {
                cout << "Error: Registro corrupto omitido." << endl;
            }
        }
        archivo.close();
        cout << "Datos cargados." << endl;
    }
};

int main() {
    Digrafo miDigrafo;
    string nombreArchivo = "digrafo_datos.txt";

    miDigrafo.leerDesdeArchivo(nombreArchivo);

    int opcion;
    do {
        cout << "1. Mostrar Digrafo" << endl;
        cout << "2. Agregar conexion" << endl;
        cout << "3. Guardar archivo" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            miDigrafo.mostrarDigrafo();
        }
        else if (opcion == 2) {
            string orig, dest, arista;
            double t, c;
            cout << "Origen: ";
            cin >> orig;
            cout << "Destino: ";
            cin >> dest;
            cout << "Arista: ";
            cin >> arista;
            cout << "Tiempo: ";
            cin >> t;
            cout << "Costo: ";
            cin >> c;

            miDigrafo.agregarRuta(orig, dest, arista, t, c);
        }
        else if (opcion == 3) {
            miDigrafo.guardarEnArchivo(nombreArchivo);
        }
        else if (opcion == 4) {
            miDigrafo.guardarEnArchivo(nombreArchivo);
        }
    } while (opcion != 4);

    return 0;
}
