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




/// Funciones principales TDA fila
void agregarAlFinalFila(filaReservas*reservas,stPrestamo aux)
{
    nodoDoble * NN = crearNodoDoble(aux);

    if(reservas->primero != NULL)
    {
        reservas->ultimo->siguiente=NN;

        NN->anterior = reservas->ultimo;
        reservas->ultimo=NN;
    }
    else
    {
        reservas->primero = NN;
        reservas->ultimo = NN;
    }

}

void mostrarFila(filaReservas reservas)
{
    if(reservas.primero != NULL)
    {
        imprimirMensajeVerde("=======================INICIO======================= \n");
        mostrarListaDoble(reservas.primero);
        imprimirMensajeVerde("=======================FIN=======================\n");
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

stPrestamo extraerUnPrestamoFila(filaReservas*reservas)
{

    stPrestamo prestamo;
    if(reservas->primero != NULL) // si mi fila tiene datos
    {

        prestamo=reservas->primero->datoPrestamo;

        reservas->primero=borrarPrimerNodoDobleRETORNAR(reservas->primero);


        if(reservas->primero == NULL)
        {

            reservas->ultimo= inicListaDoble();
        }

    }


    mostrarUnPrestamo(prestamo);

    return prestamo;
}


nodoDoble*borrarPrimerNodoDobleRETORNAR(nodoDoble*listaDoble)
{
    nodoDoble*liberar=inicListaDoble();
    if(listaDoble != NULL)
    {
        liberar=listaDoble;

        listaDoble=listaDoble->siguiente;

        free(liberar);
    }

    return listaDoble;
}





int filaVacia(filaReservas filaAux)
{
    int flag=0;
    if(filaAux.primero == NULL)
    {
        flag=1;
    }
    return flag;
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

stFecha retornarUltimaFecha(filaReservas reservas)
{


    time_t tiempoActual;
    time(&tiempoActual);
    struct tm *infoTiempo = localtime(&tiempoActual);

    stFecha fecha;
    if(reservas.primero == NULL)
    {
        asignarTiempo(&fecha,infoTiempo);
    }
    else
    {
        fecha = reservas.ultimo->datoPrestamo.vencimientoPrestamo;
    }

    return fecha;
}

