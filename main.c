#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arbolMiembros.h"
#include "filaReservas.h"
#include "biblioteca.h"
#include "listaDobleReservas.h"
#include "listaSimpleLibros.h"

#define maxOpcionesMain 2
#define minOpcionesMain 1


int main()
{


    char archivoMiembros[MAX_DIM]="archivoMiembros";
    char archivoPrestamos[MAX_DIM]="archivoPrestamos";
    char archivoLibros[MAX_DIM]="archivoLibros";

    //printf("\Benvindo a la Biblotequiña do BookMaze\n");
    //biblioteca();

    nodoSimple*listaSimple=inicListaSimple();
    listaSimple=agregarAlPpioSimple(listaSimple,crearNodoSimple(crearUnLibro()));


    return 0;
}

//    char respuesta[MAX_DIM];
//    char accion[MAX_DIM];
//    int operador;

    /// aca esta el while que va a hacer que se ejecuten las funciones
    /// que llaman al resto de cosas en un futuro
/*
    do
    {

        menuDeAccionesPrincipales();
        fflush(stdin);
        gets(accion);

        operador = validacionNumeros(accion, minOpcionesMain, maxOpcionesMain)

        switch(operador);
        {

        case 1:
            menuGestionarLibros(); // Aca deberiamos llamar posteriormente a una funcion que gestione libros
            break;

        case 2:
            menuGestionarMiembros(); // Aca deberias llamar a una funcionq ue gestione los usuarios
            break;

        }


        menuRepetirAcciones();
        fflush(stdin);
        gets(respuesta);

        //Hay que hacer la validación de string de este 'si', para que funciones como correpsonde

    }
    while (strcmpi(respuesta, "si") == 0);



*/
/// Aca esta la validación de los numeros y todos los menues necesarios
/*

int validacionNumeros(char str[100], int min, int max)
{
    char *endptr;
    long num = strtol(str, &endptr, 10);
    int valido =0;
    int conv;

    conv = (int)num;
    if (*endptr == '\0' && conv >= min && conv <= max )
    {
        valido = 1;
    }
    else
    {
        while (valido == 0)
        {
            printf("Ingrese una opcion valida\n OPCION:");
            gets(str);
            num = strtol(str, &endptr, 10);
            conv = (int)num;
            if (*endptr == '\0' && conv >= min && conv <= max)
            {
                valido = 1;

            }
        }
    }
    conv = (int)num;
    return conv;
}

void menuRepetirAcciones()
{

    printf("Desea seguir?\n");
    printf("'si' = Seguir\n");
    printf("'no' = Salir\n";

}







*/
