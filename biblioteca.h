#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#include "listaSimpleLibros.h"
#define MAX_DIM 26



//funciones clasicas
int preguntarDatoEntero();
void limpiarPantalla();


///funciones biblioteca


void biblioteca();
void menuDeAccionesPrincipales();

void opcionesMenuGestionarLibros();
void menuLibros(estanteria arregloEstanterias[]);

void actualizarLibro(estanteria arregloEstanterias[]);
void opcionesMenuActualizarLibros();

void opcionesMenuBuscarLibros();
void menuBuscarLibros();

void menuMiembros();
void opcionesMenuMiembros();

void opcionesMenuBuscarMiembros();
void menuBuscarMiembros();

///funciones de estanteria
void inicEstanterias(estanteria arregloEstanterias[]);
void mostrarTodasLasEstanterias(estanteria arregloEstanterias[]);
void mostrarUnaEstanteria(estanteria unaEstanteriaSola);
void cargarEstanteriaOrdenada(estanteria arregloEstanterias[],nodoSimple*nuevoNodo);

#endif // BIBLIOTECA_H_INCLUDED
