#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arbolMiembros.h"
#define MAX_DIM 26

#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"


///funciones miembro

//crear una persona
stPersona crearUnaPersona(nodoArbol * raiz)
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
    while(validarDniRepetido(raiz,aux.dni)== 1||validarCaracteresEnEnteros(aux.dni)== 0||validarRangoDNI(aux.dni)== 0);
    do
    {
        printf("Nro de telefono: ");
        fflush(stdin);
        scanf("%s", &aux.numeroDeTelefono);
    }
    while(validarNroRepetido(raiz,aux.numeroDeTelefono)== 1|| validarCaracteresEnEnteros(aux.numeroDeTelefono)== 0||validarRangoTelefono(aux.numeroDeTelefono)== 0);

    printf("Direccion: ");
    fflush(stdin);
    gets(&aux.direccion);///preguntar que tipo de validacion hacemos(solo mdp u otro tipo)

    return aux;
}

// crear un miembro
stMiembro crearUnMiembro(nodoArbol * raiz)
{
    stMiembro auxMiembro;

    auxMiembro.datosPersonales = crearUnaPersona(raiz);

    auxMiembro.estado = 1; // 1.activo o 0.dado de baja, comienza activo

    auxMiembro.validosPrestamosActivosID=0; // por el momento tiene 0 validos debido a que se inician sin ningun prestamo

    auxMiembro.saldo=0; // comienza con saldo 0 y lo podra ir modificando

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
    puts("===========================Miembro=================================");
    mostrarUnaPersona(aux.datosPersonales);


    printf("Nro de Prestamos activos....: %i \n", aux.validosPrestamosActivosID);
    printf("ID de los prestamos activos: ");
    for(int i=0; i < aux.validosPrestamosActivosID; i++)
    {
        printf("[%i] ",aux.prestamosActivosID[i]);
    }
    printf("Estado......................: %i \n", aux.estado);
    printf("Limite de prestamos.........: %i \n", aux.limitePrestamos);
    printf("Saldo en cuenta.............: %i \n", aux.saldo);
    puts("============================================================");

}

///funciones arbol

// Iniciar un arbol

nodoArbol*inicArbol()
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

// preguntar si la raiz actual es de grado uno (si tiene un solo hijo)

int esGradoUnoArbol(nodoArbol*raiz)
{
    return (raiz && ((raiz->izquierda && !raiz->derecha) || (!raiz->izquierda && raiz->derecha)));
}

//preguntar si la raiz actual esta llena (si tiene dos hijos)

int estaLlenoArbol(nodoArbol*raiz)
{
    return (raiz && raiz->izquierda && raiz->derecha);
}

//preguntar si el arbol esta vacio


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
            else
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

//contar cantidad de miembros que hay


int contarMiembrosArbol(nodoArbol* raiz)
{
    int contador=0;
    if(raiz != NULL)
    {
        contador=1;
        contador+= contarMiembrosArbol(raiz->izquierda);
        contador+= contarMiembrosArbol(raiz->derecha);
    }
    return contador;
}

///Validaciones

int validarRangoDeNombre(char nombreAux[])
{
    int flag = 0;
    int i = 0;
    int longitud = 0;

    while (nombreAux[i] != '\0')
    {
        i++;

    }
    longitud = i;


    if(longitud >= MAX_DIM||longitud < 3)
    {
        imprimirMensajeRojo("Ingrese un nombre entre 3 y 25 caracteres\n");
        flag = 1;
    }

    return flag;
}

int validarDigitosEnStrings(char nombreAux[])
{

    int flag = 0;
    int i = 0;
    char espacio = ' ';
    while(i<strlen(nombreAux)&& flag == 0)
    {

        if(isalpha(nombreAux[i])!= 0 || nombreAux[i] == espacio)
        {
            i++;
        }
        else
        {
            imprimirMensajeRojo("Error, hay datos numericos en el nombre...\n");
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
        imprimirMensajeRojo("Ingrese un DNI entre 7 y 8 digitos.\n");
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
            imprimirMensajeRojo("No puede ingresar caracteres... \n");
            flag = 0;
        }
    }

    return flag;
}
int validarRangoTelefono(char telefono[])
{

    int flag = 0;
    int tam = strlen(telefono);
    if(tam >= 8 && tam <= 10)
    {
        flag = 1;
    }
    else
    {
        imprimirMensajeRojo("Ingrese un Nro de telefono entre 8 y 10 digitos(ej:2235762462).\n");
    }
    return flag;
}
int validarEstadoMiembro(int estadoAux)
{
    int flag = 0;
    if(estadoAux <0||estadoAux >1)
    {
        imprimirMensajeRojo("Ingrese un estado valido\n");
        flag = 1;
    }

    return flag;
}

int validarDentroDeUnRango(int dato,int minimo,int maximo)
{
    if(dato < minimo ||dato >maximo)
    {
        imprimirMensajeRojo("Ingrese una opcion o rango valido\n");
        return 1;
    }

    return 0;
}
int validarLimitePrestamoMiembro(int limiteAux)
{
    int flag = 0;

    if(limiteAux<0 || limiteAux>3)
    {
        imprimirMensajeRojo("Ingrese un limite valido\n");
        flag = 1;
    }

    return flag;
}
//verifica si ya existe el DNI en otro miembro


int validarDniRepetido(nodoArbol * raiz,char dniAbuscar[])
{
    int flag = 0;

    if(raiz!= NULL)
    {


        if(strcmp(raiz->dato.datosPersonales.dni,dniAbuscar)==0)
        {
            flag = 1;
        }
        else
        {
            if(strcmp(raiz->dato.datosPersonales.dni,dniAbuscar)>0)
            {

                flag= validarDniRepetido(raiz->izquierda,dniAbuscar);
            }
            else
            {
                flag = validarDniRepetido(raiz->derecha,dniAbuscar);
            }
        }
    }

    if(flag == 1)
    {
        imprimirMensajeRojo("Ingrese un DNI que no este en la base de datos");
    }
    return flag;
}


//valida si existe un dni en el arbol

int validarSiExisteDniArbol(nodoArbol*raiz,char dniAux[])
{
       int flag = 0;

    if(raiz!= NULL)
    {


        if(strcmp(raiz->dato.datosPersonales.dni,dniAux)==0)
        {
            flag = 1;
        }
        else
        {
            if(strcmp(raiz->dato.datosPersonales.dni,dniAux)>0)
            {

                flag= validarDniRepetido(raiz->izquierda,dniAux);
            }
            else
            {
                flag = validarDniRepetido(raiz->derecha,dniAux);
            }
        }
    }

    if(flag == 1)
    {
        imprimirMensajeRojo("Ingrese un DNI que no este en la base de datos");
    }
    return flag;
}

//verifica si ya existe el nro de telefono en otro miembro


int validarNroRepetido(nodoArbol * raiz,char nroExistente[])
{
    int flag = 0;

    if(raiz!= NULL)
    {
        if(strcmpi(raiz->dato.datosPersonales.numeroDeTelefono,nroExistente)== 0)
        {
            flag = 1;
        }
        else
        {
            flag = validarNroRepetido(raiz->derecha,nroExistente);
            flag = validarNroRepetido(raiz->izquierda,nroExistente);
        }
    }
    if(flag == 1)
    {
        imprimirMensajeRojo("Ingrese un numero de telefono que no este repetido en la base de datos");
    }

    return flag;
}



///archivos

//Cuando se cree un nuevo miembro utilizo esta funcion
void cargarUnMiembroAlArchivo(stMiembro aux)
{

    FILE * buffer = fopen(ARCHIVO_MIEMBROS,"ab");
    if(buffer != NULL)
    {
        fwrite(&aux,sizeof(stMiembro),1,buffer);
        fclose(buffer);
    }
    else
    {
        imprimirMensajeRojo("Archivo de miembro vacio");
    }

}
//se pasan los datos del archivo al arbol
nodoArbol * archivoAlArbol(nodoArbol * raiz)
{
    FILE * buffer = fopen(ARCHIVO_MIEMBROS,"rb");
    stMiembro aux;

    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stMiembro),1,buffer)>0)
        {
            raiz = insertarPorDni(raiz,crearNodoArbol(aux));
        }
        fclose(buffer);

    }
    else
    {
        imprimirMensajeRojo("Archivo de miembro vacio");
    }

    return raiz;
}

//cuando finaliza el programa se encarga de todas las modificaciones que se hicieron cargarlas en el archivo y se abre en WB para que no se repitan NODOS

void arbolAlArchivo(nodoArbol * raiz)
{

    if(raiz!=NULL)
    {


        FILE * buffer = fopen(ARCHIVO_MIEMBROS,"wb");
        if(buffer != NULL)
        {
            escribirArchivoArbol(raiz,buffer);
            fclose(buffer);
        }
        else
        {
            imprimirMensajeRojo("Archivo de miembro vacio");
        }
    }



}

//se encarga de pasar la estructura del nodo al archivo

void escribirArchivoArbol(nodoArbol * raiz,FILE * buffer)
{

    if(raiz !=NULL)
    {
        fwrite(&raiz->dato,sizeof(stMiembro),1,buffer);
        escribirArchivoArbol(raiz->derecha,buffer);
        escribirArchivoArbol(raiz->izquierda,buffer);

    }

}

void mostrarArchivoDeMiembros()
{

    FILE * buffer = fopen(ARCHIVO_MIEMBROS,"rb");
    stMiembro aux;

    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stMiembro),1,buffer)>0)
        {
            mostrarUnMiembro(aux);
        }
        fclose(buffer);

    }
    else
    {
        imprimirMensajeRojo("Archivo de miembro vacio");
    }

}

///modificaciones
nodoArbol * menuDeModificaciones(nodoArbol * raiz,char dniAModificar[])
{
    int  opSw = 0,min = 1,max = 3;
    char op = 's';
    nodoArbol * aux = inicArbol();
    if(raiz!=NULL)
    {
        aux = buscarNodoPorDniArbol(raiz,dniAModificar);

        do
        {
            do
            {
                opcionesMenuActualizarMiembros();
                opSw = preguntarDatoEntero();
            }
            while(validarDentroDeUnRango(opSw,min,max)== 1);

            switch(opSw)
            {
            case 1:
                aux = actualizarUnMiembroDatosPersonales(raiz,aux); ///modificar datospersonales
                break;

            case 2:
                aux = actualizarUnMiembroCampos(aux);///modificar estado/saldo/lmite de prestamos
                break;
            case 3:
                op = 'n';
                break;
            default:
                imprimirMensajeRojo("Ingrese una opcion valida\n");
                break;
            }

        }
        while(op != 'n');
    }


    return raiz;
}

void opcionesMenuActualizarMiembros()
{
    puts("============================================================");
    printf("[1]Actualizar datos personales\n");
    printf("[2]Actualizar saldo|estado|cantidad de prestamos\n");
    printf("[3]Volver al menu de miembros\n");
    puts("============================================================");

}
nodoArbol * actualizarUnMiembroDatosPersonales(nodoArbol *raiz,nodoArbol * aux)
{

    int flag = 0,opSw = 0,min = 1,max = 6;
    char op = 's';

    do
    {
        do
        {
            opcionesActualizarUnMiembro();
            opSw = preguntarDatoEntero();
        }
        while(validarDentroDeUnRango(opSw,min,max)== 1);
        switch(opSw)
        {
        case 1:
            do
            {
                printf("Nuevo nombre: ");
                fflush(stdin);
                scanf("%s",&aux->dato.datosPersonales.nombre);
            }
            while(validarDigitosEnStrings(aux->dato.datosPersonales.nombre)== 1 || validarRangoDeNombre(aux->dato.datosPersonales.nombre)== 1);

            break;
        case 2:
            do
            {
                printf("Nuevo DNI: ");
                fflush(stdin);
                scanf("%s", &aux->dato.datosPersonales.dni);
            }
            while(validarRangoDNI(aux->dato.datosPersonales.dni)== 0 || validarCaracteresEnEnteros(aux->dato.datosPersonales.dni)== 0);
            break;
        case 3:
            do
            {
                printf("Nuevo numero de telefono: ");
                fflush(stdin);
                scanf("%s", &aux->dato.datosPersonales.numeroDeTelefono);
            }
            while(validarRangoTelefono(aux->dato.datosPersonales.numeroDeTelefono)== 0 || validarCaracteresEnEnteros(aux->dato.datosPersonales.numeroDeTelefono)== 0);
            break;
        case 4:
            printf("Nueva direccion: ");
            fflush(stdin);
            gets(&aux->dato.datosPersonales.direccion);
            break;
        case 5:
            aux->dato = crearUnMiembro(raiz);
            break;
        case 6:
            op = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;

        }

    }
    while(op !='n');
    return aux;
}

void opcionesActualizarUnMiembro()
{
    puts("============================================================");
    printf("[1]Actualizar nombre\n");
    printf("[2]Actualizar DNI\n");
    printf("[3]Actualizar Numero de telefono\n");
    printf("[4]Actualizar direccion\n");
    printf("[5]Actualizar todo el miembro\n");
    printf("[6]Volver al menu de miembros\n");
    puts("============================================================");

}

nodoArbol * actualizarUnMiembroCampos(nodoArbol * aux)
{
    int  opSw = 0,min = 1,max = 4;
    char op = 's';
    do
    {
        do
        {
            opcionesActualizarUnMiembroCampos();
            opSw = preguntarDatoEntero();
        }
        while(validarDentroDeUnRango(opSw,min,max)== 1);
        switch(opSw)
        {
        case 1:
            do
            {
                printf("Ingrese el nuevo estado: ");
                fflush(stdin);
                scanf("%i",&aux->dato.estado);
            }
            while(validarEstadoMiembro(aux->dato.estado)== 1);
            break;
        case 2:
            do
            {
                printf("Ingrese el nuevo saldo: ");
                fflush(stdin);
                scanf("%i",&aux->dato.saldo);
            }
            while(validarDentroDeUnRango(aux->dato.saldo,0,100000)== 1);
            break;
        case 3:
            do
            {
                printf("Ingrese el nuevo limite de prestamo: ");
                fflush(stdin);
                scanf("%i",&aux->dato.limitePrestamos);
            }
            while(validarLimitePrestamoMiembro(aux->dato.limitePrestamos)== 1);
            break;
        case 4:
            op = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }



    }
    while(op !='n');



    return aux;
}

void opcionesActualizarUnMiembroCampos()
{
    puts("============================================================");
    printf("[1]Actualizar estado\n");
    printf("[2]Actualizar saldo\n");
    printf("[3]Actualizar limites de prestamos \n");
    printf("[4]Volver al menu de miembros\n");
    puts("============================================================");

}

