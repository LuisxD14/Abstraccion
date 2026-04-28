#include <iostream>
#include <string>

using namespace std;

class Producto {
private:
    string nombre;
    float precio;

public:
    Producto(string n = "", float p = 0.0) {
        nombre = n;
        precio = p;
    }

    float getPrecio() { return precio; }

    void mostrar() {
        cout << "- " << nombre << " : $" << precio << endl;
    }
};

class Inventario {
private:
    Producto* listaProductos;
    Producto** arrPunteros; 
    int capacidadMax;
    int cantidadActual;

    void merge(int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        Producto** L = new Producto*[n1];
        Producto** R = new Producto*[n2];

        for (int i = 0; i < n1; i++) 
            *(L + i) = *(arrPunteros + inicio + i);
            
        for (int j = 0; j < n2; j++) 
            *(R + j) = *(arrPunteros + medio + 1 + j);

        int i = 0, j = 0, k = inicio;

        while (i < n1 && j < n2) {
            if ((*(L + i))->getPrecio() <= (*(R + j))->getPrecio()) {
                *(arrPunteros + k) = *(L + i);
                i++;
            } else {
                *(arrPunteros + k) = *(R + j);
                j++;
            }
            k++;
        }

        while (i < n1) {
            *(arrPunteros + k) = *(L + i);
            i++; k++;
        }

        while (j < n2) {
            *(arrPunteros + k) = *(R + j);
            j++; k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSortRecursivo(int inicio, int fin) {
        if (inicio >= fin) return;
        int medio = inicio + (fin - inicio) / 2;
        mergeSortRecursivo(inicio, medio);
        mergeSortRecursivo(medio + 1, fin);
        merge(inicio, medio, fin);
    }

public:
    Inventario(int capacidad) {
        capacidadMax = capacidad;
        cantidadActual = 0;
        listaProductos = new Producto[capacidadMax];
        arrPunteros = new Producto*[capacidadMax];
    }

    ~Inventario() {
        delete[] listaProductos;
        delete[] arrPunteros;
    }

    void agregarProducto(string nombre, float precio) {
        if (cantidadActual < capacidadMax) {
            *(listaProductos + cantidadActual) = Producto(nombre, precio);
            *(arrPunteros + cantidadActual) = (listaProductos + cantidadActual);
            cantidadActual++;
        }
    }

    void mostrarInventarioOrdenado() {
        for (int i = 0; i < cantidadActual; i++) {
            (*(arrPunteros + i))->mostrar();
        }
    }

    void ordenarPorPrecio() {
        if (cantidadActual > 1) {
            mergeSortRecursivo(0, cantidadActual - 1);
        }
    }
};

int main() {
    int n;
    cout << "Cuantos productos registrara? ";
    cin >> n;

    Inventario miTienda(n);

    for (int i = 0; i < n; i++) {
        string nombre;
        float precio;
        cout << "\nProducto " << i + 1 << endl;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Precio: ";
        cin >> precio;
        miTienda.agregarProducto(nombre, precio);
    }

    miTienda.ordenarPorPrecio();

    cout << "\n--- INVENTARIO ORDENADO (PUNTEROS INDIRECTOS) ---" << endl;
    miTienda.mostrarInventarioOrdenado();

    return 0;
}