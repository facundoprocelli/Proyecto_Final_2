#ifndef LISTADOBLERESERVAS_H_INCLUDED
#define LISTADOBLERESERVAS_H_INCLUDED
#include "biblioteca.h"

///funciones estructura prestamos

stPrestamo crearUnPrestamo(int dniUsuarioPrestadoAux);

//mostrar
void mostrarUnaFecha(stFecha aux);
void mostrarUnPrestamo(stPrestamo aux);




///funciones lista doble

//basicas
nodoDoble*inicListaDoble();
nodoDoble*crearNodoDoble(stPrestamo aux);
void mostrarListaDoble(nodoDoble*listaDoble);

//insertar
nodoDoble*agregarAlPpioDoble(nodoDoble*listaDoble, nodoDoble*nuevoNodo);
nodoDoble*agregarAlFinalDoble(nodoDoble*listaDoble,nodoDoble*nuevoNodo);


//buscar
nodoDoble*buscarUltimoNodoDoble(nodoDoble*listaDoble);




//validaciones

int validarPrecioPrestamo(char aux[]);

#endif // LISTADOBLERESERVAS_H_INCLUDED
