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
    int historialDelPrestamo[100];///CHECKEAR SI USAR ARREGLO U OTRO TIPO DE DATO POR EL TAMAÑO FIJO,Arreglo con las ID de los prestamos que leyo(luego si quiere ver el libro lo busca por ID en un archivo)
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

    auxMiembro.id = 0; /// hacer funcion de ID automatica

    auxMiembro.prestamosActivos = 0;

    strcpy(auxMiembro.saldo, 0);

    auxMiembro.limitePrestamos = 5; // predeterminado

    return auxMiembro;
}

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
    printf("ID: |%i|\n", aux.id);
    printf("Prestamos activos: |%i|\n", aux.prestamosActivos);
    printf("Saldo en cuenta: |%i|\n", aux.saldo);
}

/// Inicar un arbol
nodoArbol *inicarbol()
{
    return NULL;
}

/// Crear el nodo del arbol

nodoArbol *crearNodoArbol(stMiembro miembro)
{

    nodoArbol *aux = (nodoArbol *)malloc(sizeof(nodoArbol));

    aux->dato = miembro;
    aux->izq = inicarbol();
    aux->der = inicarbol();

    return aux;
}

/// Buscar un nodo en un arbol

nodoArbol *buscarNodo(nodoArbol *arbol, int idMiembro)
{

    nodoArbol *rta = inicarbol();
    if (arbol != NULL)
    {
        if (idMiembro == arbol->dato.id)
        {
            rta = arbol;
        }
        else
        {

            if (idMiembro > arbol->dato.id)
            {
                // primer acercamiento al corte
                rta = buscarNodo(arbol->der, idMiembro);
            }
            else
            {
                // segundo acercamiento al corte
                rta = buscarNodo(arbol->izq, idMiembro);
            }
        }
    }
    return rta;
}

/// Insertar un nodo en un arbol

nodoArbol *insertarNodo(nodoArbol *raiz, nodoArbol *NN)
{

    if (raiz == NULL)
    {
        raiz = NN;
    }

    else
    {

        if (NN->dato > raiz->dato)
        {
            // Pongo ese = ya que el dato se va a linkear a esa parte
            raiz->der = insertarNodo(raiz->der, NN);
        }
        else
        {
            // Pongo ese = ya que el dato se va a linkear a esa parte
            raiz->izq = insertarNodo(raiz->izq, NN);
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

// Borrar Nodo

nodoArbol *borrarNodo(nodoArbol *raiz, int idMiembro)
{
    if (raiz != NULL)
    {

        if (raiz->dato.id == dato)
        {

            if (raiz->izq != NULL)
            {

                nodoArbol *masDerecha = nodoMasDerecha(raiz->izq);
                raiz->dato.id = masDerecha->dato.id;
                raiz->izq = borrarNodo(raiz->izq, masDerecha->dato.id);
            }
            else if (raiz->der != NULL)
            {
                nodoArbol *masIzquierda = nodoMasIzquierda(raiz->der);
                raiz->dato.id = masIzquierda->dato.id;
                raiz->der = borrarNodo(raiz->der, masIzquierda->dato.id);
            }

            if (esHoja(raiz) == 1)
            {
                free(raiz);
                raiz = NULL;
            }
        }
        else if (dato < raiz->dato.id)
        {
            raiz->izq = borrarNodo(raiz->izq, idMiembro);
        }

        else
        {
            raiz->der = borrarNodo(raiz->der, idMiembro);
        }
    }

    return raiz;
}

