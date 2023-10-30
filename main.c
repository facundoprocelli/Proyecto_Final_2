#include <stdio.h>
#include <stdlib.h>
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

//    nodoSimple*listaSimple=inicListaSimple();
//    listaSimple=agregarAlFinalSimple(listaSimple,crearNodoSimple(crearUnLibro()));
//    mostrarListaSimple(listaSimple);

    nodoArbol*raiz=inicArbol();
    raiz=insertarPorDni(raiz,crearNodoArbol(crearUnMiembro()));
    raiz=insertarPorDni(raiz,crearNodoArbol(crearUnMiembro()));
//    raiz=insertarPorDni(raiz,crearNodoArbol(crearUnMiembro()));
    mostrarArbolInorden(raiz);
    puts("\n...........................Buscar............................\n");
    ///raiz = borrarUnNodoPorDni(raiz,"46012540");
    nodoArbol * buscado = buscarNodoPorDniArbol(raiz,"46012540");
    mostrarArbolInorden(buscado);

//    nodoDoble*listaDoble=inicListaDoble();
//    listaDoble=agregarAlFinalDoble(listaDoble,crearNodoDoble(crearUnPrestamo(35)));
//    mostrarListaDoble(listaDoble);


    return 0;
}



