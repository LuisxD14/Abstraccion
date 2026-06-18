/*
 * grafo.cpp
 * Compilar: g++ -o grafo grafo.cpp
 * Ejecutar: ./grafo
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// ── Estructuras ──────────────────────────────

struct Nodo  {
    int id; std::string nombre;
};
struct Arista {
    int id; std::string nombre;
};

struct Conexion {
    int nodoInicial;
    int nodoFinal;
    int aristaConexion;
    //double tiempo;
};

struct Ruta {
    int id;
    std::string nombre;
    std::vector<Conexion> conexiones;
};

struct Grafo {
    std::vector<Nodo>   nodos;
    std::vector<Arista> aristas;
    std::vector<Ruta>   rutas;
};

// ── Helpers ──────────────────────────────────

std::string jsonStr(const std::string& s) {
    return "\"" + s + "\"";
}

std::string xmlEsc(const std::string& s) {
    std::string o;
    for (char c : s) {
        if      (c == '&') o += "&amp;";
        else if (c == '<') o += "&lt;";
        else if (c == '>') o += "&gt;";
        else               o += c;
    }
    return o;
}

// ── Exportadores ─────────────────────────────

void exportCSV(const Grafo& g) {
    std::ofstream f("grafo.csv");
    f << "### NODOS\nid,nombre\n";
    for (auto& n : g.nodos)
        f << n.id << "," << n.nombre << "\n";

    f << "\n### ARISTAS\nid,nombre\n";
    for (auto& a : g.aristas)
        f << a.id << "," << a.nombre << "\n";

    f << "\n### RUTAS\nrutaId,rutaNombre,nodoInicial,nodoFinal,aristaConexion,tiempo\n";
    for (auto& r : g.rutas)
        for (auto& c : r.conexiones)
            f << r.id << "," << r.nombre << ","
              << c.nodoInicial << "," << c.nodoFinal << ",";

    std::cout << "✓ grafo.csv\n";
}

void exportTXT(const Grafo& g) {
    std::ofstream f("grafo.txt");
    f << "=== NODOS ===\n";
    for (auto& n : g.nodos)
        f << "  [" << n.id << "] " << n.nombre << "\n";

    f << "\n=== ARISTAS ===\n";
    for (auto& a : g.aristas)
        f << "  [" << a.id << "] " << a.nombre << "\n";

    f << "\n=== RUTAS ===\n";
    for (auto& r : g.rutas) {
        f << "  Ruta [" << r.id << "] " << r.nombre << "\n";
        for (auto& c : r.conexiones)
            f << "    Nodo " << c.nodoInicial
              << " -[A" << c.aristaConexion << "]-> "
              << "Nodo " << c.nodoFinal;
    }
    std::cout << "✓ grafo.txt\n";
}

void exportXML(const Grafo& g) {
    std::ofstream f("grafo.xml");
    f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<grafo>\n";

    f << "  <nodos>\n";
    for (auto& n : g.nodos)
        f << "    <nodo id=\"" << n.id << "\"><nombre>" << xmlEsc(n.nombre) << "</nombre></nodo>\n";
    f << "  </nodos>\n";

    f << "  <aristas>\n";
    for (auto& a : g.aristas)
        f << "    <arista id=\"" << a.id << "\"><nombre>" << xmlEsc(a.nombre) << "</nombre></arista>\n";
    f << "  </aristas>\n";

    f << "  <rutas>\n";
    for (auto& r : g.rutas) {
        f << "    <ruta id=\"" << r.id << "\"><nombre>" << xmlEsc(r.nombre) << "</nombre>\n";
        f << "      <conexiones>\n";
        for (auto& c : r.conexiones)
            f << "        <conexionNodo2Nodo>"
              << "<nodoInicial>"    << c.nodoInicial    << "</nodoInicial>"
              << "<nodoFinal>"      << c.nodoFinal      << "</nodoFinal>"
              << "<aristaConexion>" << c.aristaConexion << "</aristaConexion>"
              << "</conexionNodo2Nodo>\n";
        f << "      </conexiones>\n    </ruta>\n";
    }
    f << "  </rutas>\n</grafo>\n";
    std::cout << "✓ grafo.xml\n";
}

void exportJSON(const Grafo& g) {
    std::ofstream f("grafo.json");
    f << "{\n  \"nodos\": [\n";
    for (size_t i = 0; i < g.nodos.size(); i++)
        f << "    {\"id\":" << g.nodos[i].id << ",\"nombre\":" << jsonStr(g.nodos[i].nombre) << "}"
          << (i+1 < g.nodos.size() ? "," : "") << "\n";

    f << "  ],\n  \"aristas\": [\n";
    for (size_t i = 0; i < g.aristas.size(); i++)
        f << "    {\"id\":" << g.aristas[i].id << ",\"nombre\":" << jsonStr(g.aristas[i].nombre) << "}"
          << (i+1 < g.aristas.size() ? "," : "") << "\n";

    f << "  ],\n  \"rutas\": [\n";
    for (size_t ri = 0; ri < g.rutas.size(); ri++) {
        auto& r = g.rutas[ri];
        f << "    {\"id\":" << r.id << ",\"nombre\":" << jsonStr(r.nombre) << ",\"conexiones\":[\n";
        for (size_t ci = 0; ci < r.conexiones.size(); ci++) {
            auto& c = r.conexiones[ci];
            f << "      {\"nodoInicial\":" << c.nodoInicial
              << ",\"nodoFinal\":"         << c.nodoFinal
              << ",\"aristaConexion\":"    << c.aristaConexion
              << (ci+1 < r.conexiones.size() ? "," : "") << "\n";
        }
        f << "    ]}" << (ri+1 < g.rutas.size() ? "," : "") << "\n";
    }
    f << "  ]\n}\n";
    std::cout << " grafo.json\n";
}

// ── Datos de ejemplo ─────────────────────────

// Grafo grafoEjemplo() {
//     Grafo g;
//     g.nodos   = {{1,"Ciudad A"},{2,"Ciudad B"},{3,"Ciudad C"},{4,"Ciudad D"},{5,"Ciudad E"}};
//     g.aristas = {{10,"Autopista Norte"},{11,"Carretera Sur"},{12,"Camino Rural"},{13,"Via Expresa"},{14,"Puente Central"}};
//
//     Ruta r1; r1.id=100; r1.nombre="Ruta Norte";
//     r1.conexiones = {{1,2,10,1.5},{2,3,11,2.0},{3,4,12,0.75},{4,5,13,3.0},{5,1,14,1.0}};
//
//     Ruta r2; r2.id=101; r2.nombre="Ruta Sur";
//     r2.conexiones = {{1,3,13,2.5},{3,5,14,1.5},{5,2,10,2.0},{2,4,11,1.0},{4,1,12,0.5}};
//
//     g.rutas = {r1, r2};
//     return g;
// }
void editarNodo(Grafo& g) {
    int id; std::cout << "ID del nodo a editar: "; std::cin >> id; std::cin.ignore();
    for (auto& n : g.nodos) {
        if (n.id == id) {
            std::cout << "Nuevo nombre [" << n.nombre << "]: ";
            std::getline(std::cin, n.nombre);
            std::cout << " Nodo actualizado.\n"; return;
        }
    }
    std::cout << "Nodo no encontrado.\n";
}

void editarArista(Grafo& g) {
    int id; std::cout << "ID de la arista a editar: "; std::cin >> id; std::cin.ignore();
    for (auto& a : g.aristas) {
        if (a.id == id) {
            std::cout << "Nuevo nombre [" << a.nombre << "]: ";
            std::getline(std::cin, a.nombre);
            std::cout << " Arista actualizada.\n"; return;
        }
    }
    std::cout << "Arista no encontrada.\n";
}

void editarRuta(Grafo& g) {
    int id; std::cout << "ID de la ruta a editar: "; std::cin >> id; std::cin.ignore();
    for (auto& r : g.rutas) {
        if (r.id == id) {
            std::cout << "Nuevo nombre [" << r.nombre << "]: ";
            std::getline(std::cin, r.nombre);
            std::cout << "¿Editar conexiones? (s/n): ";
            char ch; std::cin >> ch; std::cin.ignore();
            if (ch == 's' || ch == 'S') {
                r.conexiones.clear();
                int n; std::cout << " conexiones: "; std::cin >> n;
                for (int i = 0; i < n; i++) {
                    Conexion c;
                    std::cout << "  nodoInicial nodoFinal aristaConexion tiempo: ";
                    std::cin >> c.nodoInicial >> c.nodoFinal >> c.aristaConexion;
                    r.conexiones.push_back(c);
                }
                std::cin.ignore();
            }
            std::cout << "Ruta actualizada.\n"; return;
        }
    }
    std::cout << "Ruta no encontrada.\n";
}

void eliminarNodo(Grafo& g) {
    int id; std::cout << "ID del nodo a eliminar: "; std::cin >> id; std::cin.ignore();
    for (auto it = g.nodos.begin(); it != g.nodos.end(); ++it) {
        if (it->id == id) { g.nodos.erase(it); std::cout << "✓ Nodo eliminado.\n"; return; }
    }
    std::cout << "Nodo no encontrado.\n";
}

void eliminarArista(Grafo& g) {
    int id; std::cout << "ID de la arista a eliminar: "; std::cin >> id; std::cin.ignore();
    for (auto it = g.aristas.begin(); it != g.aristas.end(); ++it) {
        if (it->id == id) { g.aristas.erase(it); std::cout << "✓ Arista eliminada.\n"; return; }
    }
    std::cout << "Arista no encontrada.\n";
}

void eliminarRuta(Grafo& g) {
    int id; std::cout << "ID de la ruta a eliminar: "; std::cin >> id; std::cin.ignore();
    for (auto it = g.rutas.begin(); it != g.rutas.end(); ++it) {
        if (it->id == id) { g.rutas.erase(it); std::cout << "Ruta eliminada.\n"; return; }
    }
    std::cout << "Ruta no encontrada.\n";
}
void verRuta(const Grafo& g) {
    int id; std::cout << "ID de la ruta: "; std::cin >> id; std::cin.ignore();
    for (auto& r : g.rutas) {
        if (r.id == id) {
            std::cout << "\nRuta [" << r.id << "] " << r.nombre << "\n";
            int i = 1;
            for (auto& c : r.conexiones)
                std::cout << "  " << i++ << ". Nodo " << c.nodoInicial
                          << " -[A" << c.aristaConexion << "]-> "
                          << "Nodo " << c.nodoFinal;
            return;
        }
    }
    std::cout << "✗ Ruta no encontrada.\n";
}

int main() {
    Grafo g; //= grafoEjemplo();
    int op;
    do {
        std::cout<< std::endl <<"1. Ver nodo" << std::endl;
        std::cout<< "2. Agregar nodo" << std::endl;
        std::cout<< "3. Agregar arista" << std::endl;
        std::cout<< "4. Agregar ruta" << std::endl;
        std::cout<< "5. Editar nodo" << std::endl;
        std::cout<< "6. Editar arista" << std::endl;
        std::cout<< "7. Editar Ruta" << std::endl;
        std::cout<< "8. Eliminar nodo" << std::endl;
        std::cout<< "9. Eliminar arista" << std::endl;
        std::cout<< "10. Eliminar ruta" << std::endl;
        std::cout<< "11. Exportar a CSV" << std::endl;
        std::cout<< "12. Exportar a TXT" << std::endl;
        std::cout<< "13. Exportar a XML" << std::endl;
        std::cout<< "14. Exportar a JSON" << std::endl;
        std::cout<< "15. Ver ruta" << std::endl;
        std::cout<< "0. Salir" << std::endl;
        std::cout<< "Opcion: ";
        std::cin >> op; std::cin.ignore();

        if (op == 1) {
            std::cout << "Nodos: ";
            for (auto& n : g.nodos) std::cout << "[" << n.id << "]" << n.nombre << " ";
            std::cout << "\nAristas: ";
            for (auto& a : g.aristas) std::cout << "[" << a.id << "]" << a.nombre << " ";
            std::cout << "\nRutas: " << g.rutas.size() << "\n";
        }
        else if (op == 2) {
            Nodo n;
            std::cout << "ID: "; std::cin >> n.id; std::cin.ignore();
            std::cout << "Nombre: "; std::getline(std::cin, n.nombre);
            g.nodos.push_back(n);
        }
        else if (op == 3) {
            Arista a;
            std::cout << "ID: "; std::cin >> a.id; std::cin.ignore();
            std::cout << "Nombre: "; std::getline(std::cin, a.nombre);
            g.aristas.push_back(a);
        }
        else if (op == 4) {
            Ruta r;
            std::cout << "ID ruta: "; std::cin >> r.id; std::cin.ignore();
            std::cout << "Nombre: "; std::getline(std::cin, r.nombre);
            int n; std::cout << "# conexiones: "; std::cin >> n;
            for (int i = 0; i < n; i++) {
                Conexion c;
                std::cout << "  nodoInicial nodoFinal aristaConexion : ";
                std::cin >> c.nodoInicial >> c.nodoFinal >> c.aristaConexion;
                r.conexiones.push_back(c);
            }
            std::cin.ignore();
            g.rutas.push_back(r);
        }
        else if (op == 15) verRuta(g);
        else if (op == 5) editarNodo(g);
        else if (op == 6) editarArista(g);
        else if (op == 7) editarRuta(g);
        else if (op == 8) eliminarNodo(g);
        else if (op == 9) eliminarArista(g);
        else if (op == 10) eliminarRuta(g);
        else if (op == 11) exportCSV(g);
        else if (op == 12) exportTXT(g);
        else if (op == 13)exportXML(g);
        else if (op == 14) exportJSON(g);
    } while (op != 0);
}
