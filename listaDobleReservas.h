#ifndef LISTADOBLERESERVAS_H_INCLUDED
#define LISTADOBLERESERVAS_H_INCLUDED
#include "pilaPrestamosInactivos.h"
#define MAX_DIM 26



///funciones estructura prestamos

stPrestamo crearUnPrestamo(char dniUsuarioPrestadoAux[]);

//mostrar
void mostrarUnaFecha(stFecha aux);
void mostrarUnPrestamo(stPrestamo aux);

void asignarTiempo(stFecha * aux,struct tm * info_tiempo);
void calcularVencimiento(stFecha *vencimiento, stFecha inicio,int duracionPrestamo);

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

//borrar
nodoDoble*borrarPrimerNodoDoble(nodoDoble*listaDoble);


//validaciones
int validarDias(int dias);
int validarPrecioPrestamo(char aux[]);

///Funciones archivo
int retornarUltimoIDPrestamo();

#endif // LISTADOBLERESERVAS_H_INCLUDED
