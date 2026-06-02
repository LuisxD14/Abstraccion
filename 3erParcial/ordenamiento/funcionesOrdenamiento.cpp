#include "funcionesOrdenamiento.h"
#include <algorithm>

// ===== ORDENADOR INT =====
void OrdenadorInt::cargar() {
    cout << "\n   Ingresa " << TAM << " enteros:\n";
    for (int i = 0; i < TAM; i++) {
        cout << "   [" << i + 1 << "]: ";
        cin >> datos[i];
    }
}

void OrdenadorInt::ordenar() {
    for (int i = 0; i < TAM - 1; i++)
        for (int j = 0; j < TAM - 1 - i; j++)
            if (datos[j] > datos[j + 1])
                swap(datos[j], datos[j + 1]);
}

void OrdenadorInt::mostrar() {
    cout << "\n   Resultado: ";
    for (int i = 0; i < TAM; i++)
        cout << datos[i] << " ";
    cout << "\n";
}

vector<string> OrdenadorInt::obtenerDatos() {
    vector<string> resultado;
    for (int i = 0; i < TAM; i++) {
        resultado.push_back(to_string(datos[i]));
    }
    return resultado;
}

// ===== ORDENADOR CHAR =====
void OrdenadorChar::cargar() {
    cout << "\n   Ingresa " << TAM << " caracteres:\n";
    for (int i = 0; i < TAM; i++) {
        cout << "   [" << i + 1 << "]: ";
        cin >> datos[i];
    }
}

void OrdenadorChar::ordenar() {
    for (int i = 0; i < TAM - 1; i++)
        for (int j = 0; j < TAM - 1 - i; j++)
            if (datos[j] > datos[j + 1])
                swap(datos[j], datos[j + 1]);
}

void OrdenadorChar::mostrar() {
    cout << "\n   Resultado: ";
    for (int i = 0; i < TAM; i++)
        cout << datos[i] << " ";
    cout << "\n";
}

vector<string> OrdenadorChar::obtenerDatos() {
    vector<string> resultado;
    for (int i = 0; i < TAM; i++) {
        resultado.push_back(string(1, datos[i]));
    }
    return resultado;
}

// ===== ORDENADOR ESTUDIANTE =====
void OrdenadorEstudiante::cargar() {
    cout << "\n   Ingresa " << TAM << " estudiantes:\n";
    for (int i = 0; i < TAM; i++) {
        cout << "   Nombre   [" << i + 1 << "]: ";
        cin.ignore();
        getline(cin, datos[i].nombre);
        cout << "   Promedio [" << i + 1 << "]: ";
        cin >> datos[i].promedio;
    }
}

void OrdenadorEstudiante::ordenar() {
    for (int i = 0; i < TAM - 1; i++)
        for (int j = 0; j < TAM - 1 - i; j++)
            if (datos[j].promedio > datos[j + 1].promedio)
                swap(datos[j], datos[j + 1]);
}

void OrdenadorEstudiante::mostrar() {
    cout << "\n   Resultado (menor a mayor promedio):\n";
    for (int i = 0; i < TAM; i++)
        cout << "   [" << i + 1 << "]  "
             << datos[i].nombre
             << "   " << datos[i].promedio << "\n";
}

vector<string> OrdenadorEstudiante::obtenerDatos() {
    vector<string> resultado;
    for (int i = 0; i < TAM; i++) {
        resultado.push_back(datos[i].nombre + " (" + to_string((int)datos[i].promedio) + ")");
    }
    return resultado;
}

// ===== MERGE SORT HANDLER =====
MergeSortHandler::MergeSortHandler() : n(0) {}

void MergeSortHandler::cargar() {
    cout << "\n=== Merge Sort ===\n";
    cout << "Cuantos numeros quieres ingresar: ";
    cin >> n;

    cout << "Ingresa los numeros:\n";
    for (int i = 0; i < n; i++) {
        cout << "  [" << i + 1 << "]: ";
        cin >> arr[i];
    }
}

void MergeSortHandler::merge(int izq, int mid, int der) {
    int n1 = mid - izq + 1;
    int n2 = der - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[izq + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = izq;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void MergeSortHandler::mergeSort(int izq, int der) {
    if (izq < der) {
        int mid = (izq + der) / 2;
        mergeSort(izq, mid);
        mergeSort(mid + 1, der);
        merge(izq, mid, der);
    }
}

void MergeSortHandler::ordenar() {
    mergeSort(0, n - 1);
}

void MergeSortHandler::mostrar() const {
    cout << "\n   Resultado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

vector<string> MergeSortHandler::obtenerDatos() const {
    vector<string> resultado;
    for (int i = 0; i < n; i++) {
        resultado.push_back(to_string(arr[i]));
    }
    return resultado;
}

// ===== QUICK SORT HANDLER =====
QuickSortHandler::QuickSortHandler() : lista(nullptr), n(0), criterio(0) {}

QuickSortHandler::~QuickSortHandler() {
    if (lista != nullptr)
        delete[] lista;
}

void QuickSortHandler::cargar() {
    cout << "\n--- QUICK SORT ---\n";
    cout << "Cantidad de elementos: ";
    cin >> n;

    lista = new Dato[n];

    for (int i = 0; i < n; i++) {
        cout << "Elemento " << i + 1 << " (Caracter y Entero): ";
        cin >> lista[i].letra >> lista[i].numero;
    }

    cout << "\nOrdenar por: 1. Caracter | 2. Entero: ";
    cin >> criterio;
}

void QuickSortHandler::intercambiar(Dato &a, Dato &b) {
    Dato temporal = a;
    a = b;
    b = temporal;
}

int QuickSortHandler::particion(int bajo, int alto) {
    Dato pivote = lista[alto];
    int i = (bajo - 1);

    for (int j = bajo; j <= alto - 1; j++) {
        bool condicion = false;
        if (criterio == 1) {
            condicion = (lista[j].letra < pivote.letra);
        } else {
            condicion = (lista[j].numero < pivote.numero);
        }

        if (condicion) {
            i++;
            intercambiar(lista[i], lista[j]);
        }
    }
    intercambiar(lista[i + 1], lista[alto]);
    return (i + 1);
}

void QuickSortHandler::ejecutarQuickSort(int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(bajo, alto);
        ejecutarQuickSort(bajo, pi - 1);
        ejecutarQuickSort(pi + 1, alto);
    }
}

void QuickSortHandler::ordenar() {
    ejecutarQuickSort(0, n - 1);
}

void QuickSortHandler::mostrar() const {
    cout << "\n   Resultado final:\n";
    for (int i = 0; i < n; i++) {
        cout << "   [" << lista[i].letra << ", " << lista[i].numero << "]\n";
    }
}

vector<string> QuickSortHandler::obtenerDatos() const {
    vector<string> resultado;
    for (int i = 0; i < n; i++) {
        resultado.push_back(string(1, lista[i].letra) + " - " + to_string(lista[i].numero));
    }
    return resultado;
}

// ===== FUNCIONES DE CONVERSIÓN =====
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
    archivo << "ARCHIVO DE DATOS ORDENADO\n";
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
