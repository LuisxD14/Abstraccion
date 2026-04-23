#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/* =========================================
   PROTOTIPOS DE FUNCIONES
   Le decimos a C qué funciones existen antes de usarlas
   ========================================= */
const char* seleccionarPalabra(const char* banco[], int cantidad);
void prepararPalabraOculta(char* oculta, int longitud);
bool verificarLetra(const char* secreta, char* oculta, char letra);
void jugar(const char* palabraSecreta);

/* =========================================
   FUNCIÓN PRINCIPAL (MAIN)
   ========================================= */
int main() {
    const char* bancoPalabras[] = {"programacion", "algoritmo", "puntero", "memoria", "compilador"};
    int numPalabras = sizeof(bancoPalabras) / sizeof(bancoPalabras[0]);
    
    srand(time(NULL)); 

    printf("¡Bienvenido al juego del Ahorcado con Funciones en C!\n");
    
    /* 1. Elegimos la palabra */
    const char* palabraElegida = seleccionarPalabra(bancoPalabras, numPalabras);
    
    /* 2. Iniciamos el juego con esa palabra */
    jugar(palabraElegida);

    return 0;
}

/* =========================================
   IMPLEMENTACIÓN DE FUNCIONES
   ========================================= */

/* Función que devuelve un puntero a la palabra elegida */
const char* seleccionarPalabra(const char* banco[], int cantidad) {
    return banco[rand() % cantidad];
}

/* Función que llena el arreglo con guiones bajos */
void prepararPalabraOculta(char* oculta, int longitud) {
    for (int i = 0; i < longitud; i++) {
        oculta[i] = '_';
    }
    oculta[longitud] = '\0'; /* No olvidar el carácter nulo */
}

/* Función que busca la letra. Retorna 'true' si acertó, 'false' si falló */
bool verificarLetra(const char* secreta, char* oculta, char letra) {
    bool acierto = false;
    int longitud = strlen(secreta);
    
    for (int i = 0; i < longitud; i++) {
        if (secreta[i] == letra) {
            oculta[i] = letra; /* Modificamos el arreglo original */
            acierto = true;
        }
    }
    return acierto;
}

/* Función que controla el ciclo de vidas y turnos */
void jugar(const char* palabraSecreta) {
    int longitud = strlen(palabraSecreta);
    char palabraOculta[50]; 
    
    prepararPalabraOculta(palabraOculta, longitud);

    int vidas = 6;
    bool adivinada = false;

    while (vidas > 0 && !adivinada) {
        printf("\nPalabra: %s\n", palabraOculta);
        printf("Vidas restantes: %d\n", vidas);
        printf("Ingresa una letra: ");
        
        char letraIngresada;
        scanf(" %c", &letraIngresada); 

        /* Llamamos a la función para verificar si la letra está */
        bool acertaste = verificarLetra(palabraSecreta, palabraOculta, letraIngresada);

        if (!acertaste) {
            printf("Letra incorrecta.\n");
            vidas--;
        } else {
            printf("¡Bien hecho!\n");
        }

        /* Comparamos si ya se adivinó la palabra completa */
        if (strcmp(palabraOculta, palabraSecreta) == 0) {
            adivinada = true;
        }
    }

    /* Resultados */
    if (adivinada) {
        printf("\n¡Felicidades! Adivinaste la palabra: %s\n", palabraSecreta);
    } else {
        printf("\n¡Fin del juego! Te quedaste sin vidas. La palabra era: %s\n", palabraSecreta);
    }
}