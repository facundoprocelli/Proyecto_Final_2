#ifndef FILARESERVAS_H_INCLUDED
#define FILARESERVAS_H_INCLUDED
#define MAX_DIM 26
#include "listaDobleReservas.h"
typedef struct{

    nodoDoble*primero;
    nodoDoble*ultimo;

} filaReservas;

///funciones fila

void inicFila(filaReservas*reservas);
void agregarAlFinalFila(filaReservas*reservas,stPrestamo aux);
void mostrarFila(filaReservas reservas);
stPrestamo retornarPrimerPrestamoFila(filaReservas reservas);
stPrestamo extraerUnPrestamoFila(filaReservas reservas);

#endif // FILARESERVAS_H_INCLUDED
