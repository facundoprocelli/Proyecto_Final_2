#include <stdio.h>
#include <stdlib.h>
#include "pilaPrestamosInactivos.h"
#define ARCHIVO_PRESTAMOS_INACTIVOS "archivoPrestamosInactivos.bin"

void inicPila(pilaPrestamos * pila)
{
    pila->prestamoInactivo = inicListaDoble();
}

void archivoAPila(pilaPrestamos * pila)
{
    stPrestamo aux;
    FILE * buffer = fopen(ARCHIVO_PRESTAMOS_INACTIVOS,"rb");
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stPrestamo),1,buffer)>0)
        {
            pila->prestamoInactivo = agregarAlPpioDoble(pila->prestamoInactivo,crearNodoDoble(aux));

        }
    }
    else
    {
        imprimirMensajeRojo("Archivo prestamos vacio");
    }
}

void apilar(pilaPrestamos * pila,stPrestamo aux)
{
    pila->prestamoInactivo = agregarAlPpioDoble(pila->prestamoInactivo,crearNodoDoble(aux));
}



void mostrarPila(pilaPrestamos pila)
{
    mostrarListaDoble(pila.prestamoInactivo);
}


void cargarPilaAlArchivo(pilaPrestamos * pila)
{

    FILE * buffer = fopen(ARCHIVO_PRESTAMOS_INACTIVOS,"wb");
    if(buffer != NULL)
    {
        while(pila->prestamoInactivo != NULL)
        {
            fwrite(&pila->prestamoInactivo,sizeof(stPrestamo),1,buffer);
            pila->prestamoInactivo = pila->prestamoInactivo->siguiente;
        }

    }
    else
    {
        imprimirMensajeRojo("Archivo de prestamos inactivos vacio");
    }

}
