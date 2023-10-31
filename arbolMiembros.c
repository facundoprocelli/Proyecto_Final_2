#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arbolMiembros.h"
///funciones miembro
//crear una persona
stPersona crearUnaPersona()
{
    stPersona aux;

    puts("----------------- Ingrese los datos personales del nuevo miembro ---------------------"); /// HACER VALIDACIONES
    do
    {
        printf("Nombre: ");
        fflush(stdin);
        scanf("%s",&aux.nombre);
    }
    while(validarDigitosEnStrings(aux.nombre)== 1 || validarRangoDeNombre(aux.nombre)== 1);

    do
    {
        printf("DNI: ");
        fflush(stdin);
        scanf("%s", &aux.dni);
    }
    while(validarRangoDNI(aux.dni)== 0 || validarCaracteresEnEnteros(aux.dni)== 0);
    do
    {
        printf("Nro de telefono: ");
        fflush(stdin);
        scanf("%s", &aux.numeroDeTelefono);
    }
    while(validarRangoTelefono(aux.numeroDeTelefono)== 0 || validarCaracteresEnEnteros(aux.numeroDeTelefono)== 0);

    printf("Direccion: ");
    fflush(stdin);
    gets(&aux.direccion);///preguntar que tipo de validacion hacemos(solo mdp u otro tipo)

    return aux;
}

// crear un miembro
stMiembro crearUnMiembro()
{
    stMiembro auxMiembro;

    auxMiembro.datosPersonales = crearUnaPersona();

    auxMiembro.historialDelPrestamo[0] = 0;

    auxMiembro.estado = 1; // 1.activo o 0.dado de baja

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
    puts("--------------------------Miembro-----------------------");
    mostrarUnaPersona(aux.datosPersonales);
    printf("Historial de prestamos......: %i\n", aux.historialDelPrestamo); /// for para poder ver todos
    printf("Estado......................: %i \n", aux.estado);
    printf("Prestamos activos...........: %i \n", aux.prestamosActivos);
    printf("Saldo en cuenta.............: %i \n", aux.saldo);
    puts("--------------------------------------------------------");
}

///funciones arbol

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

//insertar un dato
nodoArbol * insertarPorDni(nodoArbol * raiz,nodoArbol * nuevo)
{


    if(raiz != NULL)
    {
        if(strcmp(raiz->dato.datosPersonales.dni,nuevo->dato.datosPersonales.dni)>0)
        {

            raiz->izquierda = insertarPorDni(raiz->izquierda,nuevo);
        }
        else
        {
            raiz->derecha = insertarPorDni(raiz->derecha,nuevo);
        }

    }
    else
    {
        raiz = nuevo;
    }


    return raiz;
}


// Buscar un nodo en un arbol

nodoArbol * buscarNodoPorDniArbol(nodoArbol * raiz, char dniMiembro[])
{

    nodoArbol * nuevo = inicArbol();
    if(raiz!= NULL)
    {
        if(strcmp(raiz->dato.datosPersonales.dni,dniMiembro)== 0)
        {
            nuevo = raiz;
            nuevo->izquierda = NULL;
            nuevo->derecha = NULL;
        }
        raiz->izquierda = buscarNodoPorDniArbol(raiz->izquierda,dniMiembro);

        raiz->derecha = buscarNodoPorDniArbol(raiz->derecha,dniMiembro);
    }


    return nuevo;
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
nodoArbol* borrarUnNodoPorDni(nodoArbol* raiz, char dniMiembro[])
{
    if (raiz != NULL)
    {
        if (strcmp(raiz->dato.datosPersonales.dni, dniMiembro) == 0)
        {
            nodoArbol* aux;
            if (esHoja(raiz))
            {
                free(raiz);
                raiz = NULL;
            }
            else if (raiz->izquierda != NULL)
            {
                aux = nodoMasDerechaArbol(raiz->izquierda);
                raiz->dato = aux->dato;
                raiz->izquierda = borrarUnNodoPorDni(raiz->izquierda, aux->dato.datosPersonales.dni);
            }
            else if (raiz->derecha != NULL)
            {
                aux = nodoMasIzquierdaArbol(raiz->derecha);
                raiz->dato = aux->dato;
                raiz->derecha = borrarUnNodoPorDni(raiz->derecha, aux->dato.datosPersonales.dni);
            }
        }
        else if (strcmp(raiz->dato.datosPersonales.dni, dniMiembro) < 0)
        {
            raiz->derecha = borrarUnNodoPorDni(raiz->derecha, dniMiembro);
        }
        else
        {
            raiz->izquierda = borrarUnNodoPorDni(raiz->izquierda, dniMiembro);
        }
    }

    return raiz;
}

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
    if(raiz!= NULL)
    {
        if(raiz->derecha != NULL)
        {

            raiz = nodoMasDerechaArbol(raiz->derecha);
        }
    }
    return raiz;
}

nodoArbol* nodoMasIzquierdaArbol(nodoArbol*raiz)
{
    if(raiz!= NULL)
    {
        if(raiz->izquierda != NULL)
        {

            raiz = nodoMasIzquierdaArbol(raiz->izquierda);
        }
    }
    return raiz;
}

///Validaciones

int validarRangoDeNombre(char nombreAux[])
{
    int flag = 0;

    if(strlen(nombreAux)>MAX_DIM||strlen(nombreAux)<3)
    {
        printf("\nIngrese un nombre entre 3 y 25 caracteres\n");
        flag = 1;
    }

    return flag;
}

int validarDigitosEnStrings(char nombreAux[])
{

    int flag = 0;
    int i = 0;
    while(i<strlen(nombreAux)&& flag == 0)
    {

        if(isalpha(nombreAux[i])!= 0)
        {
            i++;
        }
        else
        {
            printf("\nError, hay datos numericos en el nombre...\n");
            flag = 1;
        }
    }
    return flag;
}

int validarRangoDNI(char dniAux[])
{

    int flag = 0;
    int length = strlen(dniAux);
    if(length >= 7 && length <= 8)
    {
        flag = 1;
    }
    else
    {
        printf("\nIngrese un DNI entre 7 y 8 digitos.\n");
    }
    return flag;
}


int validarCaracteresEnEnteros(char aux[])
{

    int flag = 1;
    for(int i = 0; i<strlen(aux) && flag == 1; i++)
    {
        if(!isdigit(aux[i]))  // Si el carácter actual no es un dígito
        {
            puts("No puede ingresar caracteres... \n");
            flag = 0;
        }
    }

    return flag;
}
int validarRangoTelefono(char telefono[])
{

    int flag = 0;
    int length = strlen(telefono);
    if(length >= 8 && length <= 10)
    {
        flag = 1;
    }
    else
    {
        printf("\nIngrese un Nro de telefono entre 8 y 10 digitos(ej:2235762462).\n");
    }
    return flag;
}




