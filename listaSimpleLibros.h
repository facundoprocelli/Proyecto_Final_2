#ifndef LISTASIMPLELIBROS_H_INCLUDED
#define LISTASIMPLELIBROS_H_INCLUDED
#include "biblioteca.h"

///funciones estructura libros

stLibro crearUnLibro();
void mostrarUnLibro(stLibro aux);


///funciones lista simple

//funciones basicas
nodoSimple*inicListaSimple();
void mostrarListaSimple(nodoSimple*listaSimple);
nodoSimple*crearNodoSimple(stLibro aux);
nodoSimple*agregarAlPpioSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo);
nodoSimple*agregarAlFinalSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo);

//funciones de verificar
int verificarSiExisteLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[]);




//funciones buscar

nodoSimple*retornarNodoSimpleXid(nodoSimple*listaSimple,int idBuscar);
stLibro retornarLibroXid(nodoSimple*listaSimple,int idBuscar);
stLibro retornarLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[]);


///validaciones
//Se utilizaron validaciones ya hechas en otras librerias para modularizar
void validarGenero(char auxGenero[]);
void opcionesGenero();


/// funciones del archivo de libros

void cargarUnLibroAlArchivo(stLibro aux);
#endif // LSTASIMPLESLIBROS_H_INCLUDED
