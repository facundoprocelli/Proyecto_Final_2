#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arbolMiembros.h"
#include "filaReservas.h"
#include "biblioteca.h"
#include "listaDobleReservas.h"
#include "listaSimpleLibros.h"

int main()
{
    char archivoMiembros[MAX_DIM]="archivoMiembros";
    char archivoPrestamos[MAX_DIM]="archivoPrestamos";
    char archivoLibros[MAX_DIM]="archivoLibros";

    nodoArbol*raiz=inicArbol();

    raiz= insertarNodoArbol(raiz,crearNodoArbol(crearUnMiembro()));

    nodoArbol*aux=buscarNodoArbol(raiz,1);

    mostrarArbolInorden(aux);

    return 0;
}
