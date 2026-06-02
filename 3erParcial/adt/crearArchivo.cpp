#include <iostream>
#include <fstream>
#include <iterator>
#include "funciones.h"

using namespace std;

void menuPila(Pila& pila) {
    int opcion, valor;

    do {
        cout << "\n--- MENU PILA ---\n";
        cout << "1. Agregar elemento\n";
        cout << "2. Quitar elemento\n";
        cout << "3. Mostrar pila\n";
        cout << "4. Verificar si esta vacia\n";
        cout << "5. Verificar si esta llena\n";
        cout << "6. Mostrar tamanio de la pila\n";
        cout << "7. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Valor: ";
                cin >> valor;
                pila.agregar(valor);
                break;
            case 2:
                pila.quitar();
                break;
            case 3:
                pila.mostrar();
                break;
            case 4:
                if (pila.estaVacia())
                    cout << "La pila ESTA VACIA.\n";
                else
                    cout << "La pila NO esta vacia.\n";
                break;
            case 5:
                if (pila.estaLlena())
                    cout << "La pila ESTA LLENA.\n";
                else
                    cout << "La pila NO esta llena.\n";
                break;
            case 6:
                cout << "Tamanio de la pila: " << pila.obtenerTamano() << "\n";
                break;
            case 7:
                cout << "\nVolviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 7);
}

void menuCola(Cola& cola) {
    int opcion;

    do {
        cout << "\n--- Menu de Cola ---\n";
        cout << "1. Agregar producto\n";
        cout << "2. Quitar producto\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Verificar si esta vacia\n";
        cout << "5. Verificar si esta llena\n";
        cout << "6. Mostrar tamano de la cola\n";
        cout << "7. Volver al menu principal\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            Producto p;
            cout << "\n  Nuevo producto\n";
            cout << "  Nombre : ";
            cin.ignore();
            getline(cin, p.nombre);
            cout << "  Precio : $ ";
            cin >> p.precio;
            cola.encolar(p);
            cout << "\n  Producto encolado.\n";
            break;
        }

        case 2:
            cola.desencolar();
            break;

        case 3:
            cout << "\n  Cola actual\n";
            cola.mostrar();
            break;

        case 4:
            cout << "\n  La cola "
                 << (cola.estaVacia() ? "SI esta vacia." : "NO esta vacia.")
                 << "\n";
            break;

        case 5:
            cout << "\n  La cola "
                 << (cola.estaLlena() ? "SI esta llena." : "NO esta llena.")
                 << "\n";
            break;

        case 6:
            cout << "\n  Elementos en cola : " << cola.tamano()
                 << " / " << MAX_COLA << "\n";
            break;

        case 7:
            cout << "\n  Volviendo al menu principal.\n\n";
            break;

        default:
            cout << "\n  Opcion invalida.\n";
        }

    } while (opcion != 7);
}

void menuLista(Lista& lista) {
    int opcion, valor;

    do {
        cout << "\n--- Menú de Lista ---\n";
        cout << "1. Agregar elemento\n";
        cout << "2. Quitar elemento\n";
        cout << "3. Mostrar lista\n";
        cout << "4. Verificar si esta vacia\n";
        cout << "5. Verificar si esta llena\n";
        cout << "6. Mostrar tamaño de la lista\n";
        cout << "7. Volver al menu principal\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingresa un numero entero: ";
                cin >> valor;
                lista.agregarElemento(valor);
                break;
            case 2:
                lista.quitarElemento();
                break;
            case 3:
                lista.mostrarLista();
                break;
            case 4:
                if (lista.estaVacia())
                    cout << "La lista esta vacia.\n";
                else
                    cout << "La lista no esta vacia.\n";
                break;
            case 5:
                if (lista.estaLlena())
                    cout << "La lista esta llena.\n";
                else
                    cout << "La lista aun tiene espacio.\n";
                break;
            case 6:
                cout << "Tamaño actual: " << lista.obtenerTamano() << "\n";
                break;
            case 7:
                cout << "\nVolviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 7);
}

void menuConversion(const string& nombreEstructura, const vector<string>& datos) {
    int formatoOpc;

    do {
        cout << "\n--- MENU DE FORMATOS ---\n";
        cout << "1. Convertir a JSON\n";
        cout << "2. Convertir a XML\n";
        cout << "3. Convertir a CSV\n";
        cout << "4. Convertir a TXT\n";
        cout << "5. No convertir\n";
        cout << "Selecciona un formato: ";
        cin >> formatoOpc;

        switch (formatoOpc) {
            case 1:
                convertirAJSON(nombreEstructura, datos);
                break;
            case 2:
                convertirAXML(nombreEstructura, datos);
                break;
            case 3:
                convertirACSV(nombreEstructura, datos);
                break;
            case 4:
                convertirATXT(nombreEstructura, datos);
                break;
            case 5:
                cout << "\nConversion cancelada.\n";
                break;
            default:
                cout << "\nOpcion invalida.\n";
        }
    } while (formatoOpc < 1 || formatoOpc > 5);
}

int main(){
    int opc;

    do{
        cout << " MENU PRINCIPAL\n";
        cout << "1. Crear Pila\n";
        cout << "2. Crear Cola\n";
        cout << "3. Crear Lista\n";
        cout << "Cualquier otro numero para salir.\n";
        cout << "Selecciona una opcion: ";
        cin >> opc;

        if (opc == 1) {
            Pila pila;
            menuPila(pila);

            if (pila.obtenerTamano() > 0) {
                cout << "\n Deseas convertir los datos de la pila?\n";
                vector<string> datospila = pila.obtenerDatos();
                menuConversion("pila", datospila);
            }
        }
        else if (opc == 2) {
            Cola cola;
            menuCola(cola);

            if (cola.tamano() > 0) {
                cout << "\n Deseas convertir los datos de la cola?\n";
                vector<string> datoscola = cola.obtenerDatos();
                menuConversion("cola", datoscola);
            }
        }
        else if (opc == 3) {
            Lista lista;
            menuLista(lista);

            if (lista.obtenerTamano() > 0) {
                cout << "\n Deseas convertir los datos de la lista?\n";
                vector<string> datoslista = lista.obtenerDatos();
                menuConversion("lista", datoslista);
            }
        }

    } while (opc >= 1 && opc <= 3);

    cout << "\nPrograma finalizado.\n";
    return 0;
}
