#ifndef FILARESERVAS_H_INCLUDED
#define FILARESERVAS_H_INCLUDED
#define MAX_DIM 26
#include "listaDobleReservas.h"




///estructura fila

typedef struct{

    nodoDoble*primero;
    nodoDoble*ultimo;

} filaReservas;

///funciones fila

void inicFila(filaReservas*reservas);
void agregarAlFinalFila(filaReservas*reservas, stPrestamo aux);
void mostrarFila(filaReservas reservas);
stPrestamo extraerUnPrestamoFila(filaReservas*reservas);
int filaVacia(filaReservas filaAux);
stFecha retornarUltimaFecha(filaReservas reservas);

///funciones para el archivo de prestamos
void recorrerFilaParaPrestamos(filaReservas reservasLibro,FILE*buffer);
void recorrerFilaParaArchivarPrestamos(filaReservas reservasLibro,FILE*buffer);


nodoDoble*borrarPrimerNodoDobleRETORNAR(nodoDoble*listaDoble);



#endif // FILARESERVAS_H_INCLUDED
