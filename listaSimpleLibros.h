#ifndef LISTASIMPLELIBROS_H_INCLUDED
#define LISTASIMPLELIBROS_H_INCLUDED
#define MAX_DIM 26
#define MAX_DIM_TITULO 50
#define MAX_DIM_DESC 300
#include "filaReservas.h"
#include "arbolMiembros.h"

///estructura libros

typedef struct
{

    int idLibro; //id autoincremental
    char nombreDeLibro[MAX_DIM_TITULO];
    char generoLibro[MAX_DIM];
    char autorLibro[MAX_DIM];
    char descripcionLibro[MAX_DIM_DESC];
    int estado; // si esta activo,eliminado o prestado
    int vecesPrestadoLibro;
    char cantidadDeCopias[MAX_DIM];
    filaReservas reservasLibro;

} stLibro;


///estructura listaSimple

typedef struct
{
    stLibro datoLibro;
    struct nodoSimple*siguiente;

} nodoSimple;

///estructura estanteria

typedef struct
{
    nodoSimple* listaLibro;
    char generoEstanteria[MAX_DIM];

}estanteria;



///funciones estructura libros

stLibro crearUnLibro(estanteria arregloEstanterias[]);
void mostrarUnLibro(stLibro aux);


///funciones lista simple

//funciones basicas
nodoSimple*inicListaSimple();
void mostrarListaSimple(nodoSimple*listaSimple);
nodoSimple*crearNodoSimple(stLibro aux);
nodoSimple*agregarAlPpioSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo);
nodoSimple*agregarAlFinalSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo);
void cargarEstanteriaOrdenada(estanteria arregloEstanterias[],nodoSimple*nuevoNodo);

void cargarLibrosPredeterminados(estanteria arregloEstanteria[]);
//funciones de verificar
int verificarSiExisteLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[]);

//Funciones de modificar

nodoSimple* modificarNombreLibro(nodoSimple* aux);
nodoSimple* modificarGeneroLibro(nodoSimple* aux);
nodoSimple* modificarAutorLibro(nodoSimple* aux);
nodoSimple* modificarDescripcionLibro(nodoSimple* aux);
nodoSimple* modificarEstadoLibro(nodoSimple* aux);
nodoSimple* modificarCantidadDeCopias(nodoSimple* aux);

// funciones de mostrar

void buscarLibroXAutor(estanteria arregloEstanterias[]);
void buscarEstanteriaParaAutor(estanteria arregloEstanterias[], char autor[]);
void buscarLibroXgenero(estanteria arregloEstanterias[]);
void buscarLibroXTitulo(estanteria arregloEstanterias[]);
void buscarEstanteriaParaTitulo(estanteria arregloEstanterias[], char titulo[]);
void buscarLibroXClave( estanteria arregloEstanterias[]);
void buscarPalabrasClaves(nodoSimple* listaSimple, char claves[]);
void buscarLibrosXEstado(estanteria arregloEstanterias[]);
void buscarLibrosXCopias(estanteria arregloEstanterias[]);
void buscarLibrosUsuario(estanteria arregloEstanterias[]);
void menuOpcionesCopias();
void menuOpcionesDisponibilidad();
void menuEstados();


//funciones buscar

nodoSimple*retornarNodoSimpleXid(nodoSimple*listaSimple,int idBuscar);
nodoSimple* retornarNodosLibrosXAutor(nodoSimple* listaSimple, char autorBuscar[]);
stLibro retornarLibroXid(nodoSimple*listaSimple,int idBuscar);
stLibro retornarLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[]);
stLibro retornarUnSoloLibroXAutor(nodoSimple*listaSimple,char autorBuscar[]);
nodoSimple* retornarNodosLibrosXEstado(nodoSimple* listaSimple, int estado);
int retornarIDMasGrandeEnLista(nodoSimple*listaSimple);
int retornarUltimoIDLibro(estanteria arregloEstanterias[]);
nodoSimple* retornarNodosLibroXTitulo(nodoSimple* listaSimple, char tituloBuscar[]);
nodoSimple* retornarNodosLibroXClave(nodoSimple* listaSimple, char clave[]);
nodoSimple* retornarNodosLibrosXCopias(nodoSimple* lista,int minCopias, int maxCopias);
nodoSimple* retornarNodosLibrosXDisponibilidad(nodoSimple* lista);
void verLibrosDisponiblesUsuario(estanteria arregloEstanterias[]);
void buscarEstanteriaParaCopias(estanteria arregloEstanterias[], int minCopias, int maxCopias);
void buscarEstanteriaParaEstado(estanteria arregloEstanterias[], int opcion);


///validaciones
//Se utilizaron validaciones ya hechas en otras librerias para modularizar
void validarGenero(char auxGenero[]);
void opcionesGenero();
int verificarSiHayCopiasEnUnLibro(stLibro datoLibro);


/// funciones del archivo de libros
void cargarUnLibroAlArchivo(stLibro aux);

void estanteriaAlArchivo(estanteria arregloEstanterias[]);
void archivoAEstanteria(estanteria arregloEstanterias[]);

/// funciones del archivo de prestamos
void prestamosAlArchivo(estanteria arregloEstanterias[]);
void recorrerLibrosParaFila(nodoSimple*listaSimpleLibros,FILE*buffer);
void recorrerFilaParaArchivarPrestamos(filaReservas reservasLibro,FILE*buffer);
void archivoAFilasPrestamos(estanteria arregloEstanterias[]);
void recorrerEstanteriasParaAgregarAFilaPrestamo(estanteria arregloEstanterias[], stPrestamo datoPrestamo);
int recorrerLibrosParaAgregarAFilaPrestamo(nodoSimple*listaS, stPrestamo datoPrestamo);

#endif // LSTASIMPLESLIBROS_H_INCLUDED
