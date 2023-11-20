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

    printf("Descripcion: ");
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
    printf("Descripcion...........: %s \n",aux.descripcionLibro);
    printf("Copias................: %s \n",aux.cantidadDeCopias);

    mostrarFila(aux.reservasLibro);

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
    nodoSimple* aux =NULL;

    while(listaSimple != NULL && listaSimple->datoLibro.idLibro != idBuscar)
    {
        listaSimple =listaSimple ->siguiente;
    }

    aux=listaSimple;

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

// verifico si hay copias disponibles de un determinado libro

int verificarSiHayCopiasEnUnLibro(stLibro datoLibro)
{
    int flag=0;

    if(datoLibro.cantidadDeCopias != 0)
    {
        flag=1;
    }

    return flag; // si flag= 1 hay copias sino 0
}


///archivos

// cargar un libro a un archivo

void cargarUnLibroAlArchivo(stLibro aux) //cuando se cree un nuevo libro se utiliza esta funcion
{
    FILE*buffer=fopen(ARCHIVO_LIBROS,"wb");
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

void cargarLibrosPredeterminados(estanteria arregloEstanteria[])
{

    nodoSimple* aux = inicListaSimple();

    stLibro libro1;
    libro1.idLibro = 1;
    strcpy(libro1.nombreDeLibro, "Kenobi");
    strcpy(libro1.generoLibro, "Ciencia Ficcion");
    strcpy(libro1.autorLibro, "John Jackson Miller");
    strcpy(libro1.descripcionLibro, "Una historia que contribuye a la caracterizacion general de Obi-Wan Kenobi.");
    libro1.estado = 1;
    libro1.vecesPrestadoLibro = 0;
    strcpy(libro1.cantidadDeCopias, "5");
    inicFila(&libro1.reservasLibro);
    cargarEstanteriaOrdenada(arregloEstanteria,crearNodoSimple(libro1));



    stLibro libro2;
    libro2.idLibro = 2;
    strcpy(libro2.nombreDeLibro, "Pokemon Mystery Dungeon: Ginjis Rescue Team");
    strcpy(libro2.generoLibro, "Aventura");
    strcpy(libro2.autorLibro, "Makoto Mizobuchi");
    strcpy(libro2.descripcionLibro, "Una emocionante historia de aventuras en el universo de Pokemon.");
    libro2.estado = 1;
    libro2.vecesPrestadoLibro = 0;
    strcpy(libro2.cantidadDeCopias, "3");
    inicFila(&libro2.reservasLibro);
    cargarEstanteriaOrdenada(arregloEstanteria,crearNodoSimple(libro2));



    stLibro libro3;
    libro3.idLibro = 3;
    strcpy(libro3.nombreDeLibro, "Harry Potter and the Philosophers Stone");
    strcpy(libro3.generoLibro, "Fantasia");
    strcpy(libro3.autorLibro, "J.K. Rowling");
    strcpy(libro3.descripcionLibro, "La historia de un nino que descubre que es un mago en su 11 cumpleaños.");
    libro3.estado = 1;
    libro3.vecesPrestadoLibro = 0;
    strcpy(libro3.cantidadDeCopias, "6");
    inicFila(&libro3.reservasLibro);
    cargarEstanteriaOrdenada(arregloEstanteria,crearNodoSimple(libro3));





    stLibro libro4;
    libro4.idLibro = 4;
    strcpy(libro4.nombreDeLibro, "Pride and Prejudice");
    strcpy(libro4.generoLibro, "Romance");
    strcpy(libro4.autorLibro, "Jane Austen");
    strcpy(libro4.descripcionLibro, "Una historia de amor y malentendidos entre Elizabeth Bennet y el señor Darcy.");
    libro4.estado = 1;
    libro4.vecesPrestadoLibro = 0;
    strcpy(libro4.cantidadDeCopias, "5");
    inicFila(&libro4.reservasLibro);
    cargarEstanteriaOrdenada(arregloEstanteria,crearNodoSimple(libro4));


    stLibro libro5;
    libro5.idLibro = 5;
    strcpy(libro5.nombreDeLibro, "1984");
    strcpy(libro5.generoLibro, "Terror");
    strcpy(libro5.autorLibro, "George Orwell");
    strcpy(libro5.descripcionLibro, "Una novela distopica sobre un futuro totalitario donde la libertad y la privacidad están severamente restringidas.");
    libro5.estado = 1;
    libro5.vecesPrestadoLibro = 0;
    strcpy(libro5.cantidadDeCopias, "8");
    inicFila(&libro5.reservasLibro);
    cargarEstanteriaOrdenada(arregloEstanteria,crearNodoSimple(libro5));



}


//cargar todos los libros al archivo

//cargar una listaSimple de libros al archivo

void estanteriaAlArchivo(estanteria arregloEstanterias[])
{
    int dim=5;
    FILE*buffer=fopen(ARCHIVO_LIBROS,"wb");
    nodoSimple * aux = inicListaSimple();

    if(buffer != NULL)
    {
        for(int i=0; i < dim; i++)
        {
            aux = arregloEstanterias[i].listaLibro;
            while(aux != NULL)
            {
                fwrite(&aux->datoLibro,sizeof(stLibro),1,buffer);
                aux = aux->siguiente;
            }
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
    stPrestamo aux;

    if(buffer != NULL)
    {

        for(int i=0 ; i < MAX_GEN; i++)
        {
            recorrerLibrosParaFila(arregloEstanterias[i].listaLibro,buffer);
        }
        fclose(buffer);
    }
    else
    {
        puts("Archivo prestamos vacio");
    }

}

void recorrerLibrosParaFila(nodoSimple*listaSimpleLibros,FILE*buffer)
{
    while(listaSimpleLibros != NULL)
    {
        recorrerFilaParaArchivarPrestamos(listaSimpleLibros->datoLibro.reservasLibro,buffer);
        listaSimpleLibros = listaSimpleLibros->siguiente;
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

    int flag = -1;
    int i = 0;
    nodoSimple* aux = inicListaSimple();

    while ((i < MAX_GEN))
    {
        aux = retornarNodosLibroXAutor(arregloEstanterias[i].listaLibro, autor);

        if ( aux != NULL)
        {
            if (strcmpi(aux->datoLibro.autorLibro, autor) == 0)
            {
                mostrarListaSimple(aux);
                flag = 1;
            }
        }

        i++;
    }

    if (flag == -1)
    {
        printf("\nNo se encontro nungun Libro de ese Autor\n");
    }

}

void mostrarMenuLibrosPopularidad()
{

    puts("[1] Top 3 libros mas Populares");
    puts("[2] Top 3 libros menos Populares");
    puts("-----------------------------------------");


}




/// Buscar e imprimir libros por Genero


void buscarLibroXgenero(estanteria arregloEstanterias[])
{


    char genero[MAX_DIM];

    printf("Que genero quiere buscar?\n");
    validarGenero(genero);

    for (int i = 0; i < MAX_GEN; i++)
    {
        if (strcmpi(genero, arregloEstanterias[i].generoEstanteria) == 0)
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
    int flag = -1;
    int i = 0;
    nodoSimple* aux = inicListaSimple();

    while ((i < MAX_GEN))
    {

        aux = retornarNodosLibroXTitulo(arregloEstanterias[i].listaLibro, titulo);

        if ( aux != NULL)
        {

            if (strcmpi(aux->datoLibro.nombreDeLibro, titulo) == 0)
            {
                mostrarListaSimple(aux);
                flag = 1;
            }
        }
        i++;
    }

    if (flag == -1)
    {
        printf("\nNo se encontro nungun Libro con ese Titulo\n");
    }

}

void buscarLibrosXEstado(estanteria arregloEstanterias[])
{

    int opcion;



    menuOpcionesDisponibilidad();
    opcion = preguntarDatoEntero();

    buscarEstanteriaParaEstado(arregloEstanterias, opcion);


}


void buscarEstanteriaParaEstado(estanteria arregloEstanterias[], int opcion)
{

    int flag = -1;
    int i = 0;
    nodoSimple* aux = inicListaSimple();

    while (i < MAX_GEN)
    {

        aux = retornarNodosLibroXEstado(arregloEstanterias[i].listaLibro, opcion);

        if ( aux != NULL)
        {
            if (aux->datoLibro.estado == opcion)
            {
                mostrarListaSimple(aux);
                flag = 1;
            }
        }
        i++;
    }

    if (flag == -1)
    {
        printf("\nNo se encontro nungun Libro con ese Estado\n");
    }

}




void menuOpcionesDisponibilidad()
{
    printf("\n[0] Titulo de baja");
    printf("\n[1] Titulo en alta");
    printf("\n[2] Titulo Prestados");

}


void buscarLibrosXCopias(estanteria arregloEstanterias[])
{

    int opcion;

    menuOpcionesCopias();
    opcion = preguntarDatoEntero();

    switch(opcion)
    {

    case 1:
        buscarEstanteriaParaCopias(arregloEstanterias, 0, 0);
        break;
    case 2:
        buscarEstanteriaParaCopias(arregloEstanterias, 0, 10);
        break;
    case 3:
        buscarEstanteriaParaCopias(arregloEstanterias,10, 30);
        break;
    case 4:
        buscarEstanteriaParaCopias(arregloEstanterias, 30, 50);
        break;
    case 5:
        buscarEstanteriaParaCopias(arregloEstanterias, 50, 100 );
        break;
    default:
        puts("\n Opcion invalida");



    }
}

void buscarEstanteriaParaCopias(estanteria arregloEstanterias[], int minCopias, int maxCopias)
{

    int flag = -1;
    int i = 0;
    nodoSimple* aux = inicListaSimple();

    while ((i < MAX_GEN))
    {

        aux = retornarNodosLibrosXCopias(arregloEstanterias[i].listaLibro,minCopias, maxCopias);

        if ( aux != NULL)
        {
            mostrarListaSimple(aux);
            flag = 1;
        }
        i++;
    }

    if (flag == -1)
    {
        printf("\nNo se encontro nungun Libro entre esos parametros\n");
    }

}

nodoSimple* retornarNodosLibrosXCopias(nodoSimple* lista, int minCopias, int maxCopias)
{


    nodoSimple* aux = inicListaSimple();

    while (lista != NULL)
    {

        int copias = convertirStringsDeNumerosAEntero(lista->datoLibro.cantidadDeCopias);

        if(copias >= minCopias && copias <= maxCopias)
        {

            nodoSimple* NN = crearNodoSimple(lista->datoLibro);
            aux = agregarAlFinalSimple(aux, NN);
        }

        lista = lista->siguiente;
    }


    return aux;
}





void menuOpcionesCopias()
{

    printf("\n[1] 0 Copias disponibles");
    printf("\n[2] Menos de 10 copias disponibles");
    printf("\n[3] Entre 30 y 10 copias disponibles");
    printf("\n[4] Entre 30 y 50 copias disponibles");
    printf("\n[5] Mas de 50 copias disponibles");

}



nodoSimple*  retornarNodosLibrosXDisponibilidad(nodoSimple* lista)
{

    nodoSimple* aux = inicListaSimple();

    while (lista != NULL)
    {

        if ( lista->datoLibro.estado == 1)
        {
            nodoSimple* NN =  crearNodoSimple(lista->datoLibro);
            aux = agregarAlFinalSimple(aux, NN);
        }

        lista = lista->siguiente;
    }


    return aux;
}

void verLibrosDisponiblesUsuario(estanteria arregloEstanterias[])
{

    int flag = -1;
    int i = 0;
    nodoSimple* aux = inicListaSimple();

    while ((i < MAX_GEN))
    {
        aux = retornarNodosLibrosXDisponibilidad(arregloEstanterias[i].listaLibro);

        if ( aux != NULL)
        {
            if(aux->datoLibro.estado == 1)
            {
                mostrarListaSimple(aux);
                flag = 1;
            }
        }

        i++;
    }

    if (flag == -1)
    {
        printf("\nNo se encontro nungun Libro disponible\n");
    }

}

// funcion que pasa el prestamo leido del archivo de prestamos a la fila correspondiente
void archivoAFilasPrestamos(estanteria arregloEstanterias[])
{
    FILE*buffer=fopen(ARCHIVO_PRESTAMOS,"rb");
    stPrestamo aux;


    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stPrestamo),1,buffer)>0)
        {

            recorrerEstanteriasParaAgregarAFilaPrestamo(arregloEstanterias,aux);

        }

        fclose(buffer);
    }
}

//busco la estanteria del prestamo correspondiente
void recorrerEstanteriasParaAgregarAFilaPrestamo(estanteria arregloEstanterias[], stPrestamo datoPrestamo)
{
    int flag=0, i=0;
    while(flag)
    {
        flag=recorrerLibrosParaAgregarAFilaPrestamo(arregloEstanterias[i].listaLibro,datoPrestamo);
        if(flag==0)
        {
            i++;
        }
    }
}

//busco el idLibro que tiene el prestamo, si coinciden lo agrego a la fila y retorno 1, si no, retorno 0
int recorrerLibrosParaAgregarAFilaPrestamo(nodoSimple*listaS, stPrestamo datoPrestamo)
{
    int flag=0;
    while(listaS != NULL && listaS->datoLibro.idLibro != datoPrestamo.idLibro)
    {
        listaS= listaS->siguiente;
    }

    if(listaS->datoLibro.idLibro == datoPrestamo.idLibro)
    {
        agregarAlFinalFila(&listaS->datoLibro.reservasLibro,datoPrestamo);
        flag=1;
    }
    return flag;
}




