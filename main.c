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


    nodoArbol*raiz=inicArbol();

    raiz= insertarNodoArbol(raiz,crearNodoArbol(crearUnMiembro()));

    nodoArbol*aux=buscarNodoArbol(raiz,1);

    mostrarArbolInorden(aux);

    printf("\Benvindo a la Biblotequiña do BookMaze\n");

    char respuesta[MAX_DIM];
    char accion[MAX_DIM];
    int operador;

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


    return 0;
}

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


void menuDeAccionesPrincipales()
{
    printf("Por favor, seleccione que accion desea relizar");
    printf("[1] Gestionar Libros\n");
    printf("[2] Gestionar Usuarios\n");
}


void menuGestionarLibros()
{
    printf("Selecciones una opcion\n");

    printf("[1] Ingresar Nuevo Libro \n");
    printf("[2] Buscar libros\n");
    printf("[3] Prestar Libros\n");
    printf("[4] Devolver Libros\n");
    printf("[5] Reservar Libros\n");
    printf("[6] Actualizar Libro \n");
    printf("[7] Eliminar Libro\n");
    printf("[8] Modificar condiciones de prestamo\n");

}

void menuBuscarLibros()
{

    printf("Seleccione una opción\n");

    printf("[1] Buscar por Titulo \n");
    printf("[2] Buscar por Autor \n");
    printf("[3] Buscar por Genero \n");
    printf("[4] Buscar Palabra Clave \n");

}

void menuActualizarLibros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Actualizar Nombre \n");
    printf("[2] Actualizar Genero\n");
    printf("[3] Actualizar Autor \n");
    printf("[4] Actualizar Descripcion\n");
    printf("[5] Actualizar Estado"); // Activo o inactivo- No permitir poner que este prestado.
}

void menuGestionarMiembros()
{

    printf("Seleccione una opcion\n");


    printf("[1] Registrar Miembros \n");
    printf("[2] Buscar Miembros \n");
    printf("[3] Calcular Multas \n");
    printf("[4] Generar Infomres  \n");
}

void menuMostrarMiembros(){

printf("Seleccione una opicon\n");

    printf("[1] Buscar Por Nombre\n");
    printf("[2] Buscar Por Id\n");
    printf("[3] Buscar Alquileres\n");
    printf("[4] Buscar por Saldo\n ");
    printf("[5] Buscar por Limite de prestamos\n");
}


*/
