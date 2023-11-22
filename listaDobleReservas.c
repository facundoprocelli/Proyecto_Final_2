#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaDobleReservas.h"

#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"

///funciones estructura prestamo

stPrestamo crearUnPrestamo(char dniUsuarioPrestadoAux[],int idLibroPrestado, char generoDelPrestamo[])
{
    stPrestamo aux;
    int duracionVencimiento = 0;
    aux.idPrestamo= retornarUltimoIDPrestamo() +1;
    strcpy(aux.dniUsuarioPrestado,dniUsuarioPrestadoAux);
    strcpy(aux.generoEstanteria,generoDelPrestamo);
    aux.idLibro=idLibroPrestado;
    aux.estado = 1;


    //funciones para calcular inicio y fin del prestamo(automatico)
    time_t tiempoActual;
    time(&tiempoActual);
    struct tm *infoTiempo = localtime(&tiempoActual);
    asignarTiempo(&aux.inicioPrestamo,infoTiempo);



    do
    {
        printf("Ingrese de cuantos dias quiere el prestamo: ");
        fflush(stdin);
        scanf("%i",&duracionVencimiento);
    }
    while(validarDias(duracionVencimiento)== 1);

    int precio = duracionVencimiento * 1000;
    char precioPrestamo[MAX_DIM];

    sprintf(precioPrestamo, "%d", precio);



    strcpy(aux.precioPrestamo, precioPrestamo);
    printf("El precio del prestamos es: $%s\n", aux.precioPrestamo);


    calcularVencimiento(&aux.vencimientoPrestamo,aux.inicioPrestamo,duracionVencimiento);
    return aux;
}


int validarDias(int dias)
{
    int flag = 0;
    if(dias< 1 || dias> 31)
    {
        flag = 1;
        imprimirMensajeRojo("Ingrese un dia entre 1 y 31");
    }

    return flag;
}



void asignarTiempo(stFecha * aux,struct tm * info_tiempo)
{
    aux->diaTiempo = info_tiempo->tm_mday;
    aux->mesTiempo = info_tiempo->tm_mon+1;
    aux->anioTiempo = info_tiempo->tm_year+1900;
}
void calcularVencimiento(stFecha *vencimiento, stFecha inicio,int duracionPrestamo)
{
    // Convertir la fecha de inicio a una estructura de tiempo
    struct tm info_inicio = {0};
    info_inicio.tm_mday = inicio.diaTiempo;
    info_inicio.tm_mon = inicio.mesTiempo - 1;  // Restar 1 al mes
    info_inicio.tm_year = inicio.anioTiempo - 1900;  // Restar 1900 al año

    // Calcular el tiempo en segundos para 7 días
    time_t duracionVencimiento = duracionPrestamo * 24 * 60 * 60;

    // Sumar el tiempo en segundos a la fecha de inicio
    time_t tiempo_vencimiento = mktime(&info_inicio) + duracionVencimiento;

    // Convertir el tiempo de vencimiento a una estructura de tiempo local
    struct tm *info_vencimiento = localtime(&tiempo_vencimiento);

    // Asignar los valores de la estructura de tiempo local a la fecha de vencimiento
    vencimiento->diaTiempo = info_vencimiento->tm_mday;
    vencimiento->mesTiempo = info_vencimiento->tm_mon + 1;  // Sumar 1 al mes
    vencimiento->anioTiempo = info_vencimiento->tm_year + 1900;
}



//mostrar una fecha
void mostrarUnaFecha(stFecha aux)
{
    printf("Fecha: %02d-%02d-%04d \n", aux.diaTiempo, aux.mesTiempo, aux.anioTiempo);
}

//generar multas por retraso
int generarMulta(stFecha fechaFinDelPrestamo)///falta terminar
{
    int multa = 0;
    time_t tiempoActual;
    time(&tiempoActual);
    struct tm *infoTiempo = localtime(&tiempoActual);///me da la hora actual del sistema
//    fechaFinDelPrestamo.diaTiempo = 9;
//    fechaFinDelPrestamo.mesTiempo = infoTiempo->tm_mon;     //esto evalua sin funciona una multa
//    fechaFinDelPrestamo.anioTiempo = 2023;

    if (infoTiempo->tm_mon == fechaFinDelPrestamo.mesTiempo)
    {
        if(infoTiempo->tm_mday >fechaFinDelPrestamo.diaTiempo)
        {
            multa = rand() % 5000 + 100;
        }
    }
    else if(infoTiempo->tm_mon > fechaFinDelPrestamo.mesTiempo)
    {
        multa = rand() % 5000 + 100;
    }

    return multa;
}



//mostra un prestamo
void mostrarUnPrestamo(stPrestamo aux)
{
    puts("---------------------Prestamo---------------------");
    printf("[ID Prestamo]...............: %i \n",aux.idPrestamo);
    printf("[DNI del miembro]...........: %s \n",aux.dniUsuarioPrestado);
    printf("[Precio]....................: %s \n",aux.precioPrestamo);
    printf("[Genero]....................: %s \n",aux.generoEstanteria);
    printf("[Estado]....................: %i \n",aux.estado);
    printf(".......[Inicio del prestamo].......\n");
    mostrarUnaFecha(aux.inicioPrestamo);
    printf("....[Vencimiento del prestamo].... \n");
    mostrarUnaFecha(aux.vencimientoPrestamo);
    puts("--------------------------------------------------");
}

///funciones lista doble

// iniciar lista doble
nodoDoble*inicListaDoble()
{
    return NULL;
}

void mostrarListaDoble(nodoDoble*listaDoble)
{
    while(listaDoble != NULL)
    {
        mostrarUnPrestamo(listaDoble->datoPrestamo);
        listaDoble=listaDoble->siguiente;
    }
}

//crear nodo doble

nodoDoble*crearNodoDoble(stPrestamo aux)
{
    nodoDoble*nuevoNodo=(nodoDoble*)malloc(sizeof(nodoDoble));
    nuevoNodo->datoPrestamo=aux;
    nuevoNodo->anterior=NULL;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

// agregar al principio doble

nodoDoble*agregarAlPpioDoble(nodoDoble*listaDoble, nodoDoble*nuevoNodo)
{
    nuevoNodo->siguiente=listaDoble;
    if(listaDoble != NULL)
    {
        listaDoble->anterior=nuevoNodo;
    }
    return nuevoNodo;
}

//buscar ultimo nodo doble

nodoDoble*buscarUltimoNodoDoble(nodoDoble*listaDoble)
{
    if(listaDoble != NULL)
    {
        while(listaDoble->siguiente != NULL)
        {
            listaDoble=listaDoble->siguiente;
        }
    }
    return listaDoble; // si la lista esta vacia me retorna NULL
}

// agregar al final doble
nodoDoble*agregarAlFinalDoble(nodoDoble*listaDoble,nodoDoble*nuevoNodo)
{
    if(listaDoble != NULL)
    {
        nodoDoble*aux=buscarUltimoNodoDoble(listaDoble);

        aux->siguiente=nuevoNodo;

        nuevoNodo->anterior=aux;
    }
    else
    {
        listaDoble= nuevoNodo;
    }
    return listaDoble;
}

//borrar el primer nodo de la lista doble

void borrarPrimerNodoDoble(nodoDoble**listaDoble)
{
    nodoDoble*liberar;
    nodoDoble*aux=*listaDoble;

    if(aux != NULL)
    {
        liberar=aux;
        *listaDoble=aux->siguiente;
        free(liberar);
    }

}



///validaciones

int validarPrecioPrestamo(char aux[])
{
    int flag=0;
    int dato=convertirStringsDeNumerosAEntero(aux); // funcion que convierte numeros en un string al tipo de dato entero
    int min=0,max=10000;


    if(dato < min || dato > max)
    {
        imprimirMensajeRojo("Ingrese un precio valido \n");
        flag=1;
    }

    return flag;
}

///funciones archivo

int retornarUltimoIDPrestamo() //vamos a tener que modificarla, y buscar el ultimo id de otra forma
{
    FILE*buffer=fopen(ARCHIVO_PRESTAMOS,"rb");
    stPrestamo aux;
    int ultId=0;
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stPrestamo),1,buffer) > 0)
        {
            if(aux.idPrestamo > ultId)
            {
                ultId=aux.idPrestamo;
            }
        }
    }
    return ultId;
}
