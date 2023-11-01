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


