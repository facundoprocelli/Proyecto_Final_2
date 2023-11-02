#ifndef LISTASIMPLELIBROS_H_INCLUDED
#define LISTASIMPLELIBROS_H_INCLUDED
#define MAX_DIM 26
#define MAX_DIM_DESC 300
#include "filaReservas.h"
///estructura libros

typedef struct{

    int idLibro; //id autoincremental
    char nombreDeLibro[MAX_DIM];
    char generoLibro[MAX_DIM];
    char autorLibro[MAX_DIM];
    char descripcionLibro[MAX_DIM_DESC];
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

//Funciones de modificar

nodoSimple* modificarNombreLibro(nodoSimple* aux);
nodoSimple* modificarGeneroLibro(nodoSimple* aux);
nodoSimple* modificarAutorLibro(nodoSimple* aux);
nodoSimple* modificarDescripcionLibro(nodoSimple* aux);
nodoSimple* modificarEstadoLibro(nodoSimple* aux);



//funciones buscar


nodoSimple*retornarNodoSimpleXid(nodoSimple*listaSimple,int idBuscar);
nodoSimple* retornarNodosLibrosXAutor(nodoSimple* listaSimple, char autorBuscar[]);
stLibro retornarLibroXid(nodoSimple*listaSimple,int idBuscar);
stLibro retornarLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[]);
stLibro retornarUnSoloLibroXAutor(nodoSimple*listaSimple,char autorBuscar[]);
nodoSimple* retornarNodosLibrosXEstado(nodoSimple* listaSimple, int estado);


///validaciones
//Se utilizaron validaciones ya hechas en otras librerias para modularizar
void validarGenero(char auxGenero[]);
void opcionesGenero();


/// funciones del archivo de libros

void cargarUnLibroAlArchivo(stLibro aux);
#endif // LSTASIMPLESLIBROS_H_INCLUDED
