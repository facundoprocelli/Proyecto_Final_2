#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "filaReservas.h"
#define MAX_DIM 26
#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"

void inicFila(filaReservas*reservas)
{
    reservas->primero=inicListaDoble();
    reservas->ultimo=inicListaDoble();
}

void agregarAlFinalFila(filaReservas*reservas,stPrestamo aux)
{
    nodoDoble*nuevoNodo=crearNodoDoble(aux);
    if(reservas->primero != NULL)
    {


        ((nodoDoble*)(reservas->ultimo))->siguiente=nuevoNodo;

        nuevoNodo->anterior=reservas->ultimo;

        reservas->ultimo=nuevoNodo;

    }
    else
    {

        reservas->primero=nuevoNodo;

        reservas->ultimo=nuevoNodo;
    }

}

void mostrarFila(filaReservas reservas)
{
    if(reservas.primero != NULL)
    {
        printf("INICIO \n");
        mostrarListaDoble(reservas.primero);
        printf("FIN \n");
    }
    else
    {
        imprimirMensajeRojo("Fila vacia");
    }
}

stPrestamo retornarPrimerPrestamoFila(filaReservas reservas)
{
    stPrestamo dato;
    if(reservas.primero != NULL)
    {
        dato=reservas.primero->datoPrestamo;
    }
    return dato;

}

stPrestamo extraerUnPrestamoFila(filaReservas reservas)
{

    stPrestamo prestamo;
    if(reservas.primero != NULL)
    {

        prestamo=reservas.primero->datoPrestamo;

        reservas.primero=borrarPrimerNodoDoble(reservas.primero);

        if(reservas.primero == NULL)
        {
            reservas.ultimo= NULL;
        }

    }
    return prestamo;
}



///funciones para el archivo de prestamos

void recorrerFilaParaArchivarPrestamos(filaReservas reservasLibro,FILE*buffer)
{

    stPrestamo auxPrestamo;
    while(reservasLibro.primero != NULL)
    {
        auxPrestamo=reservasLibro.primero->datoPrestamo;
        fwrite(&auxPrestamo,sizeof(stPrestamo),1,buffer);
        reservasLibro.primero=reservasLibro.primero->siguiente;
    }

}



