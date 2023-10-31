#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaDobleReservas.h"

///funciones estructura prestamo

stPrestamo crearUnPrestamo(char dniUsuarioPrestadoAux[])
{
    stPrestamo aux;

    aux.idPrestamo= 0; ///Hacer una funcion automatica

    do
    {
        printf("Ingrese el precio del prestamo: ");
        fflush(stdin);
        scanf("%s",&aux.precioPrestamo);
    }while(validarPrecioPrestamo(aux.precioPrestamo) || validarCaracteresEnEnteros(aux.precioPrestamo) ==0);

    strcpy(aux.dniUsuarioPrestado,dniUsuarioPrestadoAux);

//    aux.inicioPrestamo
//    aux.vencimientoPrestamo

    return aux;
}


//mostrar una fecha
void mostrarUnaFecha(stFecha aux)
{
    printf("Dia....: %i \n",aux.diaTiempo);
    printf("Mes....: %i \n",aux.mesTiempo);
    printf("Anio...: %i \n",aux.anioTiempo);
}


//mostra un prestamo
void mostrarUnPrestamo(stPrestamo aux)
{
    puts("---------------------Prestamo---------------------");
    printf("ID Prestamo...............: %i \n",aux.idPrestamo);
    printf("DNI del miembro...........: %s \n",aux.dniUsuarioPrestado);
    printf("Precio del prestamo.......: %s \n",aux.precioPrestamo);
    printf("Inicio del prestamo.......:\n");
    mostrarUnaFecha(aux.inicioPrestamo);
    printf("Vencimiento del prestamo..: \n");
    mostrarUnaFecha(aux.vencimientoPrestamo);
    puts("--------------------------------------------------");
}

///funciones lista doble

// iniciar lista doble
nodoDoble*inicListaDoble()
{
    return NULL;
}

void mostrarListaDoble(nodoDoble*listaDoble)
{
    while(listaDoble != NULL)
    {
        mostrarUnPrestamo(listaDoble->datoPrestamo);
        listaDoble=listaDoble->siguiente;
    }
}

//crear nodo doble

nodoDoble*crearNodoDoble(stPrestamo aux)
{
    nodoDoble*nuevoNodo=(nodoDoble*)malloc(sizeof(stPrestamo));
    nuevoNodo->datoPrestamo=aux;
    nuevoNodo->anterior=NULL;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

// agregar al principio doble

nodoDoble*agregarAlPpioDoble(nodoDoble*listaDoble, nodoDoble*nuevoNodo)
{
    nuevoNodo->siguiente=listaDoble;
    if(listaDoble != NULL)
    {
        listaDoble->anterior=nuevoNodo;
    }
    return nuevoNodo;
}

//buscar ultimo nodo doble

nodoDoble*buscarUltimoNodoDoble(nodoDoble*listaDoble)
{
    if(listaDoble != NULL)
    {
        while(listaDoble->siguiente != NULL)
        {
            listaDoble=listaDoble->siguiente;
        }
    }
    return listaDoble; // si la lista esta vacia me retorna NULL
}

// agregar al final doble
nodoDoble*agregarAlFinalDoble(nodoDoble*listaDoble,nodoDoble*nuevoNodo)
{
    if(listaDoble != NULL)
    {
        nodoDoble*aux=buscarUltimoNodoDoble(listaDoble);

        aux->siguiente=nuevoNodo;

        nuevoNodo->anterior=aux;
    }
    else
    {
        listaDoble= nuevoNodo;
    }
    return listaDoble;
}

//validaciones

int validarPrecioPrestamo(char aux[])
{
    int flag=0;
    int dato=atoi(aux); // funcion que convierte numeros en un string al tipo de dato entero
    int min=0,max=10000;


    if(dato < min || dato > max)
    {
        puts("Ingrese un precio valido \n");
        flag=1;
    }

    return flag;
}
