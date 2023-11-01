#ifndef FILARESERVAS_H_INCLUDED
#define FILARESERVAS_H_INCLUDED
#define MAX_DIM 26
typedef struct{

    struct nodoDoble*primero;
    struct nodoDoble*ultimo;

} filaReservas;

void inicFila(filaReservas*reservas);

#endif // FILARESERVAS_H_INCLUDED
