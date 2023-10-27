#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"



//crear una persona

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

//crear un miembro

stMiembro crearUnMiembro()
{
    stMiembro auxMiembro;

    auxMiembro.datosPersonales=crearUnaPersona();

    auxMiembro.idMiembro = 0;///hacer funcion de ID automatica

    auxMiembro.historialDelPrestamo[0] = 0;

    auxMiembro.estado = 0; //activo o dado de baja

    auxMiembro.prestamosActivos = 0;

    auxMiembro.limitePrestamos= 5; //predeterminado

    strcpy(auxMiembro.saldo,0);

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
    printf("ID: |%i|\n",aux.idMiembro);
    printf("Prestamos activos: |%i|\n",aux.prestamosActivos);
    printf("Saldo en cuenta: |%i|\n",aux.saldo);
    puts("-----------------------------------------------");
}
