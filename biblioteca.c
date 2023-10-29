#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"

//la biblioteca va a tener el arreglo de listas simples de los libros

void biblioteca()
{
    int opMenuPrin=0;
    char opContinuarMenuPrin;
    do
    {
        menuDeAccionesPrincipales();
        opMenuPrin=preguntarDatoEntero();
        switch(opMenuPrin)
        {
        case 1:
            menuLibros();
            break;
        case 2:
            menuMiembros();
            break;
        case 3:
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        printf("Desea volver al menu principal? s/n: ");
        fflush(stdin);
        scanf("%c",&opContinuarMenuPrin);
        limpiarPantalla();
    }
    while(opMenuPrin=='s' || opMenuPrin=='S');






}

int preguntarDatoEntero()
{
    int dato=0;
    printf("Ingrese un dato: ");
    fflush(stdin);
    scanf("%i",&dato);
    return dato;
}

void limpiarPantalla()
{
    system("cls");
}

void menuDeAccionesPrincipales()
{
    printf("Por favor, seleccione que accion desea relizar \n");
    printf("[1] Gestionar Libros\n");
    printf("[2] Gestionar Miembros\n");
    printf("[3] Gestionar Prestamos \n");
    puts("-------------------------------------");
}

void opcionesMenuGestionarLibros()
{
    printf("\nSeleccione una opcion\n");

    printf("[1] Ingresar Nuevo Libro \n");
    printf("[2] Buscar libros\n");
    printf("[3] Prestar Libros\n");
    printf("[4] Devolver Libros\n");
    printf("[5] Reservar Libros\n");
    printf("[6] Actualizar Libro \n");
    printf("[7] Eliminar Libro\n");
    puts("---------------------------------------------------");
}

void menuLibros()
{
    int opSw=0;
    char opCont;

    do
    {

        opcionesMenuGestionarLibros();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1: //crear un libro nuevo

            break;
        case 2: //menu buscar libro
            menuBuscarLibros();
            break;
        case 3: // prestar un libro

            break;
        case 4: // devolver un libro

            break;
        case 5: // reservar un libro
            break;
        case 6: // menu actualizar un libro
            break;
        case 7: // eliminar un libro
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        printf("Desea volver al menu de libros? s/n: ");
        fflush(stdin);
        scanf("%c",&opCont);
        limpiarPantalla();
    }
    while(opCont=='S' || opCont=='s');


}

void opcionesMenuActualizarLibros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Actualizar Nombre \n");
    printf("[2] Actualizar Genero\n");
    printf("[3] Actualizar Autor \n");
    printf("[4] Actualizar Descripcion\n");
    printf("[5] Actualizar Estado"); // Activo o inactivo- No permitir poner que este prestado.
    puts("------------------------------------");
}

void menuActualizarLibro()
{
    int opSw=0;
    char opCont;
    do
    {
        opcionesMenuActualizarLibros();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
        }

        printf("Desea seguir en el menu de actualizar libros? s/n: ");
        fflush(stdin);
        scanf("%c",&opCont);
        limpiarPantalla();
    }
    while(opCont == 's' || opCont=='S');
}

void opcionesMenuBuscarLibros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Buscar por Titulo \n");
    printf("[2] Buscar por Autor \n");
    printf("[3] Buscar por Genero \n");
    printf("[4] Buscar Palabra Clave \n");
    puts("-----------------------------------------");
}

void menuBuscarLibros()
{
    int opSw=0;
    char opCont;
    do
    {
        opcionesMenuBuscarLibros();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        printf("Desea seguir en el menu de buscar libros? s/n: ");
        fflush(stdin);
        scanf("%c",&opCont);
        limpiarPantalla();
    }
    while(opCont=='S' || opCont=='s');

}

void opcionesMenuMiembros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Registrar Miembros \n");
    printf("[2] Buscar Miembros \n");
    printf("[3] Calcular Multas \n");
    printf("[4] Generar Informes  \n");
    printf("[5] Modificar limite de prestamo a un miembro\n");
    puts("----------------------------------------------------");
}

void menuMiembros()
{
    int opSw=0;
    char opCont;

    do
    {
        opcionesMenuMiembros();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        printf("Desea seguir en el menu miembros? s/n: ");
        fflush(stdin);
        scanf("%c",&opCont);
        limpiarPantalla();
    }
    while(opCont == 's' || opCont=='S');

}


void menuBuscarMiembros()
{

    printf("Seleccione una opcion \n");

    printf("[1] Buscar Por Nombre\n");
    printf("[2] Buscar Por Id\n");
    printf("[3] Buscar Alquileres\n");
    printf("[4] Buscar por Saldo\n ");
    printf("[5] Buscar por Limite de prestamos\n");
    puts("------------------------------------------");
}



