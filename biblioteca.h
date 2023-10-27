#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#define MAX_DIM 20
#include "arbolMiembros.h"
#include "filaReservas.h"
#include "listaDobleReservas.h"
#include "listaSimpleLibros.h"

///estructuras

typedef struct
{

    char nombre[MAX_DIM];
    char direccion[MAX_DIM];
    char numeroDeTelefono[MAX_DIM];
    char dni[MAX_DIM];

} stPersona;

typedef struct
{

    int id; //id autoincremental
    stPersona datosPersonales;
    int historialDelPrestamo[100];///CHECKEAR SI USAR ARREGLO U OTRO TIPO DE DATO POR EL TAMAÑO FIJO,Arreglo con las ID de los prestamos que leyo(luego si quiere ver el libro lo busca por ID en un archivo)
    int estado; //activo o de baja
    int saldo;// es el dinero que el miembro ingreso a la cuenta, se debera utilizar dinero para los prestamos, si no tiene, no puede pagar un prestamo
    int prestamosActivos; // nro de cuantos prestamos tiene activos/en propiedad
    int limitePrestamos; // el usuario decide el limite de prestamos que tendra esta persona

} stMiembro;

///funciones


#endif // BIBLIOTECA_H_INCLUDED
