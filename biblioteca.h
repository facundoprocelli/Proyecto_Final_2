#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include "listaSimpleLibros.h"
#include "listaDobleReservas.h"
#include "arbolMiembros.h"
#include "filaReservas.h"
#define MAX_DIM 26


///estructuras









///funciones biblioteca

void biblioteca();
int preguntarDatoEntero();
void limpiarPantalla();
void menuDeAccionesPrincipales();
void opcionesMenuGestionarLibros();
char menuLibros();
void opcionesMenuBuscarLibros();
char menuBuscarLibros();
void opcionesMenuActualizarLibros();
char menuActualizarLibro();

char menuMiembros();
void opcionesMenuMiembros();






#endif // BIBLIOTECA_H_INCLUDED
