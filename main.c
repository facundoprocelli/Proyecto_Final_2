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

    //printf("\Benvindo a la Biblotequiña do BookMaze\n");
    //biblioteca();

    nodoSimple*listaSimple=inicListaSimple();
    listaSimple=agregarAlFinalSimple(listaSimple,crearNodoSimple(crearUnLibro()));
    mostrarListaSimple(listaSimple);

//    nodoArbol*raiz=inicArbol();
//    raiz=insertarNodoArbol(raiz,crearNodoArbol(crearUnMiembro()));
//    mostrarArbolInorden(raiz);


    nodoDoble*listaDoble=inicListaDoble();
    listaDoble=agregarAlFinalDoble(listaDoble,crearNodoDoble(crearUnPrestamo(35)));
    mostrarListaDoble(listaDoble);


    return 0;
}



