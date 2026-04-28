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
    int* indices;
    int capacidadMax;
    int cantidadActual;

    void merge(int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        int* L = new int[n1];
        int* R = new int[n2];

        for (int i = 0; i < n1; i++) L[i] = indices[inicio + i];
        for (int j = 0; j < n2; j++) R[j] = indices[medio + 1 + j];

        int i = 0, j = 0, k = inicio;

        while (i < n1 && j < n2) {
            if (listaProductos[L[i]].getPrecio() <= listaProductos[R[j]].getPrecio()) {
                indices[k] = L[i];
                i++;
            } else {
                indices[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            indices[k] = L[i];
            i++; k++;
        }

        while (j < n2) {
            indices[k] = R[j];
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
        indices = new int[capacidadMax];
    }

    ~Inventario() {
        delete[] listaProductos;
        delete[] indices;
    }

    void agregarProducto(string nombre, float precio) {
        if (cantidadActual < capacidadMax) {
            listaProductos[cantidadActual] = Producto(nombre, precio);
            indices[cantidadActual] = cantidadActual; 
            cantidadActual++;
        }
    }

    void mostrarInventarioOrdenado() {
        for (int i = 0; i < cantidadActual; i++) {
            listaProductos[indices[i]].mostrar();
        }
    }
    
    void mostrarInventarioOriginal() {
        for (int i = 0; i < cantidadActual; i++) {
            listaProductos[i].mostrar();
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

    cout << "\n--- ORDEN DE LLEGADA (MEMORIA REAL) ---" << endl;
    miTienda.mostrarInventarioOriginal();

    miTienda.ordenarPorPrecio();

    cout << "\n--- ORDENADO POR PRECIO (INDIRECTO) ---" << endl;
    miTienda.mostrarInventarioOrdenado();

    return 0;
}