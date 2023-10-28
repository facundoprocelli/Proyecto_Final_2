#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arbolMiembros.h"



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

    auxMiembro.estado = 1; // 1.activo o 0.dado de baja

    auxMiembro.idMiembro = 0; /// hacer funcion de ID automatica

    auxMiembro.prestamosActivos = 0;

    auxMiembro.saldo=0;

    auxMiembro.limitePrestamos = 5; // predeterminado, si se penaliza puede disminuir o si paga puede aumentar

    return auxMiembro;
}

//mostrar una persona

void mostrarUnaPersona(stPersona aux)
{
    printf("Nombre...............: %s \n", aux.nombre);
    printf("Dni..................: %s \n", aux.dni);
    printf("Nro de telefono......: %s \n", aux.numeroDeTelefono);
    printf("Direccion............: %s \n", aux.direccion);
}

//mostrar un miembro

void mostrarUnMiembro(stMiembro aux)
{
    printf("ID..........................: %i\n", aux.idMiembro);
    mostrarUnaPersona(aux.datosPersonales);
    printf("Historial de prestamos......: %i\n", aux.historialDelPrestamo); /// for para poder ver todos
    printf("Estado......................: %i \n", aux.estado);
    printf("Prestamos activos...........: %i \n", aux.prestamosActivos);
    printf("Saldo en cuenta.............: %i \n", aux.saldo);
}

// Iniciar un arbol

nodoArbol *inicArbol()
{
    return NULL;
}

// Crear el nodo del arbol

nodoArbol *crearNodoArbol(stMiembro miembro)
{

    nodoArbol *aux = (nodoArbol *)malloc(sizeof(nodoArbol));

    aux->dato = miembro;
    aux->izquierda = inicArbol();
    aux->derecha = inicArbol();

    return aux;
}

// Buscar un nodo en un arbol

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
                rta = buscarNodoArbol(raiz->derecha, idBuscar);
            }
            else
            {
                // segundo acercamiento al corte
                rta = buscarNodoArbol(raiz->izquierda, idBuscar);
            }
        }
    }

    if(rta == NULL)
    {
        puts("Miembro no encontrado");
    }

    return rta;
}

// Insertar un nodo en un arbol

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
            raiz->derecha = insertarNodoArbol(raiz->derecha, NuevoNodo);
        }
        else
        {
            // Pongo ese = ya que el dato se va a linkear a esa parte
            raiz->izquierda = insertarNodoArbol(raiz->izquierda, NuevoNodo);
        }
    }

    return raiz;
}

//mostrar arbol

void mostrarArbolPreorden(nodoArbol *raiz)
{

    if (raiz != NULL)
    {

        mostrarUnMiembro(raiz->dato);
        mostrarArbolPreorden(raiz->izquierda);
        mostrarArbolPreorden(raiz->derecha);
    }
}

void mostrarArbolInorden(nodoArbol *raiz)
{

    if (raiz != NULL)
    {

        mostrarArbolInorden(raiz->izquierda);
        mostrarUnMiembro(raiz->dato);
        mostrarArbolInorden(raiz->derecha);
    }
}

void mostrarArbolPostorden(nodoArbol *raiz)
{

    if (raiz != NULL)
    {

        mostrarArbolPostorden(raiz->izquierda);
        mostrarArbolPostorden(raiz->derecha);
        mostrarUnMiembro(raiz->dato);
    }
}

// preguntar si la raiz actual es una hoja

int esHoja(nodoArbol*raiz)
{
    return (raiz && !raiz->izquierda && !raiz->derecha);
}

int esGradoUnoArbol(nodoArbol*raiz)
{
    return (raiz && ((raiz->izquierda && !raiz->derecha) || (!raiz->izquierda && raiz->derecha)));
}

int estaLlenoArbol(nodoArbol*raiz)
{
    return (raiz && raiz->izquierda && raiz->derecha);
}

// Borrar Nodo
int arbolVacio(nodoArbol*raiz)
{
    if(raiz != NULL)
    {
        return 0;
    }
    else
    {
        puts("Arbol Vacio");
        return 1;
    }
}

nodoArbol* nodoMasDerechaArbol(nodoArbol*raiz)
{
    while(raiz->derecha != NULL)
    {
        raiz=raiz->derecha;
    }
    return raiz;
}

nodoArbol* nodoMasIzquierdaArbol(nodoArbol*raiz)
{
    while(raiz->izquierda != NULL)
    {
        raiz=raiz->izquierda;
    }
    return raiz;
}

nodoArbol *borrarNodoArbol(nodoArbol *raiz, int idBuscar)
{
    if (!arbolVacio(raiz))
    {
        if(raiz->dato.idMiembro == idBuscar)
        {
            nodoArbol*aux=raiz;
            if(estaLlenoArbol(raiz))
            {
                raiz->dato= nodoMasIzquierdaArbol(raiz->izquierda)->dato;
                raiz->izquierda=borrarNodoArbol(raiz->izquierda, raiz->dato.idMiembro);
            }
            else
            {
                if(esHoja(raiz))
                {
                    raiz=NULL;
                }
                else
                {
                    if(raiz->izquierda != NULL)
                    {
                        raiz= raiz->izquierda;
                    }
                    else
                    {
                        raiz=raiz->derecha;
                    }
                }
            }
            free(aux);

        }
        else if (idBuscar < raiz->dato.idMiembro)
        {
            raiz->izquierda = borrarNodoArbol(raiz->izquierda, idBuscar);
        }
        else
        {
            raiz->derecha = borrarNodoArbol(raiz->derecha, idBuscar);
        }
    }

    return raiz;
}
