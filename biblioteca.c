#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"


#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"



//la biblioteca va a tener el arreglo de listas simples de los libros


///funciones generales

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

int convertirStringsDeNumerosAEntero(char aux[])
{
    return atoi(aux);
}

///menues
void biblioteca()
{
    estanteria arregloEstanterias[5];
    inicEstanterias(arregloEstanterias); /// a la iniciacion tmb deberiamos agregar las reservas de los libros pero todavia no lo tenemos
    nodoArbol * arbolMiembros=inicArbol();

    arbolMiembros=archivoAlArbol(arbolMiembros);
    archivoAEstanteria(arregloEstanterias); /// o capaz aca podemos leer el archivo de reservas tmb


    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        menuDeAccionesPrincipales();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            menuLibros(arregloEstanterias);
            break;
        case 2:
            menuMiembros();
            break;
        case 3:
            break;
        case 4:
            puts("Adios");
            opContinuarMenuPrin = 'n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');

    arbolAlArchivo(arbolMiembros);
    librosAlArchivo(arregloEstanterias);
    ///prestamos al archivo

}
void menuDeAccionesPrincipales()
{
    printf("Por favor, seleccione que accion desea realizar \n");
    printf("[1] Gestionar Libros\n");
    printf("[2] Gestionar Miembros\n");
    printf("[3] Gestionar Prestamos \n");
    printf("[4] Finalizar programa \n");
    puts("-------------------------------------");
}

void opcionesMenuGestionarLibros()
{
    printf("Seleccione una opcion\n");

    printf("[1] Ingresar Nuevo Libro \n");
    printf("[2] Buscar libros\n");
    printf("[3] Prestar Libro\n");
    printf("[4] Devolver Libro\n");
    printf("[5] Reservar Libro\n");
    printf("[6] Actualizar Libro \n");
    printf("[7] Eliminar Libro\n");
    printf("[8] Mostrar todos los libros \n");
    printf("[9] Volver al menu principal \n");
    puts("---------------------------------------------------");
}

void menuLibros(estanteria arregloEstanterias[])
{
    int opSw=0;
    char opCont='s';
    stLibro aux;


    do
    {
        puts("---------------------------------------------------");
        opcionesMenuGestionarLibros();
        opSw=preguntarDatoEntero();
        limpiarPantalla();
        switch(opSw)
        {
        case 1: //crear un libro nuevo
            aux=crearUnLibro(arregloEstanterias);
            cargarEstanteriaOrdenada(arregloEstanterias,crearNodoSimple(aux));
            mostrarUnLibro(aux);
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
            actualizarLibro(arregloEstanterias);
            break;
        case 7: // eliminar un libro
            break;
        case 8:
            mostrarTodasLasEstanterias(arregloEstanterias);
            break;
        case 9:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont != 'n');


}

void opcionesMenuActualizarLibros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Actualizar Nombre \n");
    printf("[2] Actualizar Genero\n");
    printf("[3] Actualizar Autor \n");
    printf("[4] Actualizar Descripcion\n");
    printf("[5] Actualizar Estado \n"); // Activo o inactivo- No permitir poner que este prestado.
    printf("[6] Actualizar Cantiadad de Copias\n");
    printf("[7] Volver al menu de libros \n");
    puts("------------------------------------");
}


void actualizarLibro(estanteria arregloListas[])
{
    int opSw=0;
    char opCont='s';
    nodoSimple* buscado = inicListaSimple();
    do
    {
        puts("---------------------------------------------------");
        opcionesMenuActualizarLibros();

        opSw = preguntarDatoEntero();

        limpiarPantalla();

        printf("Ingrese el ID que desea buscar");
        int idBuscado = preguntarDatoEntero();

        /*
                        for(int i = 0; i < 5; i++)
                        {

                            buscado = retornarLibroXid(arregloListas[i]->listaLibros, idBuscado);

                            if(buscado != NULL){
                                break;
                            }

                        }
        */
        switch(opSw)
        {
        case 1: //Actualizar Nombre
            buscado = modificarNombreLibro(buscado);
            break;
        case 2: //Actualizar Genero
            buscado = modificarGeneroLibro(buscado);
            break;
        case 3: // Actualizar Autor
            buscado = modificarAutorLibro(buscado);
            break;
        case 4: // Actualizar Descripción
            buscado = modificarDescripcionLibro(buscado);
            break;
        case 5:
            // Actualizar Estado
            buscado = modificarEstadoLibro(buscado);
            break;
        case 6:
            // Actualizar Cantidad de Copias
            buscado = modificarCantidadDeCopias(buscado);
        case 7:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        limpiarPantalla();
    }
    while(opCont != 'n');
}

void opcionesMenuBuscarLibros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Buscar por Titulo \n");
    printf("[2] Buscar por Autor \n");
    printf("[3] Buscar por Genero \n");
    printf("[4] Buscar Palabra Clave \n");
    printf("[5] Volver al menu de libros \n");
    puts("-----------------------------------------");
}

void menuBuscarLibros()
{
    int opSw=0;
    char opCont='s';
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
        case 5:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont!='n');

}

void opcionesMenuMiembros()
{

    puts("----------------------------------------------------");
    printf("Seleccione una opcion\n");
    printf("[1] Registrar Miembros \n");
    printf("[2] Buscar Miembros \n");
    printf("[3] Calcular Multas \n");
    printf("[4] Generar Informes  \n");
    printf("[5] Modificar limite de prestamo a un miembro\n");
    printf("[6] Volver al menu principal \n");
    puts("----------------------------------------------------");
}

void menuMiembros()
{
    int opSw=0;
    char opCont='s';

    do
    {
        opcionesMenuMiembros();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1:
            break;
        case 2:
            menuBuscarMiembros();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont != 'n');

}


void opcionesMenuBuscarMiembros()
{

    puts("------------------------------------------");
    printf("Seleccione una opcion \n");
    printf("[1] Buscar Por Nombre\n");
    printf("[2] Buscar Por Id\n");
    printf("[3] Buscar Alquileres\n");
    printf("[4] Buscar por Saldo\n ");
    printf("[5] Buscar por Limite de prestamos\n");
    printf("[6] Volver al menu de miembros \n");
    puts("------------------------------------------");
}

void menuBuscarMiembros()
{
    int opSw=0;
    char opCont='s';
    opcionesMenuBuscarMiembros();
    opSw=preguntarDatoEntero();
    do
    {

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
        case 6:
            limpiarPantalla();
            opCont='n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }

    }
    while(opCont != 'n');

}


/// funciones estanteria

void inicEstanterias(estanteria arregloEstanterias[])
{
    char*generos[]= {"Fantasia","Ciencia Ficcion","Romance","Terror","Aventura"};
    int dim=5;
    for(int i=0; i < dim; i++)
    {
        arregloEstanterias[i].listaLibro=inicListaSimple();
        strcpy(arregloEstanterias[i].generoEstanteria,generos[i]);
    }
}

void mostrarTodasLasEstanterias(estanteria arregloEstanterias[])
{
    int dim=5;
    for(int i=0; i < dim; i++)
    {
        mostrarUnaEstanteria(arregloEstanterias[i]);
    }
}

void mostrarUnaEstanteria(estanteria unaEstanteriaSola)
{
    puts("\n-----------------------------------------");
    printf("\nGENERO DE LA ESTANTERIA: %s \n",unaEstanteriaSola.generoEstanteria);

    if(unaEstanteriaSola.listaLibro != NULL)
    {
        mostrarListaSimple(unaEstanteriaSola.listaLibro);

    }
    else
    {
        puts("Estanteria vacia :(");
    }
}

void cargarEstanteriaOrdenada(estanteria arregloEstanterias[],nodoSimple*nuevoNodo)
{
    // si el genero actual que esta en X estanteria es igual al genero del libro del nuevo nodo,
    // se va a agregar al final en el genero correspondiente

    if(strcmp(arregloEstanterias[0].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[0].listaLibro=agregarAlFinalSimple(arregloEstanterias[0].listaLibro,nuevoNodo);

    }
    else if(strcmp(arregloEstanterias[1].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[1].listaLibro=agregarAlFinalSimple(arregloEstanterias[1].listaLibro,nuevoNodo);

    }
    else if(strcmp(arregloEstanterias[2].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[2].listaLibro=agregarAlFinalSimple(arregloEstanterias[2].listaLibro,nuevoNodo);

    }
    else if(strcmp(arregloEstanterias[3].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[3].listaLibro=agregarAlFinalSimple(arregloEstanterias[3].listaLibro,nuevoNodo);

    }
    else
    {
        arregloEstanterias[4].listaLibro=agregarAlFinalSimple(arregloEstanterias[4].listaLibro,nuevoNodo);

    }

}
