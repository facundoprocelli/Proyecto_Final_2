#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaSimpleLibros.h"
#define MAX_DIM 26
#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"

///funciones estructura libro

stLibro crearUnLibro()
{
    stLibro aux;

    puts("--------------- Ingrese los datos del nuevo libro ----------------------");
    do
    {
        printf("Nombre: ");
        fflush(stdin);
        gets(&aux.nombreDeLibro);
    }
    while(validarDigitosEnStrings(aux.nombreDeLibro)== 1||validarRangoDeNombre(aux.nombreDeLibro)== 1);///reutilizo la funcion de validarDigitos y validarRangoNombre que hice en arboles

    printf("Genero: \n");
    validarGenero(aux.generoLibro);

    do
    {
        printf("Autor: ");
        fflush(stdin);
        gets(&aux.autorLibro);
    }
    while(validarDigitosEnStrings(aux.autorLibro)== 1||validarRangoDeNombre(aux.autorLibro)==1);
    aux.estado=1; // 0.dado de baja, 1.disponible, 2. prestado

    aux.idLibro=0; ///es necesario una funcion automatica

    inicFila(&aux.reservasLibro);

    aux.vecesPrestadoLibro=0;


    printf("Desripcion: ");
    fflush(stdin);
    gets(&aux.descripcionLibro);

    return aux;
}

//mostrar un libro
void mostrarUnLibro(stLibro aux)
{
    puts("--------------------LIBRO: ----------------");
    printf("ID Libro..............: %i \n",aux.idLibro);
    printf("Nombre................: %s \n",aux.nombreDeLibro);
    printf("Genero................: %s \n",aux.generoLibro);
    printf("Autor.................: %s \n",aux.autorLibro);
    printf("Estado................: %i \n",aux.estado);
    printf("Veces prestado........: %i \n",aux.vecesPrestadoLibro);
    printf("Descripcion...........: %s \n", aux.descripcionLibro);
    ///printf("",aux.reservasLibro); ///mostrar fila de reservas de este libro
    puts("---------------------------------------------");
}


/// lista simple de libros

nodoSimple*inicListaSimple()
{
    return NULL;
}

//mostrar toda la lista simple
void mostrarListaSimple(nodoSimple*listaSimple)
{
    while(listaSimple != NULL)
    {
        mostrarUnLibro(listaSimple->datoLibro);
        listaSimple=listaSimple->siguiente;
    }
}

//crear un nodo simple

nodoSimple*crearNodoSimple(stLibro aux)
{
    nodoSimple*nuevoNodo=(nodoSimple*)malloc(sizeof(nodoSimple));
    nuevoNodo->datoLibro=aux;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

//agregar al principio de la lista simple

nodoSimple*agregarAlPpioSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo)
{
    nuevoNodo->siguiente=listaSimple;
    return nuevoNodo;
}

//agregar al final de la lista simple

nodoSimple*agregarAlFinalSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo)
{
    if(listaSimple != NULL)
    {
        nodoSimple*seg=listaSimple;
        while(seg->siguiente != NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevoNodo;
    }
    else
    {
        listaSimple=nuevoNodo;
    }
    return listaSimple;
}



//verificar si existe el libro

int verificarSiExisteLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[])
{
    int flag=0;

    while(listaSimple != NULL && strcmpi(listaSimple->datoLibro.nombreDeLibro,nombreBuscar) != 0)
    {
        listaSimple=listaSimple->siguiente;
    }
    if(listaSimple == NULL)
    {
        flag=1;
    }
    return flag;
}

//funciones de buscar para retornar un nodo

nodoSimple*retornarNodoSimpleXid(nodoSimple*listaSimple,int idBuscar)
{
    nodoSimple*aux=NULL;
    while(listaSimple != NULL && listaSimple->datoLibro.idLibro != idBuscar)
    {
        listaSimple=listaSimple->siguiente;
    }
    if(listaSimple == NULL) // si llegue al final no encontre el dato
    {
        puts("Libro no encontrado");
    }
    else // si no es null entonces se corto el bucle porque encontre el dato
    {
        aux=listaSimple;
    }
    return aux;
}


nodoSimple* retornarNodosLibroXAutor(nodoSimple* listaSimple, char autorBuscar[])
{

    nodoSimple* aux = inicListaSimple();


    while (listaSimple != NULL)
    {

        if (strcmpi(listaSimple->datoLibro.autorLibro, autorBuscar) == 0)
        {

            nodoSimple* NN = crearNodoSimple(listaSimple->datoLibro);
            aux = agregarAlFinalSimple(aux, NN );
        }

        listaSimple = listaSimple->siguiente;
    }

    return aux;
}




nodoSimple* retornarNodosLibroXEstado(nodoSimple* listaSimple, int estado)
{

    nodoSimple* aux = inicListaSimple();


    while (listaSimple != NULL)
    {

        if (listaSimple->datoLibro.estado == estado)
        {
            nodoSimple* NN = crearNodoSimple(listaSimple->datoLibro);
            aux = agregarAlFinalSimple(aux, NN);

        }
        listaSimple = listaSimple->siguiente;
    }

    return aux;
}








//Funciones de modificar Libros

nodoSimple* actualizarLibro(nodoSimple* lista)
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
        /*
                printf("Ingrese el ID que desea bsucar");
                int idBuscado = preguntarDatoEntero();


                for(int i = 0; i < 5; i++)
                {

                    buscado = retornarLibroXid(arregloListas[i], idBuscado);

                }

                */


        switch(opSw)
        {
        case 1: //Actualizar Nombre
            lista = modificarNombreLibro(lista);
            break;
        case 2: //Actualizar Genero
            lista = modificarGeneroLibro(lista);
            break;
        case 3: // Actualizar Autor
            lista = modificarAutorLibro(lista);
            break;
        case 4: // Actualizar Descripción
            lista = modificarDescripcionLibro(lista);
            break;
        case 5:
                // Actualizar Estado
            lista = modificarEstadoLibro(lista);
            break;
        case 6:
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

    return lista ;
}




nodoSimple* modificarNombreLibro(nodoSimple* aux)
{

    do
    {
        printf("Ingrese el nuevo nombre ");
        printf("Nombre: ");
        fflush(stdin);
        gets(aux->datoLibro.nombreDeLibro);
    }
    while(validarDigitosEnStrings(aux->datoLibro.nombreDeLibro)== 1||validarRangoDeNombre(aux->datoLibro.nombreDeLibro)== 1);///reutilizo la funcion de validarDigitos y validarRangoNombre que hice en arboles


    return aux;
}


nodoSimple* modificarGeneroLibro(nodoSimple* aux)
{

    printf("Seleccione el nuevo Genero ");
    printf("Genero: \n");
    validarGenero(aux->datoLibro.generoLibro);

    return aux;
}


nodoSimple* modificarAutorLibro(nodoSimple* aux)
{

    do
    {
        printf("Ingrese el nuevo Autor ");
        printf("Autor: ");
        fflush(stdin);
        gets(aux->datoLibro.autorLibro);
    }
    while(validarDigitosEnStrings(aux->datoLibro.autorLibro)== 1||validarRangoDeNombre(aux->datoLibro.autorLibro)==1);

    return aux;
}


nodoSimple* modificarDescripcionLibro(nodoSimple* aux)
{


    printf("Desripcion: ");
    fflush(stdin);
    gets(aux->datoLibro.descripcionLibro);


    return aux;
}


nodoSimple* modificarEstadoLibro(nodoSimple* aux)
{


    char opSw[1];
    int op = 0;
    menuEstados();
    do
    {
        op = preguntarDatoEntero();
    }
    while (op != 0 && op != 1  );

        aux->datoLibro.estado = op;



    return aux;
}

void menuEstados()
{

    printf("Seleccione una opcion\n");
    printf("[0] Dar de Baja\n");
    printf("[1] Dar de Alta\n");

}

//funciones de buscar para retornar un libro

stLibro retornarLibroXid(nodoSimple*listaSimple,int idBuscar)
{
    stLibro aux;

    while(listaSimple != NULL && listaSimple->datoLibro.idLibro != idBuscar)
    {
        listaSimple=listaSimple->siguiente;
    }
    if(listaSimple != NULL) // si no es null entonces se corto el bucle porque encontre el dato
    {
        aux=listaSimple->datoLibro;
    }
    else // si llegue al final no encontre el dato
    {

        puts("Libro no encontrado");
    }
    return aux;
}

stLibro retornarLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[])
{
    stLibro aux;
    while(listaSimple != NULL && strcmpi(listaSimple->datoLibro.nombreDeLibro,nombreBuscar) != 0)
    {
        listaSimple= listaSimple->siguiente;
    }
    if(listaSimple != NULL)
    {
        aux=listaSimple->datoLibro;
    }
    else
    {
        puts("Libro no encontrado");
    }
    return aux;
}



stLibro retornarLibroXAutor(nodoSimple*listaSimple,char autorBuscar[])
{
    stLibro aux;
    while(listaSimple != NULL && strcmpi(listaSimple->datoLibro.autorLibro,autorBuscar) != 0)
    {
        listaSimple= listaSimple->siguiente;
    }
    if(listaSimple != NULL)
    {
        aux=listaSimple->datoLibro;
    }
    else
    {
        puts("Libro no encontrado");
    }
    return aux;
}




///validaciones


void validarGenero(char auxGenero[])
{
    char opSw[1];
    int flag = 0;
    int op;
    do
    {
        ///----------Se puede hacer en una funcion aparte----------------
        do
        {
            opcionesGenero();
            printf("Ingrese una opcion: ");
            fflush(stdin);
            scanf("%s", &opSw);
        }
        while (validarCaracteresEnEnteros(opSw) == 0);

        op = convertirStringsDeNumerosAEntero(opSw);

        switch(op)
        {
        case 1:
            strcpy(auxGenero,"Fantasia");
            flag = 1;
            break;
        case 2:
            strcpy(auxGenero,"Ciencia Ficcion");
            flag = 1;
            break;
        case 3:
            strcpy(auxGenero,"Romance");
            flag = 1;
            break;
        case 4:
            strcpy(auxGenero,"Terror");
            flag = 1;
            break;
        case 5:
            strcpy(auxGenero,"Comedia");
            flag = 1;
            break;
        default:
            printf("\nIngrese una opcion valida\n");
            flag = 0;
            break;


        }

    }

    while(flag == 0);

}

//Opciones del genero de un libro

void opcionesGenero()
{
    printf("[1]Fantasia\n");
    printf("[2]Ciencia Ficcion\n");
    printf("[3]Romance\n");
    printf("[4]Terror\n");
    printf("[5]Comedia\n");

}

// cargar un libro a un archivo

void cargarUnLibroAlArchivo(stLibro aux) //cuando se cree un nuevo libro se utiliza esta funcion
{
    FILE*buffer=fopen(ARCHIVO_LIBROS,"ab");
    if(buffer != NULL)
    {
        fwrite(&aux,sizeof(stLibro),1,buffer);
        fclose(buffer);
    }
    else
    {
        puts("Archivo vacio");
    }
}

void mostrarArchivoLibros()
{
    FILE*buffer=fopen(ARCHIVO_LIBROS,"rb");
    stLibro aux;
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stLibro),1,buffer)>0)
        {
            mostrarUnLibro(aux);
        }
        fclose(buffer);
    }
    else
    {
        puts("Archivo vacio");
    }
}

/// Esto es lo que debe ir en biblioteca para que este el switch en la parte correcta, faltan los cambios para que funicone bien
/*

void menuLibros(nodoSimple arregloListas[])
{
    int opSw=0;
    char opCont='s';
    int i = 0;
    stLibro aux;
    do
    {
        puts("---------------------------------------------------");
        opcionesMenuGestionarLibros();
        opSw=preguntarDatoEntero();
        //limpiarPantalla();
        switch(opSw)
        {
        case 1: //crear un libro nuevo
            aux = crearUnLibro();
            for (i = 0; i < 5; i++){

            if (strcmpi(aux.generoLibro, arregloListas[i].datoLibro.generoLibro) == 0){

                //arregloListas[i] = agregarAlFinalSimple(arregloListas[i], crearNodoSimple(aux));
                }
            }

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
            //arregloListas[i] =  actualizarLibro(arregloListas);
            break;
        case 7: // eliminar un libro
            break;
        case 8:
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

*/
