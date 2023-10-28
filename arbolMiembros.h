#ifndef ARBOLMIEMBROS_H_INCLUDED
#define ARBOLMIEMBROS_H_INCLUDED
#include "biblioteca.h"


// Estructura Persona

stPersona crearUnaPersona();

void mostrarUnaPersona(stPersona aux);

void mostrarUnMiembro(stMiembro aux)


// Estructura Miembro

stMiembro crearUnMiembro();


//Estructura Arbol

nodoArbol *inicArbol();

nodoArbol *crearNodoArbol(stMiembro miembro);

nodoArbol *buscarNodo(nodoArbol *arbol, int idMiembro);

nodoArbol *insertarNodo(nodoArbol *raiz, nodoArbol *NN);

void preorden(nodoArbol *raiz);

void inorder(nodoArbol *raiz);

void postorder(nodoArbol *raiz);

nodoArbol *borrarNodo(nodoArbol *raiz, int idMiembro);

nodoArbol* nodoMasDerecha(nodoArbol*raiz);

nodoArbol* nodoMasIzquierda(nodoArbol*raiz);

int esHoja(nodoArbol*raiz);

int esGradoUno(nodoArbol*raiz);

int estaLleno(nodoArbol*raiz);

int arbolVacio(nodoArbol*raiz);




// cambiar el prottipado













#endif //ARBOLMIEMBROS_H_INCLUDED
