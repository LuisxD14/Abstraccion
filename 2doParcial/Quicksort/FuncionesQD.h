#include <iostream>

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
        if (criterio == 1) {
            condicion = (arreglo[j].letra < pivote.letra);
        } else {
            condicion = (arreglo[j].numero < pivote.numero);
        }

        if (condicion) {
            i++;
            intercambiar(arreglo[i], arreglo[j]);
        }
    }
    intercambiar(arreglo[i + 1], arreglo[alto]);
    return (i + 1);
}

void ejecutarQuickSort(Dato arreglo[], int bajo, int alto, int criterio) {
    if (bajo < alto) {
        int pi = particion(arreglo, bajo, alto, criterio);
        ejecutarQuickSort(arreglo, bajo, pi - 1, criterio);
        ejecutarQuickSort(arreglo, pi + 1, alto, criterio);
    }
}

void mostrarLista(Dato arreglo[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "[" << arreglo[i].letra << ", " << arreglo[i].numero << "] ";
    }
    cout << endl;
}