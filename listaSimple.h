#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED
#define MAX_DIM 20


typedef struct
{

    char nombre[MAX_DIM];
    char direccion[MAX_DIM];
    char numeroDeTelefono[MAX_DIM];

} stPersona;

typedef struct
{

    stPersona datosPersonales;
    int historialDelPrestamo[1000];///CHECKEAR SI USAR ARREGLO U OTRO TIPO DE DATO POR EL TAMAÑO FIJO,Arreglo con las ID de los prestamos que leyo(luego si quiere ver el libro lo busca por ID en un archivo)
    int id;
    int estado;///0 no tiene prestamos. 1 tiene prestamos
    char saldo[MAX_DIM];
    int prestamosActivos;

} stMiembro;

typedef struct
{

    stMiembro dato;
    struct nodoSimple * siguiente;

} nodoSimple;

#endif // LISTASIMPLE_H_INCLUDED
