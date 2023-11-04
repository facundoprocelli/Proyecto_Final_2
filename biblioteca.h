#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#include "listaSimpleLibros.h"
#include "listaDobleReservas.h"
#include "arbolMiembros.h"
#include "filaReservas.h"
#define MAX_DIM 26


///estructura estanteria


typedef struct
{
    nodoSimple* listaLibro;
    char generoEstanteria[MAX_DIM];


}estanteria;



//funciones clasicas
int preguntarDatoEntero();
void limpiarPantalla();


///funciones biblioteca


void biblioteca();
void menuDeAccionesPrincipales();

void opcionesMenuGestionarLibros();
void menuLibros();

void actualizarLibro(estanteria arregloListas[]);
void opcionesMenuActualizarLibros();

void opcionesMenuBuscarLibros();
void menuBuscarLibros();

void menuMiembros();
void opcionesMenuMiembros();

void opcionesMenuBuscarMiembros();
void menuBuscarMiembros();

///funciones de estanteria
void inicEstanterias(estanteria arregloListas[], int dim);
void mostrarTodasLasEstanterias(estanteria arregloListas[],int dim);
void mostrarUnaEstanteria(estanteria unaEstanteriaSola);
void cargarEstanteriaOrdenada(estanteria arregloListas[],nodoSimple*nuevoNodo);


#endif // BIBLIOTECA_H_INCLUDED
