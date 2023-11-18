#include <stdio.h>
#include <stdlib.h>
#include "pilaPrestamosInactivos.h"
#define ARCHIVO_PRESTAMOS_INACTIVOS "archivoPrestamosInactivos.bin"

void inicPila(pilaPrestamos * pila)
{
    pila->prestamoInactivo = inicListaDoble();
}

void cargaPila(pilaPrestamos * pila)
{
    stPrestamo aux;
    FILE * buffer = fopen(ARCHIVO_PRESTAMOS_INACTIVOS,"rb");
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stPrestamo),1,buffer)>0)
        {
            if(aux.estado == 0)///si el prestamo esta inactivo lo apilo
            {
                pila->prestamoInactivo = agregarAlFinalDoble(pila->prestamoInactivo,crearNodoDoble(aux));
            }

        }
    }
    else
    {
        puts("Archivo prestamos vacio");
    }
}

void apilar(pilaPrestamos * pila,stPrestamo aux)
{
    if(aux.estado == 0)
    {
        pila->prestamoInactivo = agregarAlFinalDoble(pila->prestamoInactivo,crearNodoDoble(aux));

    }
}

void mostrar(pilaPrestamos * pila)
{

mostrarListaDoble(pila->prestamoInactivo);

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
        puts("Archivo de prestamos inactivos vacio");
    }

}
