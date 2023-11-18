#ifndef PILAPRESTAMOSINACTIVOS_H_INCLUDED
#define PILAPRESTAMOSINACTIVOS_H_INCLUDED
#include "listaDobleReservas.h"

typedef struct
{
    nodoDoble * prestamoInactivo;///lista doble

}pilaPrestamos;

///funciones de pilas
void inicPila(pilaPrestamos * pila);
void apilar(pilaPrestamos * pila);///no pasarle un dato ya que lo agarramos desde el archivo
void mostrar(pilaPrestamos * pila);


#endif // PILAPRESTAMOSINACTIVOS_H_INCLUDED
