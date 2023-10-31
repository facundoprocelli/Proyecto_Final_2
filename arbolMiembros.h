#ifndef ARBOLMIEMBROS_H_INCLUDED
#define ARBOLMIEMBROS_H_INCLUDED
#include "biblioteca.h"


// Estructura Persona

stPersona crearUnaPersona();
void mostrarUnaPersona(stPersona aux);
void mostrarUnMiembro(stMiembro aux);

///Estructura Miembro

stMiembro crearUnMiembro();


///Estructura Arbol
//basicas
nodoArbol *inicArbol();
nodoArbol *crearNodoArbol(stMiembro miembro);

//busqueda y muestra
nodoArbol * buscarNodoPorDniArbol(nodoArbol * raiz, char dniMiembro[]);

void mostrarArbolPreorden(nodoArbol *raiz);
void mostrarArbolInorden(nodoArbol *raiz);
void mostrarArbolPostorden(nodoArbol *raiz);

//insertar y borrar
nodoArbol * insertarPorDni(nodoArbol * raiz,nodoArbol * nuevo);
nodoArbol * borrarUnNodoPorDni(nodoArbol * raiz,char dniMiembro[]);

nodoArbol* nodoMasDerechaArbol(nodoArbol*raiz);
nodoArbol* nodoMasIzquierdaArbol(nodoArbol*raiz);


int esHoja(nodoArbol*raiz);
int esGradoUnoArbol(nodoArbol*raiz);
int estaLlenoArbol(nodoArbol*raiz);
int arbolVacio(nodoArbol*raiz);

///validaciones
int validarRangoDeNombre(char nombreAux[]);///tamaño del nombre
int validarDigitosEnStrings(char nombreAux[]);///Que no se encuentren numeros en un nombre
int validarRangoDNI(char dniAux[]);
int validarCaracteresEnEnteros(char aux[]);
int validarRangoTelefono(char telefono[]);

///archivos
void cargarUnMiembroAlArchivo(stMiembro aux);
nodoArbol * archivoAlArbol(nodoArbol * raiz);
void mostrarArchivoDeMiembros();










#endif //ARBOLMIEMBROS_H_INCLUDED
