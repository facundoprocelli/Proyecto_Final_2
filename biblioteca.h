#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include "listaSimpleLibros.h"
#include "listaDobleReservas.h"
#include "arbolMiembros.h"
#include "filaReservas.h"
#define MAX_DIM 26


///estructuras


typedef struct
{
    nodoSimple* listaLibro;
    char generoEstanteria[MAX_DIM];


}estanteria;






///funciones biblioteca

void biblioteca();
int preguntarDatoEntero();
void limpiarPantalla();
void menuDeAccionesPrincipales();
void opcionesMenuGestionarLibros();
void menuLibros();
void opcionesMenuBuscarLibros();
void menuBuscarLibros();
void opcionesMenuActualizarLibros();
void actualizarLibro(estanteria arregloListas[]);

void menuMiembros();
void opcionesMenuMiembros();

void opcionesMenuBuscarMiembros();
void menuBuscarMiembros();





#endif // BIBLIOTECA_H_INCLUDED
