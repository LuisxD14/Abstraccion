#include "Funciones.h"
#include <fstream>
#include <sstream>

string limpiarCadena(const string& str) {
    size_t primero = str.find_first_not_of(" \t\r\n\"");
    if (primero == string::npos) return "";
    size_t ultimo = str.find_last_not_of(" \t\r\n\",");
    return str.substr(primero, (ultimo - primero + 1));
}

//(GUARDAR)

void guardarCSV(const GrafoPOO& grafo, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    archivo << "nodoInicial,nodoFinal,aristaConexion,tiempo,costo\n";
    for (const auto& r : grafo.getRutas()) {
        archivo << r.nodoInicial << "," << r.nodoFinal << ","
                << r.aristaConexion << "," << r.tiempo << "," << r.costo << "\n";
    }
    archivo.close();
}

void guardarXML(const GrafoPOO& grafo, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    archivo << "<grafo>\n";
    for (const auto& r : grafo.getRutas()) {
        archivo << "  <ruta>\n";
        archivo << "    <nodoInicial>" << r.nodoInicial << "</nodoInicial>\n";
        archivo << "    <nodoFinal>" << r.nodoFinal << "</nodoFinal>\n";
        archivo << "    <aristaConexion>" << r.aristaConexion << "</aristaConexion>\n";
        archivo << "    <tiempo>" << r.tiempo << "</tiempo>\n";
        archivo << "    <costo>" << r.costo << "</costo>\n";
        archivo << "  </ruta>\n";
    }
    archivo << "</grafo>\n";
    archivo.close();
}

void guardarJSON(const GrafoPOO& grafo, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    archivo << "{\n  \"rutas\": [\n";
    auto rutas = grafo.getRutas();
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

//(ABRIR)

void abrirCSV(GrafoPOO& grafo, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo. Iniciando con árbol vacío.\n";
        return;
    }
    grafo.vaciar();
    string linea;
    getline(archivo, linea); // Omitir encabezado

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
            grafo.ingresarConexion(nInicial, nFinal, arista, stod(sTiempo), stod(sCosto));
        }
    }
    archivo.close();
    cout << "Datos cargados correctamente desde el archivo.\n";
}

void abrirXML(GrafoPOO& grafo, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo XML. Iniciando vacío.\n";
        return;
    }
    grafo.vaciar();
    string linea;
    string nInicial, nFinal, arista;
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
                grafo.ingresarConexion(nInicial, nFinal, arista, tiempo, costo);
            }
        }
    }
    archivo.close();
    cout << "Archivo XML parseado e importado con éxito al árbol.\n";
}

void abrirJSON(GrafoPOO& grafo, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo JSON. Iniciando vacío.\n";
        return;
    }
    grafo.vaciar();
    string linea;
    string nInicial, nFinal, arista;
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
            grafo.ingresarConexion(nInicial, nFinal, arista, tiempo, costo);
        }
    }
    archivo.close();
    cout << "Estructura JSON leída e integrada al árbol con éxito.\n";
}


void menuArbol(GrafoPOO& grafo, int tipoArchivo, string nombreFichero) {
    int opcion;
    do {
        cout << "\nMENU DEL ARBOL\n";
        cout << "1. Ingresar conexion (Nodo a Nodo)\n";
        cout << "2. Borrar conexion existente\n";
        cout << "3. Mostrar estructura completa del arbol\n";
        cout << "4. Buscar ruta optima (Por Tiempo)\n";
        cout << "5. Buscar ruta optima (Por Costo)\n";
        cout << "6. Guardar cambios y finalizar programa\n";
        cout << "Selecciona una accion: ";
        cin >> opcion;

        if (opcion == 1) {
            string ini, fin, ar;
            double t, c;
            cout << "Ingrese Nodo Inicial: "; cin >> ini;
            cout << "Ingrese Nodo Final: "; cin >> fin;
            cout << "Nombre de la Arista vinculante: "; cin >> ar;
            cout << "Costo de Tiempo asociado: "; cin >> t;
            cout << "Costo Monetario asociado: "; cin >> c;
            grafo.ingresarConexion(ini, fin, ar, t, c);
            cout << "Conexion registrada de forma dinamica.\n";
        }
        else if (opcion == 2) {
            string ini, fin;
            cout << "Nodo Inicial de la conexion a borrar: "; cin >> ini;
            cout << "Nodo Final de la conexion a borrar: "; cin >> fin;
            if (grafo.borrarConexion(ini, fin)) {
                cout << "Conexion eliminada exitosamente del árbol.\n";
            } else {
                cout << "No se encontro coincidencia para eliminar.\n";
            }
        }
        else if (opcion == 3) {
            grafo.mostrarConexiones();
        }
        else if (opcion == 4 || opcion == 5) {
            string origen, destino;
            cout << "Establezca Nodo de Origen: "; cin >> origen;
            cout << "Establezca Nodo de Destino: "; cin >> destino;
            grafo.aplicarDijkstra(origen, destino, (opcion == 5));
        }
        else if (opcion == 6) {
            if (tipoArchivo == 1 || tipoArchivo == 2) guardarCSV(grafo, nombreFichero);
            else if (tipoArchivo == 3) guardarXML(grafo, nombreFichero);
            else if (tipoArchivo == 4) guardarJSON(grafo, nombreFichero);
            cout << "\nModificaciones resguardadas exitosamente'" << nombreFichero;
        }
    } while (opcion != 6);
}

int main() {
    GrafoPOO miGrafo;
    int tipoArchivo = 0;
    int opcionAccion = 0;
    string nombreFichero = "";

    cout << "CONFIGURACION ALMACENAMIENTO\n";
    cout << "Selecciona el formato:\n";
    cout << "1. Formato TXT\n";
    cout << "2. .CSV\n";
    cout << "3. .XML\n";
    cout << "4. .JSON\n";
    cout << "-------------------------------------------------------\n";
    cout << "Opcion elegida: ";
    cin >> tipoArchivo;

    // Asignar el nombre del archivo según la extensión seleccionada
    if (tipoArchivo == 1) nombreFichero = "arbol_datos.txt";
    else if (tipoArchivo == 2) nombreFichero = "arbol_datos.csv";
    else if (tipoArchivo == 3) nombreFichero = "arbol_datos.xml";
    else if (tipoArchivo == 4) nombreFichero = "arbol_datos.json";
    else {
        cout << "Opcion invalida. Usando formato CSV por defecto.\n";
        tipoArchivo = 2;
        nombreFichero = "arbol_datos.csv";
    }

    cout << "\nMODALIDAD DE APERTURA DEL ARBOL\n";
    cout << "1. Crear un arbol completamente nuevo (Sobreescribir/Empezar limpio)\n";
    cout << "2. Abrir y cargar un arbol existente (Lectura Obligatoria)\n";
    cout << "Opcion elegida: ";
    cin >> opcionAccion;

    if (opcionAccion == 2) {
        cout << "\nIntentando leer '" << nombreFichero << "'...\n";
        if (tipoArchivo == 1 || tipoArchivo == 2) abrirCSV(miGrafo, nombreFichero);
        else if (tipoArchivo == 3) abrirXML(miGrafo, nombreFichero);
        else if (tipoArchivo == 4) abrirJSON(miGrafo, nombreFichero);
    } else {
        cout << "\nestructura limpia de memoria.\n";
    }

    // Despliegue del segundo menú interactivo de operaciones del grafo
        menuArbol(miGrafo, tipoArchivo, nombreFichero);

    return 0;
}
