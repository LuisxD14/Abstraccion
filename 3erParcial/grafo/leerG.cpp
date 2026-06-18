/*
 * lector_grafo.cpp
 * Compilar: g++ -o lector lector_grafo.cpp
 * Ejecutar: ./lector
 */

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// ── Estructuras ──────────────────────────────

struct Nodo   { int id; std::string nombre; };
struct Arista { int id; std::string nombre; };

struct Conexion {
    int nodoInicial, nodoFinal, aristaConexion;
    double tiempo;
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

// ── Lectores ─────────────────────────────────

Grafo leerCSV(const std::string& archivo) {
    Grafo g;
    std::ifstream f(archivo);
    if (!f.is_open()) { std::cout << "✗ No se pudo abrir " << archivo << "\n"; return g; }

    std::string linea, seccion;
    while (std::getline(f, linea)) {
        if (linea.empty()) continue;
        if (linea.rfind("###", 0) == 0) { seccion = linea; continue; }
        if (linea.rfind("id,", 0) == 0 || linea.rfind("rutaId", 0) == 0) continue; // header

        std::istringstream ss(linea);
        std::string tok;
        std::vector<std::string> cols;
        while (std::getline(ss, tok, ',')) cols.push_back(tok);

        if (seccion.find("NODOS") != std::string::npos && cols.size() >= 2)
            g.nodos.push_back({std::stoi(cols[0]), cols[1]});
        else if (seccion.find("ARISTAS") != std::string::npos && cols.size() >= 2)
            g.aristas.push_back({std::stoi(cols[0]), cols[1]});
        else if (seccion.find("RUTAS") != std::string::npos && cols.size() >= 6) {
            int rid = std::stoi(cols[0]);
            bool found = false;
            for (auto& r : g.rutas) if (r.id == rid) { found = true; break; }
            if (!found) g.rutas.push_back({rid, cols[1], {}});
            for (auto& r : g.rutas)
                if (r.id == rid)
                    r.conexiones.push_back({std::stoi(cols[2]), std::stoi(cols[3]),
                                            std::stoi(cols[4]), std::stod(cols[5])});
        }
    }
    std::cout << " CSV leído: " << g.nodos.size() << " nodos, "
              << g.aristas.size() << " aristas, " << g.rutas.size() << " rutas.\n";
    return g;
}

Grafo leerJSON(const std::string& archivo) {
    Grafo g;
    std::ifstream f(archivo);
    if (!f.is_open()) { std::cout << " No se pudo abrir " << archivo << "\n"; return g; }

    std::string linea;
    Ruta rutaActual; bool enRuta = false, enConexiones = false;

    while (std::getline(f, linea)) {
        size_t ini = linea.find_first_not_of(" \t");
        if (ini == std::string::npos) continue;
        linea = linea.substr(ini);

        auto extraerStr = [&](const std::string& clave) -> std::string {
            std::string b = "\"" + clave + "\":\"";
            size_t p = linea.find(b);
            if (p == std::string::npos) return "";
            p += b.size();
            size_t e = linea.find('"', p);
            return linea.substr(p, e - p);
        };
        auto extraerNum = [&](const std::string& clave) -> std::string {
            std::string b = "\"" + clave + "\":";
            size_t p = linea.find(b);
            if (p == std::string::npos) return "";
            p += b.size();
            size_t e = linea.find_first_of(",}", p);
            return linea.substr(p, e - p);
        };

        // Detectar secciones
        if (linea.find("\"nodos\"")    != std::string::npos) { enRuta = false; enConexiones = false; continue; }
        if (linea.find("\"aristas\"")  != std::string::npos) { enRuta = false; enConexiones = false; continue; }
        if (linea.find("\"rutas\"")    != std::string::npos) { continue; }
        if (linea.find("\"conexiones\"") != std::string::npos) { enConexiones = true; continue; }
        if (linea == "]}" || linea == "]},") {
            if (enRuta) { g.rutas.push_back(rutaActual); enRuta = false; enConexiones = false; }
            continue;
        }

        if (!enRuta && !enConexiones) {
            // puede ser nodo o arista
            std::string sid = extraerNum("id"), snom = extraerStr("nombre");
            if (!sid.empty() && !snom.empty()) {
                // distinguir: si ya estamos pasando aristas
                if (g.aristas.empty() && linea.find("peso") == std::string::npos)
                    g.nodos.push_back({std::stoi(sid), snom});
                else
                    g.aristas.push_back({std::stoi(sid), snom});
            }
            // inicio de ruta
            std::string rid = extraerNum("id"), rnom = extraerStr("nombre");
            if (!rid.empty() && !rnom.empty() && linea.find("conexiones") == std::string::npos) {
                if (linea.find("\"id\":") != std::string::npos &&
                    g.nodos.size() > 0 && g.aristas.size() > 0) {
                    rutaActual = Ruta();
                    rutaActual.id = std::stoi(rid);
                    rutaActual.nombre = rnom;
                    enRuta = true;
                }
            }
        } else if (enRuta && !enConexiones) {
            std::string rid = extraerNum("id"), rnom = extraerStr("nombre");
            if (!rid.empty()) {
                rutaActual = Ruta();
                rutaActual.id = std::stoi(rid);
                rutaActual.nombre = rnom;
                enConexiones = false;
            }
        } else if (enConexiones) {
            try {
                std::string ni = extraerNum("nodoInicial"), nf = extraerNum("nodoFinal"),
                            ac = extraerNum("aristaConexion"), ti = extraerNum("tiempo");
                if (!ni.empty())
                    rutaActual.conexiones.push_back({std::stoi(ni), std::stoi(nf),
                                                     std::stoi(ac), std::stod(ti)});
            } catch (...) {}
        }
    }

    std::cout << " JSON leído: " << g.nodos.size() << " nodos, "
              << g.aristas.size() << " aristas, " << g.rutas.size() << " rutas.\n";
    return g;
}

Grafo leerXML(const std::string& archivo) {
    Grafo g;
    std::ifstream f(archivo);
    if (!f.is_open()) { std::cout << "✗ No se pudo abrir " << archivo << "\n"; return g; }

    auto entre = [](const std::string& s, const std::string& a, const std::string& b) -> std::string {
        size_t p = s.find(a);
        if (p == std::string::npos) return "";
        p += a.size();
        size_t e = s.find(b, p);
        if (e == std::string::npos) return "";
        return s.substr(p, e - p);
    };

    std::string linea, seccion;
    Ruta rutaActual; bool enRuta = false;

    while (std::getline(f, linea)) {
        size_t ini = linea.find_first_not_of(" \t");
        if (ini == std::string::npos) continue;
        linea = linea.substr(ini);

        if (linea.find("<nodos>")     != std::string::npos) { seccion = "nodos";   continue; }
        if (linea.find("</nodos>")    != std::string::npos) { seccion = "";         continue; }
        if (linea.find("<aristas>")   != std::string::npos) { seccion = "aristas"; continue; }
        if (linea.find("</aristas>")  != std::string::npos) { seccion = "";         continue; }
        if (linea.find("<rutas>")     != std::string::npos) { seccion = "rutas";   continue; }
        if (linea.find("</rutas>")    != std::string::npos) { seccion = "";         continue; }

        if (linea.find("<ruta ") != std::string::npos) {
            if (enRuta) g.rutas.push_back(rutaActual);
            rutaActual = Ruta();
            std::string sid = entre(linea, "id=\"", "\"");
            std::string nom = entre(linea, "<nombre>", "</nombre>");
            if (!sid.empty()) rutaActual.id = std::stoi(sid);
            rutaActual.nombre = nom;
            enRuta = true;
            continue;
        }
        if (linea.find("</ruta>") != std::string::npos) {
            g.rutas.push_back(rutaActual);
            enRuta = false;
            continue;
        }

        try {
            if (seccion == "nodos" && linea.find("<nodo ") != std::string::npos) {
                std::string sid = entre(linea, "id=\"", "\"");
                std::string nom = entre(linea, "<nombre>", "</nombre>");
                if (!sid.empty()) g.nodos.push_back({std::stoi(sid), nom});
            }
            else if (seccion == "aristas" && linea.find("<arista ") != std::string::npos) {
                std::string sid = entre(linea, "id=\"", "\"");
                std::string nom = entre(linea, "<nombre>", "</nombre>");
                if (!sid.empty()) g.aristas.push_back({std::stoi(sid), nom});
            }
            else if (enRuta && linea.find("<conexionNodo2Nodo>") != std::string::npos) {
                Conexion c;
                c.nodoInicial    = std::stoi(entre(linea, "<nodoInicial>",    "</nodoInicial>"));
                c.nodoFinal      = std::stoi(entre(linea, "<nodoFinal>",      "</nodoFinal>"));
                c.aristaConexion = std::stoi(entre(linea, "<aristaConexion>", "</aristaConexion>"));
                c.tiempo         = std::stod(entre(linea, "<tiempo>",         "</tiempo>"));
                rutaActual.conexiones.push_back(c);
            }
        } catch (...) {
            std::cout << "⚠ Línea ignorada: " << linea << "\n";
        }
    }

    std::cout << " XML leído: " << g.nodos.size() << " nodos, "
              << g.aristas.size() << " aristas, " << g.rutas.size() << " rutas.\n";
    return g;
}

Grafo leerTXT(const std::string& archivo) {
    Grafo g;
    std::ifstream f(archivo);
    if (!f.is_open()) { std::cout << " No se pudo abrir " << archivo << "\n"; return g; }

    std::string linea, seccion;
    Ruta rutaActual; bool enRuta = false;

    while (std::getline(f, linea)) {
        size_t ini = linea.find_first_not_of(" \t");
        if (ini == std::string::npos) continue;
        linea = linea.substr(ini);

        if (linea.find("=== NODOS")   != std::string::npos) { seccion = "nodos";   continue; }
        if (linea.find("=== ARISTAS") != std::string::npos) { seccion = "aristas"; continue; }
        if (linea.find("=== RUTAS")   != std::string::npos) { seccion = "rutas";   continue; }
        if (linea.empty()) continue;

        try {
            if (seccion == "nodos" && linea[0] == '[') {
                size_t a = linea.find('[')+1, b = linea.find(']');
                g.nodos.push_back({std::stoi(linea.substr(a, b-a)), linea.substr(b+2)});
            }
            else if (seccion == "aristas" && linea[0] == '[') {
                size_t a = linea.find('[')+1, b = linea.find(']');
                g.aristas.push_back({std::stoi(linea.substr(a, b-a)), linea.substr(b+2)});
            }
            else if (seccion == "rutas") {
                if (linea.rfind("Ruta [", 0) == 0) {
                    if (enRuta) g.rutas.push_back(rutaActual);
                    rutaActual = Ruta();
                    size_t a = linea.find('[')+1, b = linea.find(']');
                    rutaActual.id = std::stoi(linea.substr(a, b-a));
                    rutaActual.nombre = linea.substr(b+2);
                    enRuta = true;
                }
                else if (enRuta && linea.find("->") != std::string::npos) {
                    // formato: "Nodo X -[AY]-> Nodo Z  t=T"
                    std::istringstream ss(linea);
                    std::string tmp; Conexion c;
                    ss >> tmp >> c.nodoInicial;          // "Nodo" X
                    ss >> tmp;                            // "-[A10]->"
                    size_t p = tmp.find('[')+2, q = tmp.find(']');
                    c.aristaConexion = std::stoi(tmp.substr(p, q-p));
                    ss >> tmp >> c.nodoFinal;             // "Nodo" Z
                    ss >> tmp;                            // "t=1.5"
                    c.tiempo = std::stod(tmp.substr(2));
                    rutaActual.conexiones.push_back(c);
                }
            }
        } catch (...) {
            std::cout << "⚠ Línea ignorada: " << linea << "\n";
        }
    }
    if (enRuta) g.rutas.push_back(rutaActual);

    std::cout << " TXT leído: " << g.nodos.size() << " nodos, "
              << g.aristas.size() << " aristas, " << g.rutas.size() << " rutas.\n";
    return g;
}

// ── Exportadores (reusar los del grafo.cpp) ──

void exportCSV(const Grafo& g, const std::string& arch = "grafo.csv") {
    std::ofstream f(arch);
    f << "### NODOS\nid,nombre\n";
    for (auto& n : g.nodos) f << n.id << "," << n.nombre << "\n";
    f << "\n### ARISTAS\nid,nombre\n";
    for (auto& a : g.aristas) f << a.id << "," << a.nombre << "\n";
    f << "\n### RUTAS\nrutaId,rutaNombre,nodoInicial,nodoFinal,aristaConexion,tiempo\n";
    for (auto& r : g.rutas)
        for (auto& c : r.conexiones)
            f << r.id<<","<<r.nombre<<","<<c.nodoInicial<<","<<c.nodoFinal<<","<<c.aristaConexion<<","<<c.tiempo<<"\n";
    std::cout << " Guardado: " << arch << "\n";
}

void exportJSON(const Grafo& g, const std::string& arch = "grafo.json") {
    std::ofstream f(arch);
    auto js = [](const std::string& s){ return "\""+s+"\""; };
    f << "{\n  \"nodos\": [\n";
    for (size_t i=0;i<g.nodos.size();i++)
        f<<"    {\"id\":"<<g.nodos[i].id<<",\"nombre\":"<<js(g.nodos[i].nombre)<<"}"<<(i+1<g.nodos.size()?",":"")<<"\n";
    f << "  ],\n  \"aristas\": [\n";
    for (size_t i=0;i<g.aristas.size();i++)
        f<<"    {\"id\":"<<g.aristas[i].id<<",\"nombre\":"<<js(g.aristas[i].nombre)<<"}"<<(i+1<g.aristas.size()?",":"")<<"\n";
    f << "  ],\n  \"rutas\": [\n";
    for (size_t ri=0;ri<g.rutas.size();ri++) {
        auto& r=g.rutas[ri];
        f<<"    {\"id\":"<<r.id<<",\"nombre\":"<<js(r.nombre)<<",\"conexiones\":[\n";
        for (size_t ci=0;ci<r.conexiones.size();ci++) {
            auto& c=r.conexiones[ci];
            f<<"      {\"nodoInicial\":"<<c.nodoInicial<<",\"nodoFinal\":"<<c.nodoFinal
             <<",\"aristaConexion\":"<<c.aristaConexion<<",\"tiempo\":"<<c.tiempo<<"}"
             <<(ci+1<r.conexiones.size()?",":"")<<"\n";
        }
        f<<"    ]}"<<(ri+1<g.rutas.size()?",":"")<<"\n";
    }
    f << "  ]\n}\n";
    std::cout << " Guardado: " << arch << "\n";
}

void exportXML(const Grafo& g, const std::string& arch = "grafo.xml") {
    std::ofstream f(arch);
    f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<grafo>\n  <nodos>\n";
    for (auto& n : g.nodos)
        f<<"    <nodo id=\""<<n.id<<"\"><nombre>"<<n.nombre<<"</nombre></nodo>\n";
    f << "  </nodos>\n  <aristas>\n";
    for (auto& a : g.aristas)
        f<<"    <arista id=\""<<a.id<<"\"><nombre>"<<a.nombre<<"</nombre></arista>\n";
    f << "  </aristas>\n  <rutas>\n";
    for (auto& r : g.rutas) {
        f<<"    <ruta id=\""<<r.id<<"\"><nombre>"<<r.nombre<<"</nombre>\n      <conexiones>\n";
        for (auto& c : r.conexiones)
            f<<"        <conexionNodo2Nodo><nodoInicial>"<<c.nodoInicial<<"</nodoInicial>"
             <<"<nodoFinal>"<<c.nodoFinal<<"</nodoFinal><aristaConexion>"<<c.aristaConexion
             <<"</aristaConexion></conexionNodo2Nodo>\n";
        f<<"      </conexiones>\n    </ruta>\n";
    }
    f << "  </rutas>\n</grafo>\n";
    std::cout << " Guardado: " << arch << "\n";
}

void exportTXT(const Grafo& g, const std::string& arch = "grafo.txt") {
    std::ofstream f(arch);
    f << "=== NODOS ===\n";
    for (auto& n : g.nodos) f<<"  ["<<n.id<<"] "<<n.nombre<<"\n";
    f << "\n=== ARISTAS ===\n";
    for (auto& a : g.aristas) f<<"  ["<<a.id<<"] "<<a.nombre<<"\n";
    f << "\n=== RUTAS ===\n";
    for (auto& r : g.rutas) {
        f<<"  Ruta ["<<r.id<<"] "<<r.nombre<<"\n";
        for (auto& c : r.conexiones)
            f<<"    Nodo "<<c.nodoInicial<<" -[A"<<c.aristaConexion<<"]-> Nodo "<<c.nodoFinal;
    }
    std::cout << " Guardado: " << arch << "\n";
}

// ── Edición ──────────────────────────────────

void editarNodo(Grafo& g) {
    int id; std::cout << "ID nodo: "; std::cin >> id; std::cin.ignore();
    for (auto& n : g.nodos) {
        if (n.id == id) {
            std::cout << "Nuevo nombre [" << n.nombre << "]: ";
            std::getline(std::cin, n.nombre);
            std::cout << " Actualizado.\n"; return;
        }
    }
    std::cout << " No encontrado.\n";
}

void editarArista(Grafo& g) {
    int id; std::cout << "ID arista: "; std::cin >> id; std::cin.ignore();
    for (auto& a : g.aristas) {
        if (a.id == id) {
            std::cout << "Nuevo nombre [" << a.nombre << "]: ";
            std::getline(std::cin, a.nombre);
            std::cout << " Actualizado.\n"; return;
        }
    }
    std::cout << " No encontrada.\n";
}

void editarRuta(Grafo& g) {
    int id; std::cout << "ID ruta: "; std::cin >> id; std::cin.ignore();
    for (auto& r : g.rutas) {
        if (r.id == id) {
            std::cout << "Nuevo nombre [" << r.nombre << "]: ";
            std::getline(std::cin, r.nombre);
            std::cout << "¿Editar conexiones? (s/n): ";
            char ch; std::cin >> ch; std::cin.ignore();
            if (ch == 's' || ch == 'S') {
                r.conexiones.clear();
                int n; std::cout << "# conexiones: "; std::cin >> n;
                for (int i = 0; i < n; i++) {
                    Conexion c;
                    std::cout << "  nodoInicial nodoFinal aristaConexion tiempo: ";
                    std::cin >> c.nodoInicial >> c.nodoFinal >> c.aristaConexion >> c.tiempo;
                    r.conexiones.push_back(c);
                }
                std::cin.ignore();
            }
            std::cout << " Actualizada.\n"; return;
        }
    }
    std::cout << " No encontrada.\n";
}

void eliminar(Grafo& g) {
    std::cout << "Eliminar: 1.Nodo  2.Arista  3.Ruta\n> ";
    int t; std::cin >> t; std::cin.ignore();
    int id; std::cout << "ID: "; std::cin >> id; std::cin.ignore();
    if (t == 1) {
        for (auto it = g.nodos.begin(); it != g.nodos.end(); ++it)
            if (it->id == id) { g.nodos.erase(it); std::cout << " Nodo eliminado.\n"; return; }
    } else if (t == 2) {
        for (auto it = g.aristas.begin(); it != g.aristas.end(); ++it)
            if (it->id == id) { g.aristas.erase(it); std::cout << " Arista eliminada.\n"; return; }
    } else if (t == 3) {
        for (auto it = g.rutas.begin(); it != g.rutas.end(); ++it)
            if (it->id == id) { g.rutas.erase(it); std::cout << " Ruta eliminada.\n"; return; }
    }
    std::cout << " No encontrado.\n";
}

void verGrafo(const Grafo& g) {
    std::cout << "\nNodos (" << g.nodos.size() << "):\n";
    for (auto& n : g.nodos) std::cout << "  [" << n.id << "] " << n.nombre << "\n";
    std::cout << "Aristas (" << g.aristas.size() << "):\n";
    for (auto& a : g.aristas) std::cout << "  [" << a.id << "] " << a.nombre << "\n";
    std::cout << "Rutas (" << g.rutas.size() << "):\n";
    for (auto& r : g.rutas) {
        std::cout << "  Ruta [" << r.id << "] " << r.nombre << "\n";
        int i = 1;
        for (auto& c : r.conexiones)
            std::cout << "    " << i++ << ". Nodo " << c.nodoInicial
                      << " -[A" << c.aristaConexion << "]-> Nodo " << c.nodoFinal;
    }
}

// ── Main ─────────────────────────────────────

int main() {
    Grafo g;
    int op;
    do {
        std::cout << "\n--- Leer ---\n";
        std::cout << "1. CSV"<<std::endl;
        std::cout << "2. JSON"<<std::endl;
        std::cout << "3. XML"<<std::endl;
        std::cout << "4.TXT"<<std::endl;
        std::cout << "--- VER / EDITAR ---\n";
        std::cout << "5. Ver"<<std::endl;
        std::cout << "6. Editar nodo"<<std::endl;
        std::cout << "7. Editar arista"<<std::endl;
        std::cout << "8. Editar ruta"<<std::endl;
        std::cout << "9. Eliminar"<<std::endl;
        std::cout << "--- GUARDAR ---\n";
        std::cout << "10. CSV"<<std::endl;
        std::cout << "11. JSON"<<std::endl;
        std::cout << "12. XML"<<std::endl;
        std::cout << "13. TXT"<<std::endl;
        std::cout << "0.Salir" << std::endl;
        std::cout << "Opcion: ";

        std::cin >> op; std::cin.ignore();

        if (op == 1) {
            std::string arch; std::cout << "Archivo [grafo.csv]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.csv";
            g = leerCSV(arch);
        }
        else if (op == 2) {
            std::string arch; std::cout << "Archivo [grafo.json]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.json";
            g = leerJSON(arch);
        }
        else if (op == 3) {
            std::string arch; std::cout << "Archivo [grafo.xml]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.xml";
            g = leerXML(arch);
        }
        else if (op == 4) {
            std::string arch; std::cout << "Archivo [grafo.txt]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.txt";
            g = leerTXT(arch);
        }
        else if (op == 5)  verGrafo(g);
        else if (op == 6)  editarNodo(g);
        else if (op == 7)  editarArista(g);
        else if (op == 8)  editarRuta(g);
        else if (op == 9)  eliminar(g);
        else if (op == 10) {
            std::string arch; std::cout << "Guardar como [grafo.csv]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.csv";
            exportCSV(g, arch);
        }
        else if (op == 11) {
            std::string arch; std::cout << "Guardar como [grafo.json]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.json";
            exportJSON(g, arch);
        }
        else if (op == 12) {
            std::string arch; std::cout << "Guardar como [grafo.xml]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.xml";
            exportXML(g, arch);
        }
        else if (op == 13) {
            std::string arch; std::cout << "Guardar como [grafo.txt]: ";
            std::getline(std::cin, arch); if (arch.empty()) arch = "grafo.txt";
            exportTXT(g, arch);
        }
    } while (op != 0);
}
