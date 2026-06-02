#include <iostream>
#include "funcionesOrdenamiento.h"

using namespace std;

void menuBurbuja() {
    int opcion;
    
    do {
        cout << "\n========== ORDENAMIENTO BURBUJA ==========\n";
        cout << "1. Ordenar enteros\n";
        cout << "2. Ordenar caracteres\n";
        cout << "3. Ordenar estudiantes\n";
        cout << "4. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            OrdenadorInt o;
            o.cargar();
            o.ordenar();
            o.mostrar();
            
            vector<string> datos = o.obtenerDatos();
            if (!datos.empty()) {
                cout << "\n[?] Deseas convertir los datos ordenados?\n";
                int formato;
                cout << "1. JSON | 2. XML | 3. CSV | 4. TXT | 5. No: ";
                cin >> formato;
                
                if (formato >= 1 && formato <= 4) {
                    if (formato == 1) convertirAJSON("burbuja_int", datos);
                    else if (formato == 2) convertirAXML("burbuja_int", datos);
                    else if (formato == 3) convertirACSV("burbuja_int", datos);
                    else if (formato == 4) convertirATXT("burbuja_int", datos);
                }
            }
        }
        else if (opcion == 2) {
            OrdenadorChar o;
            o.cargar();
            o.ordenar();
            o.mostrar();
            
            vector<string> datos = o.obtenerDatos();
            if (!datos.empty()) {
                cout << "\n[?] Deseas convertir los datos ordenados?\n";
                int formato;
                cout << "1. JSON | 2. XML | 3. CSV | 4. TXT | 5. No: ";
                cin >> formato;
                
                if (formato >= 1 && formato <= 4) {
                    if (formato == 1) convertirAJSON("burbuja_char", datos);
                    else if (formato == 2) convertirAXML("burbuja_char", datos);
                    else if (formato == 3) convertirACSV("burbuja_char", datos);
                    else if (formato == 4) convertirATXT("burbuja_char", datos);
                }
            }
        }
        else if (opcion == 3) {
            OrdenadorEstudiante o;
            o.cargar();
            o.ordenar();
            o.mostrar();
            
            vector<string> datos = o.obtenerDatos();
            if (!datos.empty()) {
                cout << "\n[?] Deseas convertir los datos ordenados?\n";
                int formato;
                cout << "1. JSON | 2. XML | 3. CSV | 4. TXT | 5. No: ";
                cin >> formato;
                
                if (formato >= 1 && formato <= 4) {
                    if (formato == 1) convertirAJSON("burbuja_estudiantes", datos);
                    else if (formato == 2) convertirAXML("burbuja_estudiantes", datos);
                    else if (formato == 3) convertirACSV("burbuja_estudiantes", datos);
                    else if (formato == 4) convertirATXT("burbuja_estudiantes", datos);
                }
            }
        }
        else if (opcion == 4) {
            break;
        }
    } while (opcion != 4);
}

void menuMergeSort() {
    int opcion;
    
    do {
        cout << "\n========== MERGE SORT ==========\n";
        cout << "1. Cargar y ordenar\n";
        cout << "2. Ver arreglo actual\n";
        cout << "3. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        static MergeSortHandler merge;
        
        if (opcion == 1) {
            merge.cargar();
            merge.ordenar();
            merge.mostrar();
            
            vector<string> datos = merge.obtenerDatos();
            if (!datos.empty()) {
                cout << "\n[?] Deseas convertir los datos ordenados?\n";
                int formato;
                cout << "1. JSON | 2. XML | 3. CSV | 4. TXT | 5. No: ";
                cin >> formato;
                
                if (formato >= 1 && formato <= 4) {
                    if (formato == 1) convertirAJSON("mergesort", datos);
                    else if (formato == 2) convertirAXML("mergesort", datos);
                    else if (formato == 3) convertirACSV("mergesort", datos);
                    else if (formato == 4) convertirATXT("mergesort", datos);
                }
            }
        }
        else if (opcion == 2) {
            merge.mostrar();
        }
        else if (opcion == 3) {
            break;
        }
    } while (opcion != 3);
}

void menuQuickSort() {
    int opcion;
    
    do {
        cout << "\n========== QUICK SORT ==========\n";
        cout << "1. Cargar y ordenar\n";
        cout << "2. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            QuickSortHandler quick;
            quick.cargar();
            quick.ordenar();
            quick.mostrar();
            
            vector<string> datos = quick.obtenerDatos();
            if (!datos.empty()) {
                cout << "\n[?] Deseas convertir los datos ordenados?\n";
                int formato;
                cout << "1. JSON | 2. XML | 3. CSV | 4. TXT | 5. No: ";
                cin >> formato;
                
                if (formato >= 1 && formato <= 4) {
                    if (formato == 1) convertirAJSON("quicksort", datos);
                    else if (formato == 2) convertirAXML("quicksort", datos);
                    else if (formato == 3) convertirACSV("quicksort", datos);
                    else if (formato == 4) convertirATXT("quicksort", datos);
                }
            }
        }
        else if (opcion == 2) {
            break;
        }
    } while (opcion != 2);
}

int main(){
    int opc;
    
    do {
        cout << "\n========================================\n";
        cout << "  MENU PRINCIPAL - ALGORITMOS ORDENAMIENTO\n";
        cout << "========================================\n";
        cout << "1. Ordenamiento Burbuja\n";
        cout << "2. Merge Sort\n";
        cout << "3. Quick Sort\n";
        cout << "Cualquier otro numero para salir.\n";
        cout << "========================================\n";
        cout << "Selecciona una opcion: ";
        cin >> opc;
        
        if (opc == 1) {
            menuBurbuja();
        }
        else if (opc == 2) {
            menuMergeSort();
        }
        else if (opc == 3) {
            menuQuickSort();
        }
        
    } while (opc >= 1 && opc <= 3);
    
    cout << "\n[*] Programa finalizado.\n";
    return 0;
}
