#ifndef ORDENADOR_H
#define ORDENADOR_H

#include <iostream>
#include <string>
using namespace std;

const int TAM = 5;

struct Estudiante {
    string nombre;
    float  promedio;
};

class Ordenador {
public:
    virtual void cargar()   = 0;
    virtual void ordenar()  = 0;
    virtual void mostrar()  = 0;
    virtual ~Ordenador() {}
};

class OrdenadorInt : public Ordenador {
private:
    int datos[TAM];

public:
    void cargar() override {
        cout << "\n   Ingresa " << TAM << " enteros:\n";
        for (int i = 0; i < TAM; i++) {
            cout << "   [" << i + 1 << "]: ";
            cin >> datos[i];
        }
    }

    void ordenar() override {
        for (int i = 0; i < TAM - 1; i++)
            for (int j = 0; j < TAM - 1 - i; j++)
                if (datos[j] > datos[j + 1])
                    swap(datos[j], datos[j + 1]);
    }

    void mostrar() override {
        cout << "\n   Resultado: ";
        for (int i = 0; i < TAM; i++)
            cout << datos[i] << " ";
        cout << "\n";
    }
};


class OrdenadorChar : public Ordenador {
private:
    char datos[TAM];

public:
    void cargar() override {
        cout << "\n   Ingresa " << TAM << " caracteres:\n";
        for (int i = 0; i < TAM; i++) {
            cout << "   [" << i + 1 << "]: ";
            cin >> datos[i];
        }
    }

    void ordenar() override {
        for (int i = 0; i < TAM - 1; i++)
            for (int j = 0; j < TAM - 1 - i; j++)
                if (datos[j] > datos[j + 1])
                    swap(datos[j], datos[j + 1]);
    }

    void mostrar() override {
        cout << "\n   Resultado: ";
        for (int i = 0; i < TAM; i++)
            cout << datos[i] << " ";
        cout << "\n";
    }
};


class OrdenadorEstudiante : public Ordenador {
private:
    Estudiante datos[TAM];

public:
    void cargar() override {
        cout << "\n   Ingresa " << TAM << " estudiantes:\n";
        for (int i = 0; i < TAM; i++) {
            cout << "   Nombre   [" << i + 1 << "]: ";
            cin.ignore(); getline(cin, datos[i].nombre);
            cout << "   Promedio [" << i + 1 << "]: ";
            cin >> datos[i].promedio;
        }
    }

    void ordenar() override {
        for (int i = 0; i < TAM - 1; i++)
            for (int j = 0; j < TAM - 1 - i; j++)
                if (datos[j].promedio > datos[j + 1].promedio)
                    swap(datos[j], datos[j + 1]);
    }

    void mostrar() override {
        cout << "\n   Resultado (menor a mayor promedio):\n";
        for (int i = 0; i < TAM; i++)
            cout << "   [" << i + 1 << "]  "
                 << datos[i].nombre
                 << "   " << datos[i].promedio << "\n";
    }
};

#endif