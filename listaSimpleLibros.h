#ifndef LISTASIMPLELIBROS_H_INCLUDED
#define LISTASIMPLELIBROS_H_INCLUDED
#define MAX_DIM 26
#include "filaReservas.h"
///estructura libros

typedef struct{

    int idLibro; //id autoincremental
    char nombreDeLibro[MAX_DIM];
    char generoLibro[MAX_DIM];
    char autorLibro[MAX_DIM];
    char descripcionLibro[MAX_DIM];
    int estado; // si esta activo,eliminado o prestado
    int vecesPrestadoLibro;
    filaReservas reservasLibro;

} stLibro;

typedef struct
{
    stLibro datoLibro;
    struct nodoSimple*siguiente;

} nodoSimple;


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
nodoSimple* retornarNodoLibrosXAutor(nodoSimple* listaSimple, char autorBuscar[]);
stLibro retornarLibroXid(nodoSimple*listaSimple,int idBuscar);
stLibro retornarLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[]);
stLibro retornarUnSoloLibroXAutor(nodoSimple*listaSimple,char autorBuscar[]);
nodoSimple* retornarNodoLibrosXEstado(nodoSimple* listaSimple, int estado);


///validaciones
//Se utilizaron validaciones ya hechas en otras librerias para modularizar
void validarGenero(char auxGenero[]);
void opcionesGenero();


/// funciones del archivo de libros

void cargarUnLibroAlArchivo(stLibro aux);
#endif // LSTASIMPLESLIBROS_H_INCLUDED
