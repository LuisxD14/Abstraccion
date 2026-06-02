#include "funciones.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>

using namespace std;

// ===== IMPLEMENTACIÓN PILA =====
Pila::Pila() : cantidad(0) {}

void Pila::agregar(int valor) {
    if (cantidad < 100)
        datos[cantidad++] = valor;
}

void Pila::quitar() {
    if (cantidad > 0)
        cantidad--;
    else
        puts("La pila esta vacia.");
}

void Pila::mostrar() const {
    if (cantidad == 0) { puts("  [ pila vacia ]"); return; }
    for (int i = cantidad - 1; i >= 0; i--)
        printf("  | %d |\n", datos[i]);
}

bool Pila::estaVacia() const {
    return cantidad == 0;
}

bool Pila::estaLlena() const {
    return cantidad == 100;
}

int Pila::obtenerTamano() const {
    return cantidad;
}

vector<string> Pila::obtenerDatos() const {
    vector<string> resultado;
    for (int i = cantidad - 1; i >= 0; i--) {
        resultado.push_back(to_string(datos[i]));
    }
    return resultado;
}

// ===== IMPLEMENTACIÓN COLA =====
Cola::Cola() : inicio(0), fin(0), cantidad(0) {}

bool Cola::estaVacia() const {
    return cantidad == 0;
}

bool Cola::estaLlena() const {
    return cantidad == MAX_COLA;
}

int Cola::tamano() const {
    return cantidad;
}

Producto Cola::frente() const {
    return arreglo[inicio];
}

void Cola::encolar(Producto p) {
    if (estaLlena()) {
        cout << "\n  [!] La cola esta llena. No se puede encolar.\n";
        return;
    }
    arreglo[fin] = p;
    fin = (fin + 1) % MAX_COLA;
    cantidad++;
}

void Cola::desencolar() {
    if (estaVacia()) {
        cout << "\n  [!] La cola esta vacia. No hay nada que desencolar.\n";
        return;
    }
    cout << "\n  >> Producto eliminado: " << arreglo[inicio].nombre << "\n";
    inicio = (inicio + 1) % MAX_COLA;
    cantidad--;
}

void Cola::mostrar() const {
    if (estaVacia()) {
        cout << "\n  La cola esta vacia.\n";
        return;
    }
    cout << "\n  Pos  Nombre                  Precio\n";
    cout << "  ---  ----------------------  --------\n";
    for (int i = 0; i < cantidad; i++) {
        int idx = (inicio + i) % MAX_COLA;
        cout << "  [" << i + 1 << "]  "
             << arreglo[idx].nombre;

        int pad = 22 - (int)arreglo[idx].nombre.size();
        for (int s = 0; s < pad; s++) cout << ' ';
        cout << "$ " << arreglo[idx].precio << "\n";
    }
}

vector<string> Cola::obtenerDatos() const {
    vector<string> resultado;
    for (int i = 0; i < cantidad; i++) {
        int idx = (inicio + i) % MAX_COLA;
        resultado.push_back(arreglo[idx].nombre + " - $" + to_string((int)arreglo[idx].precio));
    }
    return resultado;
}

// ===== IMPLEMENTACIÓN LISTA =====
Lista::Lista() : cantidad(0) {}

void Lista::agregarElemento(int valor) {
    if (cantidad < MAX_LISTA) {
        datos[cantidad] = valor;
        cantidad++;
        cout << "Elemento agregado.\n";
    } else {
        cout << "Error: La lista esta llena.\n";
    }
}

void Lista::quitarElemento() {
    if (cantidad > 0) {
        cout << "Elemento " << datos[cantidad - 1] << " eliminado.\n";
        cantidad--;
    } else {
        cout << "La lista esta vacia.\n";
    }
}

void Lista::mostrarLista() const {
    if (cantidad == 0) {
        cout << "La lista esta vacia.\n";
        return;
    }
    cout << "\nContenido de la lista:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << i << "]: " << datos[i] << "\n";
    }
}

bool Lista::estaVacia() const {
    return cantidad == 0;
}

bool Lista::estaLlena() const {
    return cantidad == MAX_LISTA;
}

int Lista::obtenerTamano() const {
    return cantidad;
}

vector<string> Lista::obtenerDatos() const {
    vector<string> resultado;
    for (int i = 0; i < cantidad; i++) {
        resultado.push_back(to_string(datos[i]));
    }
    return resultado;
}

// ===== FUNCIONES DE CONVERSIÓN =====
vector<Registro> leerDatos(const string& nombreArchivo) {
    vector<Registro> datos;
    ifstream archivo(nombreArchivo);
    
    if (!archivo.is_open()) {
        cout << "\n[!] No se pudo abrir el archivo: " << nombreArchivo << endl;
        return datos;
    }
    
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            Registro reg;
            reg.nombre = linea;
            reg.valor = linea;
            datos.push_back(reg);
        }
    }
    
    archivo.close();
    return datos;
}

void convertirAJSON(const string& nombreArchivo, const vector<string>& datos) {
    if (datos.empty()) {
        cout << "\n[!] No hay datos para convertir.\n";
        return;
    }
    
    string salidaJSON = nombreArchivo + ".json";
    ofstream archivo(salidaJSON);
    
    if (!archivo.is_open()) {
        cout << "\n[!] No se pudo crear el archivo JSON.\n";
        return;
    }
    
    archivo << "{\n";
    archivo << "  \"registros\": [\n";
    
    for (size_t i = 0; i < datos.size(); ++i) {
        archivo << "    {\n";
        archivo << "      \"dato\": \"" << datos[i] << "\"\n";
        archivo << "    }";
        if (i < datos.size() - 1) {
            archivo << ",";
        }
        archivo << "\n";
    }
    
    archivo << "  ]\n";
    archivo << "}\n";
    
    archivo.close();
    cout << "\n[✓] Archivo convertido a JSON: " << salidaJSON << endl;
}

void convertirAXML(const string& nombreArchivo, const vector<string>& datos) {
    if (datos.empty()) {
        cout << "\n[!] No hay datos para convertir.\n";
        return;
    }
    
    string salidaXML = nombreArchivo + ".xml";
    ofstream archivo(salidaXML);
    
    if (!archivo.is_open()) {
        cout << "\n[!] No se pudo crear el archivo XML.\n";
        return;
    }
    
    archivo << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    archivo << "<datos>\n";
    
    for (const auto& dato : datos) {
        archivo << "  <registro>\n";
        archivo << "    <dato>" << dato << "</dato>\n";
        archivo << "  </registro>\n";
    }
    
    archivo << "</datos>\n";
    
    archivo.close();
    cout << "\n[✓] Archivo convertido a XML: " << salidaXML << endl;
}

void convertirACSV(const string& nombreArchivo, const vector<string>& datos) {
    if (datos.empty()) {
        cout << "\n[!] No hay datos para convertir.\n";
        return;
    }
    
    string salidaCSV = nombreArchivo + ".csv";
    ofstream archivo(salidaCSV);
    
    if (!archivo.is_open()) {
        cout << "\n[!] No se pudo crear el archivo CSV.\n";
        return;
    }
    
    archivo << "ID,Dato\n";
    
    for (size_t i = 0; i < datos.size(); ++i) {
        archivo << i + 1 << ",\"" << datos[i] << "\"\n";
    }
    
    archivo.close();
    cout << "\n[✓] Archivo convertido a CSV: " << salidaCSV << endl;
}

void convertirATXT(const string& nombreArchivo, const vector<string>& datos) {
    if (datos.empty()) {
        cout << "\n[!] No hay datos para convertir.\n";
        return;
    }
    
    string salidaTXT = nombreArchivo + ".txt";
    ofstream archivo(salidaTXT);
    
    if (!archivo.is_open()) {
        cout << "\n[!] No se pudo crear el archivo TXT.\n";
        return;
    }
    
    archivo << "========================================\n";
    archivo << "ARCHIVO DE DATOS CONVERTIDO\n";
    archivo << "========================================\n\n";
    
    for (size_t i = 0; i < datos.size(); ++i) {
        archivo << "[" << i + 1 << "] " << datos[i] << "\n";
    }
    
    archivo << "\n========================================\n";
    archivo << "Total de registros: " << datos.size() << "\n";
    archivo << "========================================\n";
    
    archivo.close();
    cout << "\n[✓] Archivo convertido a TXT: " << salidaTXT << endl;
}
