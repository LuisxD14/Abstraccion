#include <iostream>
#include <string>

using namespace std;

struct Dato {
    char letra;
    int numero;
};

void intercambiar(Dato &a, Dato &b) {
    Dato temporal = a;
    a = b;
    b = temporal;
}

int particion(Dato arreglo[], int bajo, int alto, int criterio) {
    Dato pivote = arreglo[alto];
    int i = (bajo - 1);

    for (int j = bajo; j <= alto - 1; j++) {
        bool condicion = false;
        if (criterio == 1) condicion = (arreglo[j].letra < pivote.letra);
        else condicion = (arreglo[j].numero < pivote.numero);

        if (condicion) {
            i++;
            intercambiar(arreglo[i], arreglo[j]);
        }
    }
    intercambiar(arreglo[i + 1], arreglo[alto]);
    return (i + 1);
}

void quickSortDirecto(Dato arreglo[], int bajo, int alto, int criterio) {
    if (bajo < alto) {
        int pi = particion(arreglo, bajo, alto, criterio);
        quickSortDirecto(arreglo, bajo, pi - 1, criterio);
        quickSortDirecto(arreglo, pi + 1, alto, criterio);
    }
}

int main() {
    int n, criterio;
    cout << "--- QUICK SORT DIRECTO ---\n";
    cout << "Cantidad de elementos: ";
    cin >> n;

    Dato* lista = new Dato[n];

    for (int i = 0; i < n; i++) {
        cout << "Elemento " << i + 1 << " (Caracter y Entero): ";
        cin >> lista[i].letra >> lista[i].numero;
    }

    cout << "\nOrdenar por: 1. Caracter | 2. Entero: ";
    cin >> criterio;

    quickSortDirecto(lista, 0, n - 1, criterio);

    cout << "\nResultado:\n";
    for (int i = 0; i < n; i++) {
        cout << "[" << lista[i].letra << ", " << lista[i].numero << "] ";
    }
    cout << endl;

    delete[] lista;
    return 0;
}