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

class ArbolPOO {
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

    void imprimirNodoJerarquico(const string& actual, string sangria, set<string>& visitados) const {
        visitados.insert(actual);

        for (const auto& ruta : rutas) {
            if (ruta.nodoInicial == actual) {
                if (visitados.find(ruta.nodoFinal) != visitados.end()) continue;

                cout << sangria << " L--[Arista: " << ruta.aristaConexion << " | T:" << ruta.tiempo << " C:$" << ruta.costo << "]--> Nodo: " << ruta.nodoFinal << "\n";
                imprimirNodoJerarquico(ruta.nodoFinal, sangria + "     ", visitados);
            }
        }
    }

public:
    void vaciar() {
        rutas.clear();
        nodos.clear();
        aristas.clear();
    }

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

    void mostrarArbolJerarquico(string raiz) const {
        if (rutas.empty()) {
            cout << "\n[!] El arbol esta vacio.\n";
            return;
        }
        if (nodos.find(raiz) == nodos.end()) {
            cout << "\n[!] El nodo raiz '" << raiz << "' no existe en el arbol.\n";
            return;
        }

        cout << "\n=== ESTRUCTURA VISUAL DEL ARBOL ===\n";
        cout << "[RAIZ] Nodo: " << raiz << "\n";
        set<string> visitados;
        imprimirNodoJerarquico(raiz, "", visitados);
        cout << "===================================\n";
    }

    void mostrarConexionesCrudas() const {
        cout << "\n--- Lista de Ramas (Conexiones) ---\n";
        for (const auto& r : rutas) {
            cout << r.nodoInicial << " -> " << r.nodoFinal
                 << " (" << r.aristaConexion << ") T:" << r.tiempo << " C:$" << r.costo << "\n";
        }
    }

    void aplicarDijkstra(string origen, string destino, bool optimizarCosto) {
        if (nodos.find(origen) == nodos.end() || nodos.find(destino) == nodos.end()) {
            cout << "\n[!] Nodos no encontrados.\n";
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
            cout << "\n[!] No hay ruta en el arbol entre " << origen << " y " << destino << ".\n";
            return;
        }

        cout << "\n=== RUTA OPTIMA EN EL ARBOL (" << (optimizarCosto ? "COSTO" : "TIEMPO") << ") ===\n";
        cout << "Metrica total acumulada: " << distancias[destino] << "\nTrayectoria: ";

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

    vector<ConexionNodo2Nodo> getRutas() const { return rutas; }
};

#endif
