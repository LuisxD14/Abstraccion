#include "FuncionesDigrafo.h"

int main() {
    Digrafo miDigrafo;
    string archivoBase = "digrafo_salida.txt";

    miDigrafo.leerDesdeArchivo(archivoBase);

    int opcion;
    do {
        cout << "\n1. Mostrar Digrafo" << endl;
        cout << "2. Agregar conexion" << endl;
        cout << "3. Guardar / Exportar archivo" << endl;
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
            int subOp;
            cout << "  1. Formato TXT" << endl;
            cout << "  2. Formato JSON" << endl;
            cout << "  3. Formato XML" << endl;
            cout << "  4. Formato CSV" << endl;
            cout << "  Elige formato: ";
            cin >> subOp;
            miDigrafo.exportarDatos(subOp);
        }
        else if (opcion == 4) {
            miDigrafo.exportarDatos(1);
        }
    } while (opcion != 4);

    return 0;
}
