#include "FuncionesQD.h"

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

    ejecutarQuickSort(lista, 0, n - 1, criterio);

    cout << "\nResultado final:\n";
    mostrarLista(lista, n);

    delete[] lista;
    return 0;
}