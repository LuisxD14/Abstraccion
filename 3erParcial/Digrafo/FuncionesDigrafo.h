#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

inline string xmlEscape(const string& s) {
    string r;
    for (char c : s) {
        switch (c) {
            case '&': r += "&amp;"; break;
            case '<': r += "&lt;"; break;
            case '>': r += "&gt;"; break;
            case '"': r += "&quot;"; break;
            case '\'': r += "&apos;"; break;
            default: r += c; break;
        }
    }
    return r;
}

inline string jsonEscape(const string& s) {
    string r;
    for (char c : s) {
        switch (c) {
            case '\\': r += "\\\\"; break;
            case '"': r += "\\\""; break;
            case '\n': r += "\\n"; break;
            case '\r': break;
            case '\t': r += "\\t"; break;
            default: r += c; break;
        }
    }
    return r;
}

inline string csvEscape(const string& s) {
    string r = "\"";
    for (char c : s) {
        if (c == '"') r += "\"\"";
        else r += c;
    }
    r += "\"";
    return r;
}

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

    void exportarDatos(int formato) {
        string nombre;
        string extension;

        if (formato == 1) extension = ".txt";
        else if (formato == 2) extension = ".json";
        else if (formato == 3) extension = ".xml";
        else if (formato == 4) extension = ".csv";
        else {
            cout << "Formato invalido." << endl;
            return;
        }

        nombre = "digrafo_salida" + extension;
        ofstream archivo(nombre);
        if (!archivo.is_open()) {
            cout << "Error al exportar." << endl;
            return;
        }

        if (formato == 1) {
            for (const auto& r : rutas) {
                archivo << r.to_string_format() << endl;
            }
        }
        else if (formato == 2) {
            archivo << "{\n  \"rutas\": [\n";
            for (size_t i = 0; i < rutas.size(); ++i) {
                archivo << "    {\n";
                archivo << "      \"nodoInicial\": \"" << jsonEscape(rutas[i].getNodoInicial()) << "\",\n";
                archivo << "      \"nodoFinal\": \"" << jsonEscape(rutas[i].getNodoFinal()) << "\",\n";
                archivo << "      \"aristaConexion\": \"" << jsonEscape(rutas[i].getAristaConexion()) << "\",\n";
                archivo << "      \"tiempo\": " << rutas[i].getTiempo() << ",\n";
                archivo << "      \"costo\": " << rutas[i].getCosto() << "\n";
                archivo << "    }";
                if (i < rutas.size() - 1) archivo << ",";
                archivo << "\n";
            }
            archivo << "  ]\n}\n";
        }
        else if (formato == 3) {
            archivo << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<digrafo>\n";
            for (const auto& r : rutas) {
                archivo << "  <conexion>\n";
                archivo << "    <nodoInicial>" << xmlEscape(r.getNodoInicial()) << "</nodoInicial>\n";
                archivo << "    <nodoFinal>" << xmlEscape(r.getNodoFinal()) << "</nodoFinal>\n";
                archivo << "    <aristaConexion>" << xmlEscape(r.getAristaConexion()) << "</aristaConexion>\n";
                archivo << "    <tiempo>" << r.getTiempo() << "</tiempo>\n";
                archivo << "    <costo>" << r.getCosto() << "</costo>\n";
                archivo << "  </conexion>\n";
            }
            archivo << "</digrafo>\n";
        }
        else if (formato == 4) {
            archivo << "nodoInicial,nodoFinal,aristaConexion,tiempo,costo\n";
            for (const auto& r : rutas) {
                archivo << csvEscape(r.getNodoInicial()) << ","
                        << csvEscape(r.getNodoFinal()) << ","
                        << csvEscape(r.getAristaConexion()) << ","
                        << r.getTiempo() << ","
                        << r.getCosto() << "\n";
            }
        }

        archivo.close();
        cout << "Exportado a " << nombre << endl;
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

#endif
