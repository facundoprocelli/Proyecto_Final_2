#include <stdio.h>
#include <stdlib.h>
#include "pilaPrestamosInactivos.h"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"

void inicPila(pilaPrestamos * pila)
{
    pila->prestamoInactivo = inicListaDoble();
}

void apilar(pilaPrestamos * pila)
{
    stPrestamo aux;
    FILE * buffer = fopen(ARCHIVO_PRESTAMOS,"rb");
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

void mostrar(pilaPrestamos * pila)
{

mostrarListaDoble(pila->prestamoInactivo);

}
