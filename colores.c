#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
// Funci�n para imprimir un mensaje en rojo
void imprimirMensajeRojo(const char *mensaje) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("%s\n", mensaje);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void imprimirMensajeVerde(const char *mensaje) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("%s\n", mensaje);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void imprimirMensajeMarronOscuro(const char *mensaje) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Configurar un tono oscuro de marr�n (aproximaci�n)
    int colorMarronOscuro = 0x6;  // Este valor puede variar seg�n tu configuraci�n

    SetConsoleTextAttribute(hConsole, colorMarronOscuro);
    printf("%s\n", mensaje);

    // Restablecer el color a los valores predeterminados
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void imprimirMensajeVioleta(const char *mensaje) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Configurar un tono de violeta (aproximaci�n)
    int colorVioleta = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;

    SetConsoleTextAttribute(hConsole, colorVioleta);
    printf("%s\n", mensaje);

    // Restablecer el color a los valores predeterminados
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
