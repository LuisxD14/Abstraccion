#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Registro {
    string nombre;
    string valor;
};

// ===== PILA =====
class Pila {
    int datos[100];
    int cantidad;
public:
    Pila();
    void agregar(int valor);
    void quitar();
    void mostrar() const;
    bool estaVacia() const;
    bool estaLlena() const;
    int obtenerTamano() const;
    vector<string> obtenerDatos() const;
};

// ===== COLA =====
struct Producto {
    string nombre;
    float precio;
};

const int MAX_COLA = 5;

class Cola {
private:
    Producto arreglo[MAX_COLA];
    int inicio;
    int fin;
    int cantidad;

public:
    Cola();
    bool estaVacia() const;
    bool estaLlena() const;
    int tamano() const;
    Producto frente() const;
    void encolar(Producto p);
    void desencolar();
    void mostrar() const;
    vector<string> obtenerDatos() const;
};

// ===== LISTA =====
const int MAX_LISTA = 10;

class Lista {
private:
    int datos[MAX_LISTA];
    int cantidad;

public:
    Lista();
    void agregarElemento(int valor);
    void quitarElemento();
    void mostrarLista() const;
    bool estaVacia() const;
    bool estaLlena() const;
    int obtenerTamano() const;
    vector<string> obtenerDatos() const;
};

// ===== FUNCIONES DE CONVERSIÓN =====
void convertirAJSON(const string& nombreArchivo, const vector<string>& datos);
void convertirAXML(const string& nombreArchivo, const vector<string>& datos);
void convertirACSV(const string& nombreArchivo, const vector<string>& datos);
void convertirATXT(const string& nombreArchivo, const vector<string>& datos);

// Función auxiliar para leer datos
vector<Registro> leerDatos(const string& nombreArchivo);

#endif
