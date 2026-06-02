#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class Persona {

private:

    string nombre;
    string ap;
    string am;
    string genero;
    int edad;

public:

    Persona() {

        nombre = "";
        ap = "";
        am = "";
        genero = "";
        edad = 0;
    }

    void capturar() {

        cout << "\nNombre: ";
        cin >> nombre;

        cout << "Apellido paterno: ";
        cin >> ap;

        cout << "Apellido materno: ";
        cin >> am;

        cout << "Genero: ";
        cin >> genero;

        cout << "Edad: ";
        cin >> edad;
    }

    string getNombre() {
        return nombre;
    }

    string getAP() {
        return ap;
    }

    string getAM() {
        return am;
    }

    string getGenero() {
        return genero;
    }

    int getEdad() {
        return edad;
    }

    string mostrar() {

        stringstream ss;

        ss << nombre << " "
           << ap << " "
           << am << " | "
           << genero << " | "
           << edad;

        return ss.str();
    }
};


class Auto {

private:

    string marca;
    double precio;
    int anio;

public:

    Auto() {

        marca = "";
        precio = 0;
        anio = 0;
    }

    void capturar() {

        cout << "\nMarca: ";
        cin >> marca;

        cout << "Precio: ";
        cin >> precio;

        cout << "Anio: ";
        cin >> anio;
    }

    string getMarca() {
        return marca;
    }

    double getPrecio() {
        return precio;
    }

    int getAnio() {
        return anio;
    }

    string mostrar() {

        stringstream ss;

        ss << marca
           << " | "
           << precio
           << " | "
           << anio;

        return ss.str();
    }
};


string holaMundo() {

    return "Hola Mundo";
}


long factorial(int n) {

    if(n <= 1)
        return 1;

    return n * factorial(n - 1);
}

void capturarPersonasAutos(
    Persona *&personas,
    Auto *&autos,
    int &cantPersonas,
    int &cantAutos
) {

    cout << "\nCantidad de personas: ";
    cin >> cantPersonas;

    personas = new Persona[cantPersonas];

    for(int i = 0; i < cantPersonas; i++) {

        cout << "\nPERSONA "
             << i + 1
             << endl;

        personas[i].capturar();
    }

    cout << "\nCantidad de autos: ";
    cin >> cantAutos;

    autos = new Auto[cantAutos];

    for(int i = 0; i < cantAutos; i++) {

        cout << "\nAUTO "
             << i + 1
             << endl;

        autos[i].capturar();
    }
}



class Calculadora {

private:

    // Multiplicación por sumas recursivas
    int multRec(int a, int b) {

        if(b == 0)
            return 0;

        if(b == 1)
            return a;

        return a + multRec(a, b - 1);
    }

    // División por restas recursivas
    int divRec(int a, int b) {

        if(a < b)
            return 0;

        return 1 + divRec(a - b, b);
    }

    // Potencia por multiplicaciones recursivas
    int potRec(int base, int exp) {

        if(exp == 0)
            return 1;

        return base * potRec(base, exp - 1);
    }

public:

    //=========================
    // SUMA
    //=========================

    int suma() {

        return 0;
    }

    int suma(int a, int b) {

        return a + b;
    }

    int suma(int a, int b, int c) {

        return a + b + c;
    }


    int resta() {

        return 0;
    }

    int resta(int a, int b) {

        return a - b;
    }

    int resta(int a, int b, int c) {

        return a - b - c;
    }


    int multiplicacion() {

        return 0;
    }

    int multiplicacion(int a, int b) {

        return multRec(a, b);
    }

    int multiplicacion(int a, int b, int c) {

        return multRec(multRec(a, b), c);
    }

    //=========================
    // DIVISION
    //=========================

    int division() {

        return 0;
    }

    int division(int a, int b) {

        if(b == 0)
            return 0;

        return divRec(a, b);
    }

    int division(int a, int b, int c) {

        if(b == 0 || c == 0)
            return 0;

        return divRec(divRec(a, b), c);
    }


    int potencia() {

        return 1;
    }

    int potencia(int a, int b) {

        return potRec(a, b);
    }

    int potencia(int a, int b, int c) {

        return potRec(potRec(a, b), c);
    }
};


string reporteHolaMundoTXT() {

    return "Hola Mundo";
}

string reporteHolaMundoCSV() {

    stringstream ss;

    ss << "Mensaje\n";
    ss << "Hola Mundo";

    return ss.str();
}

string reporteHolaMundoXML() {

    stringstream ss;

    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    ss << "<mensaje>\n";
    ss << "    <texto>Hola Mundo</texto>\n";
    ss << "</mensaje>";

    return ss.str();
}

string reporteHolaMundoJSON() {

    stringstream ss;

    ss << "{\n";
    ss << "    \"mensaje\" : \"Hola Mundo\"\n";
    ss << "}";

    return ss.str();
}


string reporteFactorialTXT(int n) {

    stringstream ss;

    ss << "===== FACTORIAL =====\n\n";
    ss << "Numero: " << n << "\n";
    ss << "Resultado: " << factorial(n);

    return ss.str();
}

string reporteFactorialCSV(int n) {

    stringstream ss;

    ss << "Numero,Resultado\n";
    ss << n << "," << factorial(n);

    return ss.str();
}

string reporteFactorialXML(int n) {

    stringstream ss;

    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    ss << "<factorial>\n";
    ss << "    <numero>" << n << "</numero>\n";
    ss << "    <resultado>"
       << factorial(n)
       << "</resultado>\n";
    ss << "</factorial>";

    return ss.str();
}

string reporteFactorialJSON(int n) {

    stringstream ss;

    ss << "{\n";
    ss << "    \"numero\" : "
       << n
       << ",\n";

    ss << "    \"resultado\" : "
       << factorial(n)
       << "\n";

    ss << "}";

    return ss.str();
}

string reportePersonasAutosTXT(
    Persona personas[],
    Auto autos[],
    int cantPersonas,
    int cantAutos
){

    stringstream ss;

    ss << "===== PERSONAS =====\n\n";

    for(int i=0;i<cantPersonas;i++){

        ss << personas[i].mostrar()
           << "\n";
    }

    ss << "\n===== AUTOS =====\n\n";

    for(int i=0;i<cantAutos;i++){

        ss << autos[i].mostrar()
           << "\n";
    }

    return ss.str();
}


string reportePersonasAutosCSV(
    Persona personas[],
    Auto autos[],
    int cantPersonas,
    int cantAutos
){

    stringstream ss;

    ss << "Nombre,AP,AM,Genero,Edad\n";

    for(int i=0;i<cantPersonas;i++){

        ss << personas[i].getNombre() << ","
           << personas[i].getAP() << ","
           << personas[i].getAM() << ","
           << personas[i].getGenero() << ","
           << personas[i].getEdad()
           << "\n";
    }

    ss << "\n";

    ss << "Marca,Precio,Anio\n";

    for(int i=0;i<cantAutos;i++){

        ss << autos[i].getMarca() << ","
           << autos[i].getPrecio() << ","
           << autos[i].getAnio()
           << "\n";
    }

    return ss.str();
}


string reportePersonasAutosXML(
    Persona personas[],
    Auto autos[],
    int cantPersonas,
    int cantAutos
){

    stringstream ss;

    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    ss << "<datos>\n";

    ss << "    <personas>\n";

    for(int i=0;i<cantPersonas;i++){

        ss << "        <persona>\n";

        ss << "            <nombre>"
           << personas[i].getNombre()
           << "</nombre>\n";

        ss << "            <apellidoPaterno>"
           << personas[i].getAP()
           << "</apellidoPaterno>\n";

        ss << "            <apellidoMaterno>"
           << personas[i].getAM()
           << "</apellidoMaterno>\n";

        ss << "            <genero>"
           << personas[i].getGenero()
           << "</genero>\n";

        ss << "            <edad>"
           << personas[i].getEdad()
           << "</edad>\n";

        ss << "        </persona>\n";
    }

    ss << "    </personas>\n";

    ss << "    <autos>\n";

    for(int i=0;i<cantAutos;i++){

        ss << "        <auto>\n";

        ss << "            <marca>"
           << autos[i].getMarca()
           << "</marca>\n";

        ss << "            <precio>"
           << autos[i].getPrecio()
           << "</precio>\n";

        ss << "            <anio>"
           << autos[i].getAnio()
           << "</anio>\n";

        ss << "        </auto>\n";
    }

    ss << "    </autos>\n";

    ss << "</datos>";

    return ss.str();
}


string reportePersonasAutosJSON(
    Persona personas[],
    Auto autos[],
    int cantPersonas,
    int cantAutos
){

    stringstream ss;

    ss << "{\n";

    ss << "\"personas\" : [\n";

    for(int i=0;i<cantPersonas;i++){

        ss << "{\n";

        ss << "\"nombre\":\""
           << personas[i].getNombre()
           << "\",\n";

        ss << "\"apellidoPaterno\":\""
           << personas[i].getAP()
           << "\",\n";

        ss << "\"apellidoMaterno\":\""
           << personas[i].getAM()
           << "\",\n";

        ss << "\"genero\":\""
           << personas[i].getGenero()
           << "\",\n";

        ss << "\"edad\":"
           << personas[i].getEdad()
           << "\n";

        ss << "}";

        if(i < cantPersonas - 1)
            ss << ",";

        ss << "\n";
    }

    ss << "],\n";

    ss << "\"autos\" : [\n";

    for(int i=0;i<cantAutos;i++){

        ss << "{\n";

        ss << "\"marca\":\""
           << autos[i].getMarca()
           << "\",\n";

        ss << "\"precio\":"
           << autos[i].getPrecio()
           << ",\n";

        ss << "\"anio\":"
           << autos[i].getAnio()
           << "\n";

        ss << "}";

        if(i < cantAutos - 1)
            ss << ",";

        ss << "\n";
    }

    ss << "]\n";

    ss << "}";

    return ss.str();
}
//================================================
// CALCULADORA TXT
//================================================

string reporteCalculadoraTXT(
    string operacion,
    int resultado
){

    stringstream ss;

    ss << "===== CALCULADORA =====\n\n";
    ss << "Operacion: "
       << operacion
       << "\n";

    ss << "Resultado: "
       << resultado
       << "\n";

    return ss.str();
}

//================================================
// CALCULADORA CSV
//================================================

string reporteCalculadoraCSV(
    string operacion,
    int resultado
){

    stringstream ss;

    ss << "Operacion,Resultado\n";
    ss << operacion
       << ","
       << resultado;

    return ss.str();
}

/
// CALCULADORA XML

string reporteCalculadoraXML(
    string operacion,
    int resultado
){

    stringstream ss;

    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    ss << "<calculadora>\n";

    ss << "    <operacion>"
       << operacion
       << "</operacion>\n";

    ss << "    <resultado>"
       << resultado
       << "</resultado>\n";

    ss << "</calculadora>";

    return ss.str();
}



string reporteCalculadoraJSON(
    string operacion,
    int resultado
){

    stringstream ss;

    ss << "{\n";

    ss << "\"operacion\":\""
       << operacion
       << "\",\n";

    ss << "\"resultado\":"
       << resultado
       << "\n";

    ss << "}";

    return ss.str();
}
