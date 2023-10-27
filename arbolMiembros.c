#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"




///crear un miembro

stPersona crearUnaPersona()
{
    stPersona aux;

    puts("----------------- Ingrese los datos personales del nuevo miembro ---------------------");///HACER VALIDACIONES
    printf("Nombre: ");
    fflush(stdin);
    scanf("%s",&aux.nombre);

    printf("DNI: ");
    fflush(stdin);
    scanf("%s",&aux.dni);

    printf("Nro de telefono: ");
    fflush(stdin);
    scanf("%s",&aux.numeroDeTelefono);

    printf("Direccion: ");
    fflush(stdin);
    scanf("%s",&aux.direccion);

    return aux;
}


stMiembro crearUnMiembro()
{
    stMiembro auxMiembro;

    auxMiembro.datosPersonales=crearUnaPersona();

    auxMiembro.historialDelPrestamo[0] = 0;

    auxMiembro.estado = 0; //activo o dado de baja

    auxMiembro.id = 0;///hacer funcion de ID automatica

    auxMiembro.prestamosActivos = 0;

    strcpy(auxMiembro.saldo,0);

    auxMiembro.limitePrestamos= 5; //predeterminado

    return auxMiembro;
}


void mostrarUnaPersona(stPersona aux)
{
    printf("Nombre: |%s|\n",aux.nombre);
    printf("Dni: |%s| \n",aux.dni);
    printf("Nro de telefono: |%s|\n",aux.numeroDeTelefono);
    printf("Direccion: |%s| \n",aux.direccion);
}


void mostrarUnMiembro(stMiembro aux)
{
    mostrarUnaPersona(aux.datosPersonales);
    printf("Historial de prestamos: |%i|\n",aux.historialDelPrestamo);///for para poder ver todos
    printf("Estado: |%i| \n",aux.estado);
    printf("ID: |%i|\n",aux.id);
    printf("Prestamos activos: |%i|\n",aux.prestamosActivos);
    printf("Saldo en cuenta: |%i|\n",aux.saldo);

}
