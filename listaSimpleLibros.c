#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaSimpleLibros.h"


///crear un libro

stLibro crearUnLibro() ///LEO VALIDATE TODA ESTAA (funcion)
{
    stLibro aux;

    puts("--------------- Ingrese los datos del nuevo libro ----------------------");
    printf("Nombre: ");
    fflush(stdin);
    gets(&aux.nombreDeLibro);

    printf("Genero: ");
    fflush(stdin);
    gets(&aux.generoLibro);

    printf("Autor: ");
    fflush(stdin);
    gets(&aux.autorLibro);

    aux.estado=1; // 0.dado de baja, 1.disponible, 2. prestado

    aux.idLibro=0; ///es necesario una funcion automatica

    inicFila(&aux.reservasLibro);

    aux.vecesPrestadoLibro=0;

    return aux;
}


/// lista simple de libros

nodoSimple*inicListaSimple()
{
    return NULL;
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
