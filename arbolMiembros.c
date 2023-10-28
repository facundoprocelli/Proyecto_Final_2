#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"



/*
typedef struct
{

    int id; //id autoincremental
    stPersona datosPersonales;
    int historialDelPrestamo[100];///CHECKEAR SI USAR ARREGLO U OTRO TIPO DE DATO POR EL TAMA�O FIJO,Arreglo con las ID de los prestamos que leyo(luego si quiere ver el libro lo busca por ID en un archivo)
    int estado; //activo o de baja
    int saldo;// es el dinero que el miembro ingreso a la cuenta, se debera utilizar dinero para los prestamos, si no tiene, no puede pagar un prestamo
    int prestamosActivos; // nro de cuantos prestamos tiene activos/en propiedad
    int limitePrestamos; // el usuario decide el limite de prestamos que tendra esta persona

} stMiembro;

*/


/// crear un miembro

stPersona crearUnaPersona()
{
    stPersona aux;

    puts("----------------- Ingrese los datos personales del nuevo miembro ---------------------"); /// HACER VALIDACIONES
    printf("Nombre: ");
    fflush(stdin);
    scanf("%s", &aux.nombre);

    printf("DNI: ");
    fflush(stdin);
    scanf("%s", &aux.dni);

    printf("Nro de telefono: ");
    fflush(stdin);
    scanf("%s", &aux.numeroDeTelefono);

    printf("Direccion: ");
    fflush(stdin);
    scanf("%s", &aux.direccion);

    return aux;
}

stMiembro crearUnMiembro()
{
    stMiembro auxMiembro;

    auxMiembro.datosPersonales = crearUnaPersona();

    auxMiembro.historialDelPrestamo[0] = 0;

    auxMiembro.estado = 0; // activo o dado de baja

    auxMiembro.idMiembro = 0; /// hacer funcion de ID automatica

    auxMiembro.prestamosActivos = 0;

    auxMiembro.saldo=0;

    auxMiembro.limitePrestamos = 5; // predeterminado

    return auxMiembro;
}

///mostrar un miembro

void mostrarUnaPersona(stPersona aux)
{
    printf("Nombre: |%s|\n", aux.nombre);
    printf("Dni: |%s| \n", aux.dni);
    printf("Nro de telefono: |%s|\n", aux.numeroDeTelefono);
    printf("Direccion: |%s| \n", aux.direccion);
}

void mostrarUnMiembro(stMiembro aux)
{
    mostrarUnaPersona(aux.datosPersonales);
    printf("Historial de prestamos: |%i|\n", aux.historialDelPrestamo); /// for para poder ver todos
    printf("Estado: |%i| \n", aux.estado);
    printf("ID: |%i|\n", aux.idMiembro);
    printf("Prestamos activos: |%i|\n", aux.prestamosActivos);
    printf("Saldo en cuenta: |%i|\n", aux.saldo);
}

/// Iniciar un arbol

nodoArbol *inicArbol()
{
    return NULL;
}

/// Crear el nodo del arbol

nodoArbol *crearNodoArbol(stMiembro miembro)
{

    nodoArbol *aux = (nodoArbol *)malloc(sizeof(nodoArbol));

    aux->dato = miembro;
    aux->izq = inicArbol();
    aux->der = inicArbol();

    return aux;
}

/// Buscar un nodo en un arbol

nodoArbol *buscarNodoArbol(nodoArbol *raiz, int idBuscar)
{

    nodoArbol *rta = inicArbol();
    if (raiz != NULL)
    {
        if (idBuscar == raiz->dato.idMiembro)
        {
            rta = raiz;
        }
        else
        {

            if (idBuscar > raiz->dato.idMiembro)
            {
                // primer acercamiento al corte
                rta = buscarNodo(raiz->der, idBuscar);
            }
            else
            {
                // segundo acercamiento al corte
                rta = buscarNodo(raiz->izq, idBuscar);
            }
        }
    }
    return rta;
}

/// Insertar un nodo en un arbol

nodoArbol *insertarNodoArbol(nodoArbol *raiz, nodoArbol *NuevoNodo)
{

    if (raiz == NULL)
    {
        raiz = NuevoNodo;
    }

    else
    {

        if (NuevoNodo->dato.idMiembro > raiz->dato.idMiembro)
        {
            // Pongo ese = ya que el dato se va a linkear a esa parte
            raiz->der = insertarNodo(raiz->der, NuevoNodo);
        }
        else
        {
            // Pongo ese = ya que el dato se va a linkear a esa parte
            raiz->izq = insertarNodo(raiz->izq, NuevoNodo);
        }
    }

    return raiz;
}

void preorden(nodoArbol *raiz)
{

    if (raiz != NULL)
    {

        mostrarUnMiembro(raiz->dato);
        preorden(raiz->izq);
        preorden(raiz->der);
    }
}

void inorder(nodoArbol *raiz)
{

    if (raiz != NULL)
    {

        preorden(raiz->izq);
        mostrarUnMiembro(raiz->dato);
        preorden(raiz->der);
    }
}

void postorder(nodoArbol *raiz)
{

    if (raiz != NULL)
    {

        preorden(raiz->izq);
        preorden(raiz->der);
        mostrarUnMiembro(raiz->dato);
    }
}

int esHoja(nodoArbol*raiz)
{
    return (raiz && !raiz->izq && !raiz->der);
}

int esGradoUnoArbol(nodoArbol*raiz)
{
    return (raiz && ((raiz->izq && !raiz->der) || (!raiz->izq && raiz->der)));
}

int estaLlenoArbol(nodoArbol*raiz)
{
    return (raiz && raiz->izq && raiz->der);
}

int arbolVacio(nodoArbol*raiz)
{
    return raiz;
}

// Borrar Nodo

nodoArbol* nodoMasDerechaArbol(nodoArbol*raiz)
{
    while(raiz->der != NULL)
    {
        raiz=raiz->der;
    }
    return raiz;
}

nodoArbol* nodoMasIzquierdaArbol(nodoArbol*raiz)
{
    while(raiz->izq != NULL)
    {
        raiz=raiz->izq;
    }
    return raiz;
}

nodoArbol *borrarNodoArbol(nodoArbol *raiz, int idBuscar)
{
    if (raiz != NULL)
    {

        if (raiz->dato.idMiembro == idBuscar)
        {

            if (raiz->izq != NULL)
            {

                nodoArbol *masDerecha = nodoMasDerecha(raiz->izq);
                raiz->dato.idMiembro = masDerecha->dato.idMiembro;
                raiz->izq = borrarNodo(raiz->izq, masDerecha->dato.idMiembro);
            }
            else if (raiz->der != NULL)
            {
                nodoArbol *masIzquierda = nodoMasIzquierda(raiz->der);
                raiz->dato.idMiembro = masIzquierda->dato.idMiembro;
                raiz->der = borrarNodo(raiz->der, masIzquierda->dato.idMiembro);
            }
            if (esHoja(raiz) == 1)
            {
                free(raiz);
                raiz = NULL;
            }
        }
        else if (idBuscar < raiz->dato.idMiembro)
        {
            raiz->izq = borrarNodo(raiz->izq, idBuscar);
        }

        else
        {
            raiz->der = borrarNodo(raiz->der, idBuscar);
        }
    }

    return raiz;
}
