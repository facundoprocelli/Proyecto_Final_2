#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaSimpleLibros.h"
#define MAX_DIM 26
#define MAX_GEN 5
#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"

///funciones estructura libro

stLibro crearUnLibro(estanteria arregloEstanterias[])
{
    stLibro aux;

    puts("--------------- Ingrese los datos del nuevo libro ----------------------");
    do
    {
        printf("Nombre: ");
        fflush(stdin);
        gets(aux.nombreDeLibro);
    }
    while(validarDigitosEnStrings(aux.nombreDeLibro)== 1||validarRangoDeNombre(aux.nombreDeLibro)== 1);///reutilizo la funcion de validarDigitos y validarRangoNombre que hice en arboles

    printf("Genero: \n");
    validarGenero(aux.generoLibro);

    do
    {
        printf("Autor: ");
        fflush(stdin);
        gets(aux.autorLibro);
    }
    while(validarDigitosEnStrings(aux.autorLibro)== 1||validarRangoDeNombre(aux.autorLibro)==1);
    aux.estado=1; // 0.dado de baja, 1.disponible, 2. prestado

    aux.idLibro=retornarUltimoIDLibro(arregloEstanterias)+ 1;

    inicFila(&aux.reservasLibro);

    aux.vecesPrestadoLibro=0;

    do
    {
        printf("Copias: ");
        fflush(stdin);
        gets(aux.cantidadDeCopias);
    }
    while(validarCaracteresEnEnteros(aux.cantidadDeCopias)== 0 || (aux.cantidadDeCopias < 100));

    printf("Descripcion: Para ingresar palabras clave recurde usar el caracter # antes de la palabra, sin ");
    fflush(stdin);
    gets(aux.descripcionLibro);

    return aux;
}


int retornarUltimoIDLibro(estanteria arregloEstanterias[])
{
    int max= 0, aux= 0;
    for(int i=0; i < 5; i++)
    {
        aux=retornarIDMasGrandeEnLista(arregloEstanterias[i].listaLibro);
        if(aux > max)
        {
            max=aux;
        }

    }
    return max;
}

int retornarIDMasGrandeEnLista(nodoSimple*listaSimple)
{
    int max=0;
    while(listaSimple != NULL)
    {
        if(listaSimple->datoLibro.idLibro > max)
        {
            max=listaSimple->datoLibro.idLibro;
        }
        listaSimple=listaSimple->siguiente;
    }
    return max;
}



//mostrar un libro
void mostrarUnLibro(stLibro aux)
{
    puts("--------------------LIBRO:----------------");
    printf("ID Libro..............: %i \n",aux.idLibro);
    printf("Nombre................: %s \n",aux.nombreDeLibro);
    printf("Genero................: %s \n",aux.generoLibro);
    printf("Autor.................: %s \n",aux.autorLibro);
    printf("Estado................: %i \n",aux.estado);
    printf("Veces prestado........: %i \n",aux.vecesPrestadoLibro);
    printf("Descripcion...........: %s \n", aux.descripcionLibro);
    printf("Copias................: %s \n", aux.cantidadDeCopias);
    ///printf("",aux.reservasLibro); ///mostrar fila de reservas de este libro
    puts("---------------------------------------------");
}


/// lista simple de libros

nodoSimple*inicListaSimple()
{
    return NULL;
}

//mostrar toda la lista simple
void mostrarListaSimple(nodoSimple*listaSimple)
{
    while(listaSimple != NULL)
    {
        mostrarUnLibro(listaSimple->datoLibro);
        listaSimple=listaSimple->siguiente;
    }
}

//crear un nodo simple

nodoSimple*crearNodoSimple(stLibro aux)
{
    nodoSimple*nuevoNodo=(nodoSimple*)malloc(sizeof(nodoSimple));
    nuevoNodo->datoLibro=aux;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

//agregar al principio de la lista simple

nodoSimple*agregarAlPpioSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo)
{
    nuevoNodo->siguiente=listaSimple;
    return nuevoNodo;
}

//agregar al final de la lista simple

nodoSimple*agregarAlFinalSimple(nodoSimple*listaSimple,nodoSimple*nuevoNodo)
{
    if(listaSimple != NULL)
    {
        nodoSimple*seg=listaSimple;
        while(seg->siguiente != NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevoNodo;
    }
    else
    {
        listaSimple=nuevoNodo;
    }
    return listaSimple;
}



//verificar si existe el libro

int verificarSiExisteLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[])
{
    int flag=0;

    while(listaSimple != NULL && strcmpi(listaSimple->datoLibro.nombreDeLibro,nombreBuscar) != 0)
    {
        listaSimple=listaSimple->siguiente;
    }
    if(listaSimple == NULL)
    {
        flag=1;
    }
    return flag;
}

//funciones de buscar para retornar un nodo

nodoSimple*retornarNodoSimpleXid(nodoSimple*listaSimple,int idBuscar)
{
    nodoSimple*aux=NULL;
    while(listaSimple != NULL && listaSimple->datoLibro.idLibro != idBuscar)
    {
        listaSimple=listaSimple->siguiente;
    }
    if(listaSimple == NULL) // si llegue al final no encontre el dato
    {
        puts("Libro no encontrado");
    }
    else // si no es null entonces se corto el bucle porque encontre el dato
    {
        aux=listaSimple;
    }
    return aux;
}


nodoSimple* retornarNodosLibroXAutor(nodoSimple* listaSimple, char autorBuscar[])
{

    nodoSimple* aux = inicListaSimple();


    while (listaSimple != NULL)
    {

        if (strcmpi(listaSimple->datoLibro.autorLibro, autorBuscar) == 0)
        {

            nodoSimple* NN = crearNodoSimple(listaSimple->datoLibro);
            aux = agregarAlFinalSimple(aux, NN );
        }

        listaSimple = listaSimple->siguiente;
    }

    return aux;
}


///Retorna los nodos que coincidan con una palabra clave
nodoSimple* retornarNodosLibroXClave(nodoSimple* listaSimple, char clave[])
{

    nodoSimple* aux = inicListaSimple();
    char claveConDelimitador[MAX_DIM];
    strcpy(claveConDelimitador, "#");
    strcat(claveConDelimitador, clave);

    printf("%s", claveConDelimitador);

    while (listaSimple != NULL)
    {


        if (strstr(listaSimple->datoLibro.descripcionLibro, clave) == 0)
        {

            nodoSimple* NN = crearNodoSimple(listaSimple->datoLibro);
            aux = agregarAlFinalSimple(aux, NN );
        }
        listaSimple = listaSimple->siguiente;
    }
    return aux;
}

nodoSimple* retornarNodosLibroXTitulo(nodoSimple* listaSimple, char tituloBuscar[])
{

    nodoSimple* aux = inicListaSimple();


    while (listaSimple != NULL)
    {

        if (strcmpi(listaSimple->datoLibro.nombreDeLibro, tituloBuscar) == 0)
        {

            nodoSimple* NN = crearNodoSimple(listaSimple->datoLibro);
            aux = agregarAlFinalSimple(aux, NN );
        }

        listaSimple = listaSimple->siguiente;
    }

    return aux;
}


nodoSimple* retornarNodosLibroXEstado(nodoSimple* listaSimple, int estado)
{

    nodoSimple* aux = inicListaSimple();


    while (listaSimple != NULL)
    {

        if (listaSimple->datoLibro.estado == estado)
        {
            nodoSimple* NN = crearNodoSimple(listaSimple->datoLibro);
            aux = agregarAlFinalSimple(aux, NN);

        }
        listaSimple = listaSimple->siguiente;
    }

    return aux;
}








//Funciones de modificar Libros




nodoSimple* modificarNombreLibro(nodoSimple* aux)
{

    do
    {
        printf("Ingrese el nuevo nombre ");
        printf("Nombre: ");
        fflush(stdin);
        gets(aux->datoLibro.nombreDeLibro);
    }
    while(validarDigitosEnStrings(aux->datoLibro.nombreDeLibro)== 1||validarRangoDeNombre(aux->datoLibro.nombreDeLibro)== 1);///reutilizo la funcion de validarDigitos y validarRangoNombre que hice en arboles


    return aux;
}

nodoSimple* modificarCantidadDeCopias(nodoSimple* aux)
{

    do
    {
        printf("Ingrese la nueva cantiadad de copias ");
        printf("Copias: ");
        fflush(stdin);
        gets(aux->datoLibro.cantidadDeCopias);
    }
    while(validarCaracteresEnEnteros(aux->datoLibro.cantidadDeCopias)== 0|| aux->datoLibro.cantidadDeCopias < 100);



    return aux;
}

nodoSimple* modificarGeneroLibro(nodoSimple* aux)
{

    printf("Seleccione el nuevo Genero ");
    printf("Genero: \n");
    validarGenero(aux->datoLibro.generoLibro);

    return aux;
}


nodoSimple* modificarAutorLibro(nodoSimple* aux)
{

    do
    {
        printf("Ingrese el nuevo Autor ");
        printf("Autor: ");
        fflush(stdin);
        gets(aux->datoLibro.autorLibro);
    }
    while(validarDigitosEnStrings(aux->datoLibro.autorLibro)== 1||validarRangoDeNombre(aux->datoLibro.autorLibro)==1);

    return aux;
}


nodoSimple* modificarDescripcionLibro(nodoSimple* aux)
{


    printf("Desripcion: ");
    fflush(stdin);
    gets(aux->datoLibro.descripcionLibro);


    return aux;
}


nodoSimple* modificarEstadoLibro(nodoSimple* aux)
{


    char opSw[1];
    int op = 0;
    menuEstados();
    do
    {
        op = preguntarDatoEntero();
    }
    while (op != 0 && op != 1  );

    aux->datoLibro.estado = op;



    return aux;
}

void menuEstados()
{

    printf("Seleccione una opcion\n");
    printf("[0] Dar de Baja\n");
    printf("[1] Dar de Alta\n");

}

//funciones de buscar para retornar un libro

stLibro retornarLibroXid(nodoSimple*listaSimple,int idBuscar)
{
    stLibro aux;

    while(listaSimple != NULL && listaSimple->datoLibro.idLibro != idBuscar)
    {
        listaSimple=listaSimple->siguiente;
    }
    if(listaSimple != NULL) // si no es null entonces se corto el bucle porque encontre el dato
    {
        aux=listaSimple->datoLibro;
    }
    else // si llegue al final no encontre el dato
    {

        puts("Libro no encontrado");
    }
    return aux;
}

stLibro retornarLibroXNombre(nodoSimple*listaSimple,char nombreBuscar[])
{
    stLibro aux;
    while(listaSimple != NULL && strcmpi(listaSimple->datoLibro.nombreDeLibro,nombreBuscar) != 0)
    {
        listaSimple= listaSimple->siguiente;
    }
    if(listaSimple != NULL)
    {
        aux=listaSimple->datoLibro;
    }
    else
    {
        puts("Libro no encontrado");
    }
    return aux;
}



stLibro retornarLibroXAutor(nodoSimple*listaSimple,char autorBuscar[])
{
    stLibro aux;
    while(listaSimple != NULL && strcmpi(listaSimple->datoLibro.autorLibro,autorBuscar) != 0)
    {
        listaSimple= listaSimple->siguiente;
    }
    if(listaSimple != NULL)
    {
        aux=listaSimple->datoLibro;
    }
    else
    {
        puts("Libro no encontrado");
    }
    return aux;
}




///validaciones


void validarGenero(char auxGenero[])
{
    char opSw[1];
    int flag = 0;
    int op;
    do
    {
        ///----------Se puede hacer en una funcion aparte----------------
        do
        {
            opcionesGenero();
            printf("Ingrese una opcion: ");
            fflush(stdin);
            scanf("%s", &opSw);
        }
        while (validarCaracteresEnEnteros(opSw) == 0);

        op = convertirStringsDeNumerosAEntero(opSw);

        switch(op)
        {
        case 1:
            strcpy(auxGenero,"Fantasia");
            flag = 1;
            break;
        case 2:
            strcpy(auxGenero,"Ciencia Ficcion");
            flag = 1;
            break;
        case 3:
            strcpy(auxGenero,"Romance");
            flag = 1;
            break;
        case 4:
            strcpy(auxGenero,"Terror");
            flag = 1;
            break;
        case 5:
            strcpy(auxGenero,"Aventura");
            flag = 1;
            break;
        default:
            printf("\nIngrese una opcion valida\n");
            flag = 0;
            break;


        }

    }

    while(flag == 0);

}

//Opciones del genero de un libro

void opcionesGenero()
{
    printf("[1]Fantasia\n");
    printf("[2]Ciencia Ficcion\n");
    printf("[3]Romance\n");
    printf("[4]Terror\n");
    printf("[5]Aventura\n");

}

///archivos

// cargar un libro a un archivo

void cargarUnLibroAlArchivo(stLibro aux) //cuando se cree un nuevo libro se utiliza esta funcion
{
    FILE*buffer=fopen(ARCHIVO_LIBROS,"ab");
    if(buffer != NULL)
    {
        fwrite(&aux,sizeof(stLibro),1,buffer);
        fclose(buffer);
    }
    else
    {
        puts("Archivo vacio");
    }
}


// mostrar todo el archivo de libros
void mostrarArchivoLibros()
{
    FILE*buffer=fopen(ARCHIVO_LIBROS,"rb");
    stLibro aux;
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stLibro),1,buffer)>0)
        {
            mostrarUnLibro(aux);
        }
        fclose(buffer);
    }
    else
    {
        puts("Archivo vacio");
    }
}

//cargar un par de libros para comenzar

void cargarLibrosPredeterminados()
{

    FILE* archi = fopen(ARCHIVO_LIBROS, "wb");

    stLibro libro1;
    libro1.idLibro = 1;
    strcpy(libro1.autorLibro, "John Jackson Miller");
    strcpy(libro1.generoLibro, "Ciencia Ficci�n");
    strcpy(libro1.nombreDeLibro, "Kenobi");
    strcpy(libro1.descripcionLibro, "Una historia que contribuye a la caracterizaci�n general de Obi-Wan Kenobi.");
    libro1.estado = 1;
    libro1.vecesPrestadoLibro = 0;


    fwrite(&libro1, sizeof(stLibro), 1, archi);

    stLibro libro2;
    libro2.idLibro = 2;
    strcpy(libro2.autorLibro, "Makoto Mizobuchi");
    strcpy(libro2.generoLibro, "Aventura");
    strcpy(libro2.nombreDeLibro, "Pok�mon Mystery Dungeon: Ginji's Rescue Team");
    strcpy(libro2.descripcionLibro, "Una emocionante historia de aventuras en el universo de Pok�mon.");
    libro2.estado = 1;
    libro2.vecesPrestadoLibro = 0;


    fwrite(&libro2, sizeof(stLibro), 1, archi);


    stLibro libro3;
    libro3.idLibro = 3;
    strcpy(libro3.autorLibro, "J.K. Rowling");
    strcpy(libro3.generoLibro, "Fantas�a");
    strcpy(libro3.nombreDeLibro, "Harry Potter and the Philosopher�s Stone");
    strcpy(libro3.descripcionLibro, "La historia de un ni�o que descubre que es un mago en su 11 cumplea�os.");
    libro3.estado = 1;
    libro3.vecesPrestadoLibro = 0;


    fwrite(&libro3, sizeof(stLibro), 1, archi);



    stLibro libro4;
    libro4.idLibro = 4;
    strcpy(libro4.autorLibro, "Jane Austen");
    strcpy(libro4.generoLibro, "Romance");
    strcpy(libro4.nombreDeLibro, "Pride and Prejudice");
    strcpy(libro4.descripcionLibro, "Una historia de amor y malentendidos entre Elizabeth Bennet y el se�or Darcy.");
    libro4.estado = 1;
    libro4.vecesPrestadoLibro = 0;

    fwrite(&libro4, sizeof(stLibro), 1, archi);


    stLibro libro5;
    libro5.idLibro = 5;
    strcpy(libro5.autorLibro, "George Orwell");
    strcpy(libro5.generoLibro, "Terror");
    strcpy(libro5.nombreDeLibro, "1984");
    strcpy(libro5.descripcionLibro, "Una novela dist�pica sobre un futuro totalitario donde la libertad y la privacidad est�n severamente restringidas.");
    libro5.estado = 1;
    libro5.vecesPrestadoLibro = 0;

    fwrite(&libro5, sizeof(stLibro), 1, archi);

    fclose(archi);
}


//cargar todos los libros al archivo

void librosAlArchivo(estanteria arregloEstanterias[])
{
    int dim=5;
    for(int i=0; i < dim; i++)
    {
        listaSimpleAlArchivo(arregloEstanterias[i].listaLibro);
    }
}

//cargar una listaSimple de libros al archivo

void listaSimpleAlArchivo(nodoSimple*listaSimple)
{
    FILE*buffer=fopen(ARCHIVO_LIBROS,"wb");
    stLibro aux;
    if(buffer != NULL)
    {
        while(listaSimple != NULL)
        {
            aux=listaSimple->datoLibro;
            fwrite(&aux,sizeof(stLibro),1,buffer);
        }

        fclose(buffer);
    }

}


//cargar estanterias del archivo

void archivoAEstanteria(estanteria arregloEstanterias[])
{
    FILE*buffer=fopen(ARCHIVO_LIBROS,"rb");
    stLibro aux;
    if(buffer != NULL)
    {

        while(fread(&aux,sizeof(stLibro),1,buffer) > 0 )
        {
            cargarEstanteriaOrdenada(arregloEstanterias,crearNodoSimple(aux));
        }


        fclose(buffer);
    }

}


/// funciones del archivo de prestamos

void prestamosAlArchivo(estanteria arregloEstanterias[])
{
    FILE*buffer=fopen(ARCHIVO_PRESTAMOS,"wb");
    if(buffer != NULL)
    {
        for(int i=0 ; i < MAX_GEN; i++)
        {
            recorrerLibrosParaFila(arregloEstanterias[i].listaLibro,buffer);
        }
        fclose(buffer);
    }

}

void recorrerLibrosParaFila(nodoSimple*listaSimpleLibros,FILE*buffer)
{
    while(listaSimpleLibros != NULL)
    {
        recorrerFilaParaPrestamos(listaSimpleLibros->datoLibro.reservasLibro,buffer);
    }
}


/// Funciones para buscar libros




/// Buscar e imprimir libros por autor
void buscarLibroXAutor(estanteria arregloEstanterias[])
{

    char autor[MAX_DIM];

    do
    {
        printf("Ingrese el autor que desa buscar");
        fflush(stdin);
        gets(autor);
    }
    while(validarDigitosEnStrings(autor)== 1||validarRangoDeNombre(autor)== 1);
    buscarEstanteriaParaAutor(arregloEstanterias, autor);

}

void buscarEstanteriaParaAutor(estanteria arregloEstanterias[], char autor[])
{

    int flag = 0;

    for (int i= 0; i < MAX_GEN; i++)
    {

        nodoSimple* aux = retornarNodosLibroXAutor(arregloEstanterias[i].listaLibro, autor);

        if (strcmpi(aux->datoLibro.autorLibro, autor) == 0)
        {

            mostrarListaSimple(aux);
            flag = 1;
        }
    }

    if(!flag)
    {
        printf("\nNo se encontro ningun libro de ese Autor\n");
    }

}


/// Buscar e imprimir libros por Genero


void buscarLibroXgenero(estanteria arregloEstanterias[])
{

    nodoSimple* aux = inicListaSimple();

    printf("Elije una opcion\n");
    validarGenero(aux->datoLibro.generoLibro);

    for (int i = 0; i < MAX_GEN; i++)
    {
        if (strcmpi(aux->datoLibro.generoLibro, arregloEstanterias[i].generoEstanteria) == 0)
        {
            mostrarListaSimple(arregloEstanterias[i].listaLibro);
        }
    }
}



/// Buscar e imprimir libros por Titulo

void buscarLibroXTitulo(estanteria arregloEstanterias[])
{

    char titulo[MAX_DIM];

    do
    {
        printf("Ingrese el Titulo que desa buscar");
        fflush(stdin);
        gets(titulo);
    }
    while(validarDigitosEnStrings(titulo)== 1||validarRangoDeNombre(titulo)== 1);

    buscarEstanteriaParaTitulo(arregloEstanterias, titulo);

}

void buscarEstanteriaParaTitulo(estanteria arregloEstanterias[], char titulo[])
{

    int flag = 0;

    for (int i= 0; i < MAX_GEN; i++)
    {

        nodoSimple* aux = retornarNodosLibroXTitulo(arregloEstanterias[i].listaLibro, titulo);

        if (strcmpi(aux->datoLibro.nombreDeLibro, titulo) == 0)
        {

            mostrarListaSimple(aux);
            flag =1;
        }
    }

    if (!flag)
    {
        printf("\nNo se encontro nungun Libro con ese Titulo\n");
    }

}


/// Buscar e imprimir libros por Clave

/// Este codigo esta roto, no anda del todo.
/// El porbelma que me tira es que me da un bucle infinito sin que yo le llegue a escribir nada, a pesar de que tenga el fflush.
// ver que onda eso
void buscarLibroXClave( estanteria arregloEstanterias[])
{

    char claves[MAX_DIM];

    do
    {
        printf("Ingrese las palabras clave \n");
        fflush(stdin);
        fgets(claves, MAX_DIM, stdin);
    }
    while(validarDigitosEnStrings(claves)== 1||validarRangoDeNombre(claves)== 1);


    for (int i = 0; i < MAX_DIM; i++)
    {


        buscarPalabrasClaves(arregloEstanterias[i].listaLibro, claves);

    }

}



void buscarPalabrasClaves(nodoSimple* listaSimple, char claves[])
{

    nodoSimple* aux = inicListaSimple();
    char delimitador[] = "#";

    char *token = strtok(claves, delimitador);

    while (token != NULL)
    {

        if (strstr(token, delimitador) != NULL)
        {
            aux = retornarNodosLibroXClave(listaSimple, token);
        }
        mostrarListaSimple(aux);

        token = strtok(NULL, delimitador);
        }
    }




/// Esto queda a definir
