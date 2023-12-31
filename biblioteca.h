#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#define MAX_DIM 26
#include "listaSimpleLibros.h"



//funciones clasicas
int preguntarDatoEntero();
int convertirStringsDeNumerosAEntero(char aux[]);

void limpiarPantalla();


///funciones biblioteca

void opcionesMenuGeneral();

nodoArbol*  biblioteca(estanteria arregloEstanterias[], nodoArbol* arbolMiembros);
void menuDeAccionesPrincipales();

void menuUsuario(estanteria arregloEstanterias[],nodoArbol * arbolMiembro, nodoArbol*miembroActual, pilaPrestamos*prestamosInactivos);

void menuLibrosUsuario(estanteria arregloEstanterias[],nodoArbol* miembroActual,pilaPrestamos*prestamosInactivos,nodoArbol*arbolMiembros);
void opcionesMenuUsuarioLibros();

void menuPrestamosUsuario();
void opcionesMenuUsuarioPrestamos();

void menuMiembroUsuario();
void opcionesMenuUsuarioMiembro();

void opcionesMenuBuscarLibrosUsuario();
void buscarLibrosUsuario(estanteria arregloEstanterias[]);

void opcionesMenuGestionarLibros();
void menuLibros(estanteria arregloEstanterias[]);

void actualizarLibro(estanteria arregloEstanterias[]);
void opcionesMenuActualizarLibros();

void opcionesMenuBuscarLibros();
void menuBuscarLibros();

nodoArbol* menuMiembros(nodoArbol * raiz);
void opcionesMenuMiembros();

void opcionesMenuBuscarMiembros();
void menuBuscarMiembros();

void opcionesMenuPrestamos();
void menuPrestamos();







///funciones de estanteria
void inicEstanterias(estanteria arregloEstanterias[]);
void mostrarTodasLasEstanterias(estanteria arregloEstanterias[]);
void mostrarUnaEstanteria(estanteria unaEstanteriaSola);

///funciones de informes
void informeFinal(nodoArbol*raiz,estanteria arregloEstanterias[],pilaPrestamos pila);
//contar miembros ya existe
int contarMiembrosActivos(nodoArbol * raiz);
int contarMiembrosInactivos(nodoArbol * raiz);
int contarCantidadDeLibros(estanteria arregloEstanterias[]);
int contarPrestamos(estanteria arregloEstanterias[]);
int contarPrestamosInactivos(pilaPrestamos pilita);
int miembroConMayorSaldo(nodoArbol * raiz);
void verHistorialPrestamos(nodoArbol* miembroActual);

/// funciones de prestamos

void devolverUnLibroUsuario(estanteria arregloEstanterias[],pilaPrestamos*prestamosInactivos,nodoArbol*miembroActual);
int retornarPosEstanteriaXGenero(estanteria arregloEstanteria[], char generoBuscar[]);



#endif // BIBLIOTECA_H_INCLUDED
