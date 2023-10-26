#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "listaSimple.h"

///crear un miembro
stMiembro crearUnMiembro()
{
    stMiembro auxMiembro;
    puts("-----------------Ingrese los datos personales del nuevo miembro---------------------");///HACER VALIDACIONES
    printf("Nombre: ",auxMiembro.datosPersonales.nombre);
    fflush(stdin);
    scanf("%s",&auxMiembro.datosPersonales.nombre);

    printf("Nro de telefono: ",auxMiembro.datosPersonales.numeroDeTelefono);
    fflush(stdin);
    scanf("%s",&auxMiembro.datosPersonales.numeroDeTelefono);

    printf("Direccion: ");
    fflush(stdin);
    scanf("%s",&auxMiembro.datosPersonales.direccion);

    auxMiembro.historialDelPrestamo[0] = 0;

    auxMiembro.estado = 0;///arrancan siendo miembros sin prestamo

    auxMiembro.id = 0;///hacer funcion de ID automatica

    auxMiembro.prestamosActivos = 0;

    strcpy(auxMiembro.saldo,0);

    return auxMiembro;
}


void mostrarUnMiembro(stMiembro aux)
{

    printf("Nombre:|%s|\n",aux.datosPersonales.nombre);
    printf("Nro de telefono:|%s|\n",aux.datosPersonales.numeroDeTelefono);
    printf("Direccion:|%s| \n",aux.datosPersonales.direccion);
    printf("Historial de prestamos:|%i|\n",aux.historialDelPrestamo);///for para poder ver todos
    printf("Estado:|%i| \n",aux.estado);
    printf("ID:|%i|\n",aux.id);
    printf("Prestamos activos:|%i|\n",aux.prestamosActivos);
    printf("Saldo en cuenta:|%i|\n",aux.saldo);

}

///funciones basicas de listas simples
nodoSimple * inicListaSimple()
{
    return NULL;
}

