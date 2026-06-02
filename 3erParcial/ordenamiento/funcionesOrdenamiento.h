#ifndef FUNCIONES_ORDENAMIENTO_H
#define FUNCIONES_ORDENAMIENTO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// ===== BURBUJA =====
class Ordenador {
public:
    virtual void cargar()   = 0;
    virtual void ordenar()  = 0;
    virtual void mostrar()  = 0;
    virtual vector<string> obtenerDatos() = 0;
    virtual ~Ordenador() {}
};

struct Estudiante {
    string nombre;
    float  promedio;
};

const int TAM = 5;

class OrdenadorInt : public Ordenador {
private:
    int datos[TAM];

public:
    void cargar() override;
    void ordenar() override;
    void mostrar() override;
    vector<string> obtenerDatos() override;
};

class OrdenadorChar : public Ordenador {
private:
    char datos[TAM];

public:
    void cargar() override;
    void ordenar() override;
    void mostrar() override;
    vector<string> obtenerDatos() override;
};

class OrdenadorEstudiante : public Ordenador {
private:
    Estudiante datos[TAM];

public:
    void cargar() override;
    void ordenar() override;
    void mostrar() override;
    vector<string> obtenerDatos() override;
};

// ===== MERGE SORT =====
class MergeSortHandler {
private:
    int arr[100];
    int n;

public:
    MergeSortHandler();
    void cargar();
    void ordenar();
    void mostrar() const;
    vector<string> obtenerDatos() const;
    
private:
    void merge(int izq, int mid, int der);
    void mergeSort(int izq, int der);
};

// ===== QUICK SORT =====
struct Dato {
    char letra;
    int numero;
};

class QuickSortHandler {
private:
    Dato* lista;
    int n;
    int criterio;

public:
    QuickSortHandler();
    ~QuickSortHandler();
    void cargar();
    void ordenar();
    void mostrar() const;
    vector<string> obtenerDatos() const;

private:
    void intercambiar(Dato &a, Dato &b);
    int particion(int bajo, int alto);
    void ejecutarQuickSort(int bajo, int alto);
};

// ===== FUNCIONES DE CONVERSIÓN =====
void convertirAJSON(const string& nombreArchivo, const vector<string>& datos);
void convertirAXML(const string& nombreArchivo, const vector<string>& datos);
void convertirACSV(const string& nombreArchivo, const vector<string>& datos);
void convertirATXT(const string& nombreArchivo, const vector<string>& datos);

#endif
