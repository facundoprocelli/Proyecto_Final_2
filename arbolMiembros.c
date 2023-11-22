#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "arbolMiembros.h"
#define MAX_DIM 26
#define MAX_SALDO 100000


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

    auxMiembro.prestamoActivoID=0;

    auxMiembro.estado = 1; // 1.activo o 0.dado de baja, comienza activo

    auxMiembro.saldo=0; // comienza con saldo 0 y lo podra ir modificando

    //auxMiembro.limitePrestamos = 5; // predeterminado, si se penaliza puede disminuir o si paga puede aumentar

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


//    printf("Nro de Prestamos activos....: %i \n", aux.validosPrestamosActivosID);
//    printf("ID de los prestamos activos: ");
//    for(int i=0; i < aux.validosPrestamosActivosID; i++)
//    {
//        printf("[%i] ",aux.prestamosActivosID[i]);
//    }
    //printf("Limite de prestamos.........: %i \n", aux.limitePrestamos);
    printf("ID del prestamo activo......: %i \n",aux.prestamoActivoID);
    printf("Estado......................: %i \n", aux.estado);
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
        else
        {
            if(strcmp(raiz->dato.datosPersonales.dni,dniMiembro)>0)
            {
                nuevo= buscarNodoPorDniArbol(raiz->izquierda,dniMiembro);

            }
            else
            {

               nuevo= buscarNodoPorDniArbol(raiz->derecha,dniMiembro);
            }
        }

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

    if(flag == 0)
    {
        imprimirMensajeRojo("El DNI no fue encontrado en la base de datos");
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


// Actualizar datos prestamos
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
            op = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }



    }
    while(op != 'n');



    return aux;
}

void opcionesActualizarUnMiembroCampos()
{
    puts("============================================================");
    printf("[1]Actualizar estado\n");
    printf("[2]Actualizar saldo\n");
    printf("[3]Volver al menu de miembros\n");
    puts("============================================================");

}

// retornar nodos por DNI
nodoArbol* retornarNodoMiembroXDNI(nodoArbol*raiz, char dniMiembro[])
{
    nodoArbol*encontrado=inicArbol();
    if(raiz != NULL)
    {
        if(strcmp(raiz->dato.datosPersonales.dni,dniMiembro)==0)
        {
            encontrado=raiz;
        }
        else
        {
            if(strcmp(raiz->dato.datosPersonales.dni,dniMiembro)>0)
            {

                encontrado= retornarNodoMiembroXDNI(raiz->izquierda,dniMiembro);
            }
            else
            {
                encontrado= retornarNodoMiembroXDNI(raiz->derecha,dniMiembro);
            }
        }
    }
    return encontrado;
}


/// Funciones de mostrar miembros

void buscarMiembroXNombre(nodoArbol* raiz)
{
    nodoArbol* aux = inicArbol();
    char miembro[MAX_DIM];

    do
    {
        printf("Ingrese el nombre: ");
        fflush(stdin);
        gets(miembro);
    }
    while(validarDigitosEnStrings(miembro)== 1||validarRangoDeNombre(miembro)== 1);
    mostrarMiembroXNombre(raiz, miembro);


}


void mostrarMiembroXNombre(nodoArbol* raiz, char nombreBuscado[])
{


    if(raiz != NULL)
    {

        if (strcmpi(raiz->dato.datosPersonales.nombre, nombreBuscado) == 0)
        {
            mostrarUnMiembro(raiz->dato);
        }

        mostrarMiembroXNombre(raiz->derecha, nombreBuscado);
        mostrarMiembroXNombre(raiz->izquierda, nombreBuscado);


    }
}


/// Buscar y mostrar miembro X dni

void buscarMiembroXDNI(nodoArbol* raiz)
{
    nodoArbol* aux = inicArbol();
    char dni[MAX_DIM];
    int i = 0;

    do
    {

        printf("DNI: ");
        fflush(stdin);
        scanf("%s", &dni);
        i++;
    }
    while((validarSiExisteDniArbol(raiz,dni)== 0||validarCaracteresEnEnteros(dni)== 0||validarRangoDNI(dni)== 0) && i < 3);


    if ((validarSiExisteDniArbol(raiz,dni)== 1||validarCaracteresEnEnteros(dni)== 1||validarRangoDNI(dni)== 1))
    {

        aux = mostrarMiembroXDNI(raiz, dni);
    }
}


void mostrarMiembroXDNI(nodoArbol* raiz, char dniBuscado[])
{
    if(raiz != NULL)
    {

        if (strcmpi(raiz->dato.datosPersonales.dni, dniBuscado) == 0)
        {
            mostrarUnMiembro(raiz->dato);

        }
        else
        {
            if(strcmpi(raiz->dato.datosPersonales.dni, dniBuscado) > 0)
            {
                mostrarMiembroXDNI(raiz->derecha, dniBuscado);

            }
            else
            {

                mostrarMiembroXDNI(raiz->izquierda, dniBuscado);
            }
        }
    }

}

/// buscar y mostrar miembro por estado
void   buscarMiembroXEstado(nodoArbol* raiz)
{

    char dato[MAX_DIM];
    int op;
    do
    {
        menuEstadoMiembro();
        fflush(stdin);
        scanf("%s", &dato);
        op =convertirStringsDeNumerosAEntero(dato);
    }
    while ( validarCaracteresEnEnteros(dato) == 0 || (op != 1 &&  op != 0) );


    mostrarMiembroXEstado(raiz, op);

}

void menuEstadoMiembro()
{

    printf("\n[0] Miembros inactivos");
    printf("\n[1] Miembros activos");
}


void mostrarMiembroXEstado(nodoArbol* raiz, int estado)
{


    if(raiz != NULL)
    {

        if (raiz->dato.estado == estado)
        {
            mostrarUnMiembro(raiz->dato);
        }

        mostrarMiembroXEstado(raiz->derecha, estado);
        mostrarMiembroXEstado(raiz->izquierda, estado);


    }
}

/// Buscar y mostrar miembros por saldo
void menuOpcionesSaldoMiembro()
{

    printf("\n[1] $0");
    printf("\n[2] Menos de $5000");
    printf("\n[3] Entre $5000 y $10000");
    printf("\n[4] Entre $10000 y $50000");
    printf("\n[5] Mas de $50000\n");

}

void buscarMiembroXSaldo(nodoArbol* raiz)
{

    char dato[MAX_DIM];
    int opcion;

    do
    {

        menuOpcionesSaldoMiembro();
        fflush(stdin);
        scanf("%s", &dato);


    }
    while ( validarCaracteresEnEnteros(dato) == 0);

    opcion =convertirStringsDeNumerosAEntero(dato);

    switch(opcion)
    {

    case 1:
        mostrarMiembrosParaSaldo(raiz, 0, 0);
        break;
    case 2:
        mostrarMiembrosParaSaldo(raiz, 0, 5000);
        break;
    case 3:
        mostrarMiembrosParaSaldo(raiz,5000, 10000);
        break;
    case 4:
        mostrarMiembrosParaSaldo(raiz, 10000, 50000);
        break;
    case 5:
        mostrarMiembrosParaSaldo(raiz, 50000, MAX_SALDO);
        break;
    default:
        puts("\n Opcion invalida");

    }
}


void mostrarMiembrosParaSaldo(nodoArbol* raiz, int minSaldo, int maxSaldo)
{


    if (raiz != NULL)
    {

        if(raiz->dato.saldo >= minSaldo && raiz->dato.saldo <= maxSaldo)
        {

            mostrarUnMiembro(raiz->dato);
        }

        mostrarMiembrosParaSaldo(raiz->derecha, minSaldo, maxSaldo);
        mostrarMiembrosParaSaldo(raiz->izquierda, minSaldo, maxSaldo);

    }
}

/// Buscar y mostrar miembros por prestamso
void buscarMiembroXPrestamos(nodoArbol* raiz)
{


    char dato[MAX_DIM];
    int op;
    do
    {
        menuPrestadosBuscar();
        fflush(stdin);
        scanf("%s", &dato);
        op =convertirStringsDeNumerosAEntero(dato);
    }
    while ( validarCaracteresEnEnteros(dato) == 0 || (op != 1 &&  op != 2) );

    if (op == 1)
    {
        mostrarMiembrosXPrestamosActivos(raiz);
    }
    else if (op == 2)
    {
        mostrarMiembrosSinPrestamos(raiz);
    }
}


void mostrarMiembrosXPrestamosActivos(nodoArbol* raiz)
{

    if (raiz != NULL)
    {

        if(raiz->dato.prestamoActivoID != 0)
        {

            mostrarUnMiembro(raiz->dato);
        }

        mostrarMiembrosXPrestamosActivos(raiz->derecha);
        mostrarMiembrosXPrestamosActivos(raiz->izquierda);
    }

}

void mostrarMiembrosSinPrestamos(nodoArbol* raiz)
{

    if (raiz != NULL)
    {

        if(raiz->dato.prestamoActivoID == 0)
        {

            mostrarUnMiembro(raiz->dato);
        }

        mostrarMiembrosSinPrestamos(raiz->derecha);
        mostrarMiembrosSinPrestamos(raiz->izquierda);
    }

}


void menuPrestadosBuscar()
{


    printf("\n[1] Mostrar Miembros con prestamos");
    printf("\n[2] Mostrar Miembros sin prestamos");
    printf("\nIngrese un dato: ");

}





/// Modificar Mimebros Usuario


nodoArbol* cambiarNombreMiembro(nodoArbol* aux)
{

    do
    {

        printf("\nIngrese el nuevo nombre");
        printf("\nNombre: ");
        fflush(stdin);
        gets(aux->dato.datosPersonales.nombre);
    }
    while (validarDigitosEnStrings(aux->dato.datosPersonales.nombre) == 1 || validarRangoDeNombre(aux->dato.datosPersonales.nombre) == 1);


    return aux;
}


nodoArbol* cambiarNumeroDeTelefonoMiembro(nodoArbol * aux, nodoArbol* raiz)
{

    char nroTelefono[MAX_DIM];

    do
    {
        printf("\nIngrese el nuevo numero de Telefono");
        printf("\nNro de telefono: ");
        fflush(stdin);
        gets(nroTelefono);
    }
    while(validarNroRepetido(raiz, nroTelefono)== 1|| validarCaracteresEnEnteros(nroTelefono)== 0||validarRangoTelefono(nroTelefono)== 0);

    strcpy(aux->dato.datosPersonales.numeroDeTelefono, nroTelefono);


    return aux;
}



nodoArbol* cambiarSaldoDeCuentaMiembro(nodoArbol* aux)
{

    char saldo[MAX_DIM];
    int saldoNuevo = -1;
    if(aux->dato.saldo == MAX_SALDO)
    {

        imprimirMensajeRojo("\nLlego al limite de saldo\n");
    }
    else
    {
        do
        {
            printf("\nSaldo actual...: $%i",aux->dato.saldo);
            printf("\nCuanto saldo desea agregar?");
            printf("\nSaldo: ");
            fflush(stdin);
            gets(saldo);

            if (validarCaracteresEnEnteros(saldo) == 1)
            {

                saldoNuevo = convertirStringsDeNumerosAEntero(saldo);
                saldoNuevo = saldoNuevo + aux->dato.saldo;

            }

        }
        while(validarDentroDeUnRango(saldoNuevo,0,MAX_SALDO)== 1 || validarCaracteresEnEnteros(saldo) == 0);

        aux->dato.saldo = saldoNuevo;
    }
    return aux;

}



/// Cargar miembros predeterminados

nodoArbol* cargarMiembrosPredetermiandos(nodoArbol* raiz)
{

/// Miembro 1

    stPersona aux;
    stMiembro miembro;
    nodoArbol* nodo1 = inicArbol();

    strcpy(aux.nombre, "Juan");
    strcpy(aux.dni, "34897463");
    strcpy(aux.direccion, "Jovellanos");
    strcpy(aux.numeroDeTelefono, "2235672435");

    miembro.datosPersonales = aux;
    miembro.estado = 1;
    miembro.prestamoActivoID = 0;
    miembro.saldo = 70000;
    nodo1 = crearNodoArbol(miembro);

    raiz = insertarPorDni(raiz, nodo1);



/// Mimebro 2

    stPersona aux2;
    stMiembro miembro2;
    nodoArbol* nodo2 = inicArbol();

    strcpy(aux2.nombre, "Carlos");
    strcpy(aux2.dni, "4236873");
    strcpy(aux2.direccion, "Ingenieros");
    strcpy(aux2.numeroDeTelefono, "2239835273");

    miembro2.datosPersonales = aux2;
    miembro2.estado = 1;
    miembro2.prestamoActivoID = 0;
    miembro2.saldo = 5000;
    nodo2 = crearNodoArbol(miembro2);

    raiz = insertarPorDni(raiz, nodo2);



/// Mimebro 3
    stPersona aux3;
    stMiembro miembro3;
    nodoArbol* nodo3 = inicArbol();

    strcpy(aux3.nombre, "Pablo");
    strcpy(aux3.dni, "39126738");
    strcpy(aux3.direccion, "Aragon");
    strcpy(aux3.numeroDeTelefono, "2237362837");

    miembro3.datosPersonales = aux3;
    miembro3.estado = 1;
    miembro3.prestamoActivoID = 0;
    miembro3.saldo = 9000;
    nodo3 = crearNodoArbol(miembro3);

    raiz = insertarPorDni(raiz, nodo3);


    return raiz;
}



