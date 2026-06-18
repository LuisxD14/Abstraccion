#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct ConexionNodo2Nodo {
    string nodoInicial;
    string nodoFinal;
    string aristaConexion;
    double tiempo;
    double costo;
};

class GrafoPOO {
private:
    set<string> nodos;
    set<string> aristas;
    vector<ConexionNodo2Nodo> rutas;

    void actualizarComponentes() {
        nodos.clear();
        aristas.clear();
        for (const auto& r : rutas) {
            nodos.insert(r.nodoInicial);
            nodos.insert(r.nodoFinal);
            aristas.insert(r.aristaConexion);
        }
    }

public:
    void vaciar() {
        rutas.clear();
        nodos.clear();
        aristas.clear();
    }

    // MENU DEL ÁRBOL:
    void ingresarConexion(string inicial, string final, string arista, double t, double c) {
        ConexionNodo2Nodo nuevaConexion = {inicial, final, arista, t, c};
        rutas.push_back(nuevaConexion);
        actualizarComponentes();
    }

    bool borrarConexion(string inicial, string final) {
        auto it = remove_if(rutas.begin(), rutas.end(), [&](const ConexionNodo2Nodo& r) {
            return r.nodoInicial == inicial && r.nodoFinal == final;
        });

        if (it != rutas.end()) {
            rutas.erase(it, rutas.end());
            actualizarComponentes();
            return true;
        }
        return false;
    }

    void mostrarConexiones() const {
        if (rutas.empty()) {
            cout << "\nEl árbol está vacío actualmente.\n";
            return;
        }
        cout << "\nCONEXIONES ACTUALES\n";
        for (const auto& r : rutas) {
            cout << "Origen: " << r.nodoInicial << " -> Destino: " << r.nodoFinal
                 << " | Arista: " << r.aristaConexion << " | Tiempo: " << r.tiempo
                 << " | Costo: $" << r.costo << "\n";// MENU DEL ÁRBOL: 3. Mostrar árbol / conexiones
        }
    }

    // MENU DEL ÁRBOL: 4 y 5. Algoritmo de Dijkstra
    void aplicarDijkstra(string origen, string destino, bool optimizarCosto) {
        if (nodos.find(origen) == nodos.end() || nodos.find(destino) == nodos.end()) {
            cout << "\nUno o ambos nodos no existen en el sistema.\n";
            return;
        }

        map<string, double> distancias;
        map<string, string> previos;
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

        for (const auto& n : nodos) {
            distancias[n] = numeric_limits<double>::infinity();
        }

        distancias[origen] = 0;
        pq.push({0, origen});

        while (!pq.empty()) {
            double distActual = pq.top().first;
            string nodoActual = pq.top().second;
            pq.pop();

            if (nodoActual == destino) break;
            if (distActual > distancias[nodoActual]) continue;

            for (const auto& ruta : rutas) {
                if (ruta.nodoInicial == nodoActual) {
                    double peso = optimizarCosto ? ruta.costo : ruta.tiempo;
                    double nuevaDist = distancias[nodoActual] + peso;

                    if (nuevaDist < distancias[ruta.nodoFinal]) {
                        distancias[ruta.nodoFinal] = nuevaDist;
                        previos[ruta.nodoFinal] = nodoActual;
                        pq.push({nuevaDist, ruta.nodoFinal});
                    }
                }
            }
        }

        if (distancias[destino] == numeric_limits<double>::infinity()) {
            cout << "\nNo se encontró ninguna ruta disponible entre " << origen << " y " << destino << ".\n";
            return;
        }

        cout << "\nMEJOR RUTA ENCONTRADA (" << (optimizarCosto ? "COSTO" : "TIEMPO") << ") ===\n";
        cout << "Métrica total acumulada: " << distancias[destino] << "\nTrayectoria: ";

        vector<string> camino;
        for (string at = destino; at != ""; at = previos[at]) {
            camino.push_back(at);
            if (at == origen) break;
        }
        reverse(camino.begin(), camino.end());

        for (size_t i = 0; i < camino.size(); i++) {
            cout << camino[i] << (i < camino.size() - 1 ? " -> " : "\n");
        }
        cout << "\n";
    }

    // Getters y Setters para los flujos de lectura externa
    vector<ConexionNodo2Nodo> getRutas() const { return rutas; }
};

#endif // FUNCIONES_H
