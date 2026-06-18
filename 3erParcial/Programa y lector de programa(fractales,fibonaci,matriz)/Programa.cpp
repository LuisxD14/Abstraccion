
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

string xmlEscape(const string& s) {
    string r;
    for (char c : s) {
        switch (c) {
            case '&': r += "&amp;"; break;
            case '<': r += "&lt;"; break;
            case '>': r += "&gt;"; break;
            case '"': r += "&quot;"; break;
            case '\'': r += "&apos;"; break;
            default: r += c; break;
        }
    }
    return r;
}

string jsonEscape(const string& s) {
    string r;
    for (char c : s) {
        switch (c) {
            case '\\': r += "\\\\"; break;
            case '"': r += "\\\""; break;
            case '\n': r += "\\n"; break;
            case '\r': break;
            case '\t': r += "\\t"; break;
            default: r += c; break;
        }
    }
    return r;
}

string csvEscape(const string& s) {
    string r = "\"";
    for (char c : s) {
        if (c == '"') r += "\"\"";
        else r += c;
    }
    r += "\"";
    return r;
}

string nombrePrograma(int op) {
    if (op == 1) return "fibonacci";
    if (op == 2) return "matrices";
    if (op == 3) return "sierpinski";
    if (op == 4) return "polvo_de_cantor";
    return "salida";
}

string extensionArchivo(int op) {
    if (op == 1) return "txt";
    if (op == 2) return "json";
    if (op == 3) return "xml";
    if (op == 4) return "csv";
    return "";
}

string formatearMatriz(const vector<vector<double>>& m, const string& titulo) {
    ostringstream out;
    out << titulo << "\n";
    for (const auto& fila : m) {
        for (double v : fila) {
            out << setw(12) << v;
        }
        out << "\n";
    }
    return out.str();
}

string obtenerFibonacci() {
    int n;
    cout << "Cuantos terminos desea mostrar: ";
    cin >> n;

    if (n <= 0) {
        return "Programa Fibonacci\nNo se puede generar una secuencia con esa cantidad de terminos.\n";
    }

    if (n > 93) {
        return "Programa Fibonacci\nLa cantidad solicitada es demasiado grande para este programa.\n";
    }

    ostringstream out;
    out << "Programa Fibonacci\n";
    out << "Terminos solicitados: " << n << "\n";
    out << "Secuencia\n";

    unsigned long long a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            out << "F(0) = 0\n";
        } else if (i == 1) {
            out << "F(1) = 1\n";
        } else {
            unsigned long long c = a + b;
            a = b;
            b = c;
            out << "F(" << i << ") = " << b << "\n";
        }
    }

    return out.str();
}

vector<vector<double>> leerMatriz(int filas, int columnas, const string& nombre) {
    vector<vector<double>> m(filas, vector<double>(columnas));
    cout << "Ingresa los valores de " << nombre << "\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << nombre << "[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> m[i][j];
        }
    }
    return m;
}

vector<vector<double>> multiplicarMatrices(const vector<vector<double>>& a, const vector<vector<double>>& b) {
    int filasA = (int)a.size();
    int columnasA = (int)a[0].size();
    int columnasB = (int)b[0].size();
    vector<vector<double>> r(filasA, vector<double>(columnasB, 0.0));
    for (int i = 0; i < filasA; ++i) {
        for (int j = 0; j < columnasB; ++j) {
            for (int k = 0; k < columnasA; ++k) {
                r[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return r;
}

vector<vector<double>> multiplicarConstante(const vector<vector<double>>& a, double c) {
    vector<vector<double>> r = a;
    for (auto& fila : r) {
        for (double& v : fila) {
            v *= c;
        }
    }
    return r;
}

string obtenerMatrices() {
    int filasA, columnasA, filasB, columnasB;
    double constante;

    cout << "Filas de la matriz A: ";
    cin >> filasA;
    cout << "Columnas de la matriz A: ";
    cin >> columnasA;
    cout << "Filas de la matriz B: ";
    cin >> filasB;
    cout << "Columnas de la matriz B: ";
    cin >> columnasB;
    cout << "Constante para multiplicar A: ";
    cin >> constante;

    if (filasA <= 0 || columnasA <= 0 || filasB <= 0 || columnasB <= 0) {
        return "Programa Matrices\nLas dimensiones deben ser mayores que cero.\n";
    }

    vector<vector<double>> A = leerMatriz(filasA, columnasA, "A");
    vector<vector<double>> B = leerMatriz(filasB, columnasB, "B");

    ostringstream out;
    out << "Programa Matrices\n";
    out << "Matriz A\n";
    out << formatearMatriz(A, "");
    out << "Matriz B\n";
    out << formatearMatriz(B, "");

    out << "Constante\n";
    out << constante << "\n";

    vector<vector<double>> Aconstante = multiplicarConstante(A, constante);
    out << "Resultado de A por constante\n";
    out << formatearMatriz(Aconstante, "");

    if (columnasA == filasB) {
        vector<vector<double>> AB = multiplicarMatrices(A, B);
        out << "Resultado de A por B\n";
        out << formatearMatriz(AB, "");
    } else {
        out << "Resultado de A por B\n";
        out << "La multiplicacion no es posible con esas dimensiones.\n";
    }

    return out.str();
}

void sierpinskiFill(vector<string>& g, int row, int col, int size) {
    if (size == 1) {
        g[row][col] = '*';
        return;
    }
    int half = size / 2;
    sierpinskiFill(g, row, col, half);
    sierpinskiFill(g, row + half, col - half, half);
    sierpinskiFill(g, row + half, col + half, half);
}

string obtenerSierpinski() {
    int nivel;
    cout << "Nivel del fractal: ";
    cin >> nivel;

    if (nivel < 0 || nivel > 8) {
        return "Triangulo de Sierpinski\nEl nivel debe estar entre 0 y 8.\n";
    }

    int altura = 1 << nivel;
    int ancho = altura * 2 - 1;
    vector<string> g(altura, string(ancho, ' '));
    sierpinskiFill(g, 0, ancho / 2, altura);

    ostringstream out;
    out << "Triangulo de Sierpinski\n";
    for (const auto& fila : g) {
        out << fila << "\n";
    }
    return out.str();
}

void cantorFill(vector<string>& g, int row, int col, int size) {
    if (size == 1) {
        g[row][col] = '#';
        return;
    }
    int part = size / 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) continue;
            cantorFill(g, row + i * part, col + j * part, part);
        }
    }
}

string obtenerCantor() {
    int nivel;
    cout << "Nivel del polvo de Cantor: ";
    cin >> nivel;

    if (nivel < 0 || nivel > 5) {
        return "Polvo de Cantor\nEl nivel debe estar entre 0 y 5.\n";
    }

    int tam = 1;
    for (int i = 0; i < nivel; ++i) tam *= 3;

    vector<string> g(tam, string(tam, ' '));
    cantorFill(g, 0, 0, tam);

    ostringstream out;
    out << "Polvo de Cantor\n";
    for (const auto& fila : g) {
        out << fila << "\n";
    }
    return out.str();
}

void guardarArchivo(const string& programa, const string& extension, const string& contenido) {
    string nombre = programa + "." + extension;

    ofstream archivo(nombre);
    if (!archivo) {
        cout << "No se pudo crear el archivo\n";
        return;
    }

    if (extension == "txt") {
        archivo << contenido;
    } else if (extension == "json") {
        archivo << "{\n";
        archivo << "  \"programa\": \"" << jsonEscape(programa) << "\",\n";
        archivo << "  \"contenido\": \"" << jsonEscape(contenido) << "\"\n";
        archivo << "}\n";
    } else if (extension == "xml") {
        archivo << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        archivo << "<archivo>\n";
        archivo << "  <programa>" << xmlEscape(programa) << "</programa>\n";
        archivo << "  <contenido><![CDATA[" << contenido << "]]></contenido>\n";
        archivo << "</archivo>\n";
    } else if (extension == "csv") {
        archivo << "programa,contenido\n";
        string limpio = contenido;
        for (char& c : limpio) {
            if (c == '\n') c = ' ';
        }
        archivo << csvEscape(programa) << "," << csvEscape(limpio) << "\n";
    }

    cout << "Archivo guardado como " << nombre << "\n";
}

int main() {
    int opcionPrograma, opcionFormato;

    do {
        cout << "\nMenu principal\n";
        cout << "1 Fibonacci\n";
        cout << "2 Matrices\n";
        cout << "3 Triangulo de Sierpinski\n";
        cout << "4 Polvo de Cantor\n";
        cout << "5 Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcionPrograma;

        if (opcionPrograma == 5) {
            break;
        }

        string contenido;
        if (opcionPrograma == 1) {
            contenido = obtenerFibonacci();
        } else if (opcionPrograma == 2) {
            contenido = obtenerMatrices();
        } else if (opcionPrograma == 3) {
            contenido = obtenerSierpinski();
        } else if (opcionPrograma == 4) {
            contenido = obtenerCantor();
        } else {
            cout << "Opcion no valida\n";
            continue;
        }

        cout << "\nMenu de formato\n";
        cout << "1 txt\n";
        cout << "2 json\n";
        cout << "3 xml\n";
        cout << "4 csv\n";
        cout << "Elige un formato: ";
        cin >> opcionFormato;

        string ext = extensionArchivo(opcionFormato);
        if (ext.empty()) {
            cout << "Formato no valido\n";
            continue;
        }

        guardarArchivo(nombrePrograma(opcionPrograma), ext, contenido);

    } while (true);

    return 0;
}
