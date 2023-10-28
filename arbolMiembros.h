#ifndef ARBOLMIEMBROS_H_INCLUDED
#define ARBOLMIEMBROS_H_INCLUDED
#include "biblioteca.h"


// Estructura Persona

stPersona crearUnaPersona();

void mostrarUnaPersona(stPersona aux);

void mostrarUnMiembro(stMiembro aux);


// Estructura Miembro

stMiembro crearUnMiembro();


//Estructura Arbol

nodoArbol *inicArbol();

nodoArbol *crearNodoArbol(stMiembro miembro);

nodoArbol *buscarNodoArbol(nodoArbol *arbol, int idMiembro);

nodoArbol *insertarNodoArbol(nodoArbol *raiz, nodoArbol *NN);

void mostrarArbolPreorden(nodoArbol *raiz);

void mostrarArbolInorden(nodoArbol *raiz);

void mostrarArbolPostorden(nodoArbol *raiz);

nodoArbol *borrarNodo(nodoArbol *raiz, int idMiembro);

nodoArbol* nodoMasDerechaArbol(nodoArbol*raiz);

nodoArbol* nodoMasIzquierdaArbol(nodoArbol*raiz);

int esHoja(nodoArbol*raiz);

int esGradoUnoArbol(nodoArbol*raiz);

int estaLlenoArbol(nodoArbol*raiz);

int arbolVacio(nodoArbol*raiz);


















#endif //ARBOLMIEMBROS_H_INCLUDED
