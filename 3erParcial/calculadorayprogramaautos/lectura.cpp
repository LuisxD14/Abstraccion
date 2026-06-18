#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

#include "funciones.cpp"


void abrirArchivo(string nombreArchivo){

#ifdef _WIN32

    string comando = "start " + nombreArchivo;

#elif __linux__

    string comando = "xdg-open " + nombreArchivo;

#else

    string comando = nombreArchivo;

#endif

    system(comando.c_str());
}


int main(){

    int tipoArchivo;
    int ejercicio;

    cout << "========================\n";
    cout << "TIPO DE ARCHIVO\n";
    cout << "========================\n";

    cout << "1. TXT\n";
    cout << "2. CSV\n";
    cout << "3. XML\n";
    cout << "4. JSON\n";

    cout << "\nSeleccione: ";
    cin >> tipoArchivo;

    string nombreArchivo;

    switch(tipoArchivo){

        case 1:
            nombreArchivo = "datos.txt";
            break;

        case 2:
            nombreArchivo = "datos.csv";
            break;

        case 3:
            nombreArchivo = "datos.xml";
            break;

        case 4:
            nombreArchivo = "datos.json";
            break;

        default:
            cout << "Opcion invalida";
            return 0;
    }

    cout << "\n========================\n";
    cout << "MENU DE EJERCICIOS\n";
    cout << "========================\n";

    cout << "1. Hola Mundo\n";
    cout << "2. Personas y Autos\n";
    cout << "3. Factorial\n";
    cout << "4. Calculadora\n";

    cout << "\nSeleccione: ";
    cin >> ejercicio;

    ofstream archivo(nombreArchivo);

    if(!archivo){

        cout << "Error al crear archivo";
        return 0;
    }


    if(ejercicio == 1){

        switch(tipoArchivo){

            case 1:
                archivo << reporteHolaMundoTXT();
                break;

            case 2:
                archivo << reporteHolaMundoCSV();
                break;

            case 3:
                archivo << reporteHolaMundoXML();
                break;

            case 4:
                archivo << reporteHolaMundoJSON();
                break;
        }
    }


    else if(ejercicio == 2){

        Persona *personas;
        Auto *autos;

        int cantPersonas;
        int cantAutos;

        capturarPersonasAutos(
            personas,
            autos,
            cantPersonas,
            cantAutos
        );

        switch(tipoArchivo){

            case 1:

                archivo << reportePersonasAutosTXT(
                    personas,
                    autos,
                    cantPersonas,
                    cantAutos
                );

                break;

            case 2:

                archivo << reportePersonasAutosCSV(
                    personas,
                    autos,
                    cantPersonas,
                    cantAutos
                );

                break;

            case 3:

                archivo << reportePersonasAutosXML(
                    personas,
                    autos,
                    cantPersonas,
                    cantAutos
                );

                break;

            case 4:

                archivo << reportePersonasAutosJSON(
                    personas,
                    autos,
                    cantPersonas,
                    cantAutos
                );

                break;
        }

        delete[] personas;
        delete[] autos;
    }


    else if(ejercicio == 3){

        int numero;

        cout << "\nNumero: ";
        cin >> numero;

        switch(tipoArchivo){

            case 1:
                archivo << reporteFactorialTXT(numero);
                break;

            case 2:
                archivo << reporteFactorialCSV(numero);
                break;

            case 3:
                archivo << reporteFactorialXML(numero);
                break;

            case 4:
                archivo << reporteFactorialJSON(numero);
                break;
        }
    }


    else if(ejercicio == 4){

        Calculadora calc;

        int operacion;
        int tipoParametros;

        cout << "\n===== CALCULADORA =====\n";

        cout << "1. Suma\n";
        cout << "2. Resta\n";
        cout << "3. Multiplicacion\n";
        cout << "4. Division\n";
        cout << "5. Potencia\n";

        cout << "\nSeleccione: ";
        cin >> operacion;

        cout << "\n1. Sin parametros\n";
        cout << "2. Dos parametros\n";
        cout << "3. Tres parametros\n";

        cout << "\nSeleccione: ";
        cin >> tipoParametros;

        int a=0,b=0,c=0;
        int resultado=0;
        string nombreOperacion;

        if(tipoParametros >= 2){

            cout << "A: ";
            cin >> a;

            cout << "B: ";
            cin >> b;
        }

        if(tipoParametros == 3){

            cout << "C: ";
            cin >> c;
        }

        switch(operacion){

            case 1:

                nombreOperacion = "Suma";

                if(tipoParametros==1)
                    resultado = calc.suma();

                else if(tipoParametros==2)
                    resultado = calc.suma(a,b);

                else
                    resultado = calc.suma(a,b,c);

                break;

            case 2:

                nombreOperacion = "Resta";

                if(tipoParametros==1)
                    resultado = calc.resta();

                else if(tipoParametros==2)
                    resultado = calc.resta(a,b);

                else
                    resultado = calc.resta(a,b,c);

                break;

            case 3:

                nombreOperacion = "Multiplicacion";

                if(tipoParametros==1)
                    resultado = calc.multiplicacion();

                else if(tipoParametros==2)
                    resultado = calc.multiplicacion(a,b);

                else
                    resultado = calc.multiplicacion(a,b,c);

                break;

            case 4:

                nombreOperacion = "Division";

                if(tipoParametros==1)
                    resultado = calc.division();

                else if(tipoParametros==2)
                    resultado = calc.division(a,b);

                else
                    resultado = calc.division(a,b,c);

                break;

            case 5:

                nombreOperacion = "Potencia";

                if(tipoParametros==1)
                    resultado = calc.potencia();

                else if(tipoParametros==2)
                    resultado = calc.potencia(a,b);

                else
                    resultado = calc.potencia(a,b,c);

                break;
        }

        switch(tipoArchivo){

            case 1:
                archivo << reporteCalculadoraTXT(
                    nombreOperacion,
                    resultado
                );
                break;

            case 2:
                archivo << reporteCalculadoraCSV(
                    nombreOperacion,
                    resultado
                );
                break;

            case 3:
                archivo << reporteCalculadoraXML(
                    nombreOperacion,
                    resultado
                );
                break;

            case 4:
                archivo << reporteCalculadoraJSON(
                    nombreOperacion,
                    resultado
                );
                break;
        }
    }

    archivo.close();

    abrirArchivo(nombreArchivo);

    return 0;
}
