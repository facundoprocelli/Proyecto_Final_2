#ifndef PILAPRESTAMOSINACTIVOS_H_INCLUDED
#define PILAPRESTAMOSINACTIVOS_H_INCLUDED
#include "listaDobleReservas.h"

typedef struct
{
    nodoDoble * prestamoInactivo;///lista doble

}pilaPrestamos;

///funciones de pilas
void inicPila(pilaPrestamos * pila);///inicializa la lista en null
void cargaPila(pilaPrestamos * pila);///no pasarle un dato ya que lo agarramos desde el archivo
void mostrar(pilaPrestamos * pila);///muestra los prestamos inactivos
void apilar(pilaPrestamos * pila,stPrestamo aux);///los prestamos que sean de estado 0 que se encuentren en la fila, los pasamos directamente a la pila.
void cargarPilaAlArchivo(pilaPrestamos * pila);///De la pila lo pasamos a un archivo que sea de prestamos inactivos para tener un registro

#endif // PILAPRESTAMOSINACTIVOS_H_INCLUDED
