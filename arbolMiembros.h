#ifndef ARBOLMIEMBROS_H_INCLUDED
#define ARBOLMIEMBROS_H_INCLUDED
#include "biblioteca.h"

// Estrutura Arbol

typedef struct
{

    stMiembro dato;
    struct nodoArbol *der;
    struct nodoArbol *izq;

} nodoArbol;

// Estrutura Persona

stPersona crearUnaPersona();

void mostrarUnaPersona(stPersona aux);

void mostrarUnMiembro(stMiembro aux)


// Estrutura Miembro

stMiembro crearUnMiembro();


//Estrutura Arbol

nodoArbol *inicarbol();

nodoArbol *crearNodoArbol(stMiembro miembro);

nodoArbol *buscarNodo(nodoArbol *arbol, int idMiembro);

nodoArbol *insertarNodo(nodoArbol *raiz, nodoArbol *NN);

void preorden(nodoArbol *raiz);

void inorder(nodoArbol *raiz);

void postorder(nodoArbol *raiz);

nodoArbol *borrarNodo(nodoArbol *raiz, int idMiembro);


#endif // ARBOLMIEMBROS_H_INCLUDED
