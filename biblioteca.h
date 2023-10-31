#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#define MAX_DIM 26


///estructuras

///Estructura miembros

typedef struct
{

    char nombre[MAX_DIM];
    char direccion[MAX_DIM];
    char numeroDeTelefono[MAX_DIM];
    char dni[MAX_DIM];

} stPersona;

typedef struct
{

    stPersona datosPersonales;
    int historialDelPrestamo[100];///CHECKEAR SI USAR ARREGLO U OTRO TIPO DE DATO POR EL TAMA�O FIJO,Arreglo con las ID de los prestamos que leyo(luego si quiere ver el libro lo busca por ID en un archivo)
    int estado; //activo o de baja
    int saldo;// es el dinero que el miembro ingreso a la cuenta, se debera utilizar dinero para los prestamos, si no tiene, no puede pagar un prestamo
    int prestamosActivos; // nro de cuantos prestamos tiene activos/en propiedad
    int limitePrestamos; // el usuario decide el limite de prestamos que tendra esta persona

} stMiembro;

// Estrutura Arbol

typedef struct
{

    stMiembro dato;
    struct nodoArbol* derecha;
    struct nodoArbol* izquierda;

} nodoArbol;


///Estructura prestamos

typedef struct{

    int diaTiempo;
    int mesTiempo;
    int anioTiempo;

} stFecha;

typedef struct{

    int idPrestamo;
    char dniUsuarioPrestado[MAX_DIM];
    char precioPrestamo[MAX_DIM];
    stFecha inicioPrestamo;
    stFecha vencimientoPrestamo;

} stPrestamo;


typedef struct
{
    stPrestamo datoPrestamo;
    struct nodoDoble*anterior;
    struct nodoDoble*siguiente;

} nodoDoble;


typedef struct{

    struct nodoDoble*primero;
    struct nodoDoble*ultimo;

} filaReservas;

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

///funciones biblioteca

void biblioteca();
int preguntarDatoEntero();
void limpiarPantalla();
void menuDeAccionesPrincipales();
void opcionesMenuGestionarLibros();
void menuLibros();
void opcionesMenuBuscarLibros();
void menuBuscarLibros();
void opcionesMenuActualizarLibros();
void menuActualizarLibro();

void menuMiembros();
void opcionesMenuMiembros();

/*
#include "arbolMiembros.h"
#include "filaReservas.h"
#include "listaDobleReservas.h"
#include "listaSimpleLibros.h"

*/

#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"

#endif // BIBLIOTECA_H_INCLUDED
