#include "Funciones.h"
#include <fstream>
#include <sstream>

string limpiarCadena(const string& str) {
    size_t primero = str.find_first_not_of(" \t\r\n\"");
    if (primero == string::npos) return "";
    size_t ultimo = str.find_last_not_of(" \t\r\n\",");
    return str.substr(primero, (ultimo - primero + 1));
}

void guardarCSV(const ArbolPOO& arbol, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    archivo << "nodoInicial,nodoFinal,aristaConexion,tiempo,costo\n";
    for (const auto& r : arbol.getRutas()) {
        archivo << r.nodoInicial << "," << r.nodoFinal << ","
                << r.aristaConexion << "," << r.tiempo << "," << r.costo << "\n";
    }
    archivo.close();
}

void guardarXML(const ArbolPOO& arbol, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    archivo << "<arbol>\n";
    for (const auto& r : arbol.getRutas()) {
        archivo << "  <ruta>\n";
        archivo << "    <nodoInicial>" << r.nodoInicial << "</nodoInicial>\n";
        archivo << "    <nodoFinal>" << r.nodoFinal << "</nodoFinal>\n";
        archivo << "    <aristaConexion>" << r.aristaConexion << "</aristaConexion>\n";
        archivo << "    <tiempo>" << r.tiempo << "</tiempo>\n";
        archivo << "    <costo>" << r.costo << "</costo>\n";
        archivo << "  </ruta>\n";
    }
    archivo << "</arbol>\n";
    archivo.close();
}

void guardarJSON(const ArbolPOO& arbol, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    archivo << "{\n  \"rutas\": [\n";
    auto rutas = arbol.getRutas();
    for (size_t i = 0; i < rutas.size(); i++) {
        archivo << "    {\n";
        archivo << "      \"nodoInicial\": \"" << rutas[i].nodoInicial << "\",\n";
        archivo << "      \"nodoFinal\": \"" << rutas[i].nodoFinal << "\",\n";
        archivo << "      \"aristaConexion\": \"" << rutas[i].aristaConexion << "\",\n";
        archivo << "      \"tiempo\": " << rutas[i].tiempo << ",\n";
        archivo << "      \"costo\": " << rutas[i].costo << "\n";
        archivo << "    }" << (i < rutas.size() - 1 ? "," : "") << "\n";
    }
    archivo << "  ]\n}\n";
    archivo.close();
}

void abrirCSV(ArbolPOO& arbol, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "[!] No se pudo abrir el archivo. Iniciando con arbol vacio.\n";
        return;
    }
    arbol.vaciar();
    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string nInicial, nFinal, arista, sTiempo, sCosto;

        getline(ss, nInicial, ',');
        getline(ss, nFinal, ',');
        getline(ss, arista, ',');
        getline(ss, sTiempo, ',');
        getline(ss, sCosto, ',');

        if(!nInicial.empty() && !nFinal.empty()) {
            arbol.ingresarConexion(nInicial, nFinal, arista, stod(sTiempo), stod(sCosto));
        }
    }
    archivo.close();
    cout << "-> Datos del arbol cargados desde CSV.\n";
}

void abrirXML(ArbolPOO& arbol, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    arbol.vaciar();
    string linea, nInicial, nFinal, arista;
    double tiempo = 0, costo = 0;

    while (getline(archivo, linea)) {
        size_t posIni = linea.find("<");
        size_t posFin = linea.find(">");
        if (posIni == string::npos || posFin == string::npos) continue;

        string etiqueta = linea.substr(posIni + 1, posFin - posIni - 1);
        size_t posCierre = linea.find("</" + etiqueta + ">");

        if (posCierre != string::npos) {
            string valor = linea.substr(posFin + 1, posCierre - posFin - 1);
            if (etiqueta == "nodoInicial") nInicial = valor;
            else if (etiqueta == "nodoFinal") nFinal = valor;
            else if (etiqueta == "aristaConexion") arista = valor;
            else if (etiqueta == "tiempo") tiempo = stod(valor);
            else if (etiqueta == "costo") {
                costo = stod(valor);
                arbol.ingresarConexion(nInicial, nFinal, arista, tiempo, costo);
            }
        }
    }
    archivo.close();
    cout << "-> Datos del arbol cargados desde XML.\n";
}

void abrirJSON(ArbolPOO& arbol, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    arbol.vaciar();
    string linea, nInicial, nFinal, arista;
    double tiempo = 0, costo = 0;

    while (getline(archivo, linea)) {
        size_t dosPuntos = linea.find(":");
        if (dosPuntos == string::npos) continue;

        string clave = limpiarCadena(linea.substr(0, dosPuntos));
        string valor = limpiarCadena(linea.substr(dosPuntos + 1));

        if (clave == "nodoInicial") nInicial = valor;
        else if (clave == "nodoFinal") nFinal = valor;
        else if (clave == "aristaConexion") arista = valor;
        else if (clave == "tiempo") tiempo = stod(valor);
        else if (clave == "costo") {
            costo = stod(valor);
            arbol.ingresarConexion(nInicial, nFinal, arista, tiempo, costo);
        }
    }
    archivo.close();
    cout << "-> Datos del arbol cargados desde JSON.\n";
}

void menuArbol(ArbolPOO& arbol, int tipoArchivo, string nombreFichero) {
    int opcion;
    do {
        cout << "\n========== MENU DEL ARBOL ==========\n";
        cout << "1. Ingresar rama (Conexion)\n";
        cout << "2. Borrar rama existente\n";
        cout << "3. DIBUJAR ARBOL JERARQUICO (Forma de raiz y hojas)\n";
        cout << "4. Mostrar lista de conexiones crudas\n";
        cout << "5. Extraer ruta optima en el Arbol (Por Tiempo)\n";
        cout << "6. Extraer ruta optima en el Arbol (Por Costo)\n";
        cout << "7. Guardar cambios y finalizar programa\n";
        cout << "Selecciona una accion: ";
        cin >> opcion;

        if (opcion == 1) {
            string ini, fin, ar;
            double t, c;
            cout << "Nodo Inicial: "; cin >> ini;
            cout << "Nodo Final (Hijo): "; cin >> fin;
            cout << "Nombre de Arista: "; cin >> ar;
            cout << "Tiempo: "; cin >> t;
            cout << "Costo: "; cin >> c;
            arbol.ingresarConexion(ini, fin, ar, t, c);
            cout << "[+] Rama agregada al arbol.\n";
        }
        else if (opcion == 2) {
            string ini, fin;
            cout << "Nodo Padre: "; cin >> ini;
            cout << "Nodo Hijo a desconectar: "; cin >> fin;
            if (arbol.borrarConexion(ini, fin)) cout << "[-] Rama podada exitosamente.\n";
            else cout << "[!] No se encontro la rama.\n";
        }
        else if (opcion == 3) {
            string raiz;
            cout << "Ingrese el nombre del Nodo Raiz desde el cual dibujar el arbol: ";
            cin >> raiz;
            arbol.mostrarArbolJerarquico(raiz);
        }
        else if (opcion == 4) {
            arbol.mostrarConexionesCrudas();
        }
        else if (opcion == 5 || opcion == 6) {
            string origen, destino;
            cout << "Nodo Raiz (Origen): "; cin >> origen;
            cout << "Nodo Destino: "; cin >> destino;
            arbol.aplicarDijkstra(origen, destino, (opcion == 6));
        }
        else if (opcion == 7) {
            if (tipoArchivo == 1 || tipoArchivo == 2) guardarCSV(arbol, nombreFichero);
            else if (tipoArchivo == 3) guardarXML(arbol, nombreFichero);
            else if (tipoArchivo == 4) guardarJSON(arbol, nombreFichero);
            cout << "\n[✓] Arbol guardado en '" << nombreFichero << "'.\n";
        }
    } while (opcion != 7);
}

int main() {
    ArbolPOO miArbol;
    int tipoArchivo = 0, opcionAccion = 0;
    string nombreFichero = "";

    cout << "======= CONFIGURACION DEL SISTEMA DE ARBOLES =======\n";
    cout << "1. TXT\n2. CSV\n3. XML\n4. JSON\nOpcion: ";
    cin >> tipoArchivo;

    if (tipoArchivo == 1) nombreFichero = "arbol_datos.txt";
    else if (tipoArchivo == 2) nombreFichero = "arbol_datos.csv";
    else if (tipoArchivo == 3) nombreFichero = "arbol_datos.xml";
    else if (tipoArchivo == 4) nombreFichero = "arbol_datos.json";
    else { nombreFichero = "arbol_datos.csv"; tipoArchivo = 2; }

    cout << "\n1. Empezar un arbol vacio\n2. Cargar arbol desde archivo\nOpcion: ";
    cin >> opcionAccion;

    if (opcionAccion == 2) {
        if (tipoArchivo == 1 || tipoArchivo == 2) abrirCSV(miArbol, nombreFichero);
        else if (tipoArchivo == 3) abrirXML(miArbol, nombreFichero);
        else if (tipoArchivo == 4) abrirJSON(miArbol, nombreFichero);
    }

    menuArbol(miArbol, tipoArchivo, nombreFichero);

    return 0;
}
