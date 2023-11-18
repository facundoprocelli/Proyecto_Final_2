#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#define MAX_DIM 26
#include "listaSimpleLibros.h"



//funciones clasicas
int preguntarDatoEntero();


void limpiarPantalla();


///funciones biblioteca


void biblioteca(estanteria arregloEstanterias[], nodoArbol* arbolMiembros);
void menuDeAccionesPrincipales();

void menuUsuario(estanteria arregloEstanterias[], nodoArbol* arbolMiembros);

void menuLibrosUsuario();
void opcionesMenuUsuarioLibros();

void menuPrestamosUsuario();
void opcionesMenuUsuarioPrestamos();

void menuMiembroUsuario();
void opcionesMenuUsuarioMiembro();

void opcionesMenuGestionarLibros();
void menuLibros(estanteria arregloEstanterias[]);

void actualizarLibro(estanteria arregloEstanterias[]);
void opcionesMenuActualizarLibros();

void opcionesMenuBuscarLibros();
void menuBuscarLibros();

void menuMiembros(nodoArbol * raiz);
void opcionesMenuMiembros();

void opcionesMenuBuscarMiembros();
void menuBuscarMiembros();

void opcionesMenuPrestamos();
void menuPrestamos();



void informeFinal(nodoArbol*raiz,estanteria arregloEstanterias[]);

///funciones de estanteria
void inicEstanterias(estanteria arregloEstanterias[]);
void mostrarTodasLasEstanterias(estanteria arregloEstanterias[]);
void mostrarUnaEstanteria(estanteria unaEstanteriaSola);


#endif // BIBLIOTECA_H_INCLUDED
