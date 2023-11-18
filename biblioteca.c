#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"

#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"


///funciones generales

int preguntarDatoEntero()
{
    int dato=0;
    printf("Ingrese un dato: ");
    fflush(stdin);
    scanf("%i",&dato);
    return dato;
}

void limpiarPantalla()
{
    system("cls");
}

int convertirStringsDeNumerosAEntero(char aux[])
{
    return atoi(aux);
}


///todos los menu con sus respectivas funcionalidades
void biblioteca()
{

    cargarLibrosPredeterminados(); // se cargan los libros automaticamente
    estanteria arregloEstanterias[5];
    inicEstanterias(arregloEstanterias); /// a la iniciacion tmb deberiamos agregar las reservas de los libros pero todavia no lo tenemos
    archivoAEstanteria(arregloEstanterias); // Se pasan los libros a la estanteria


    /*
    Para solucionar el problema de los prestamos inactivos y seguirlos teniendo en el archivo pero no en las filas de los libros
    propusimos, para implementar el TDA de pilas, guardar todos los prestamos inactivos en una pila y luego cuando se cierre el programa,
    guardarlos en el archivo. por lo tanto nos quedarian los activos primeros y a lo ultimo los prestamos inactivos en el archivo

    crear una libreria mas de pilas.

    */



    nodoArbol * arbolMiembros=inicArbol();
    arbolMiembros=archivoAlArbol(arbolMiembros); //pasamos los miembros al arbol


    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        menuDeAccionesPrincipales();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            menuLibros(arregloEstanterias);
            break;
        case 2:
            menuMiembros(arbolMiembros);
            break;
        case 3:
            menuPrestamos();
            break;
        case 4:
            puts("Adios");
            informeFinal(arbolMiembros,arregloEstanterias);
            opContinuarMenuPrin = 'n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');

    arbolAlArchivo(arbolMiembros);
    librosAlArchivo(arregloEstanterias);
    prestamosAlArchivo(arregloEstanterias);

}

void menuUsuario(estanteria arregloEstanterias[],nodoArbol * raiz)///verificar si faltan alguna estructura mas...
{
    //aca va todo lo que puede hacer un usuario y deberiamos retornar el miembro, asi solo puede modificar el suyo


    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        menuDeAccionesPrincipales();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            menuLibrosUsuario();
            break;
        case 2:
            menuMiembroUsuario();
            break;
        case 3:
            menuPrestamosUsuario();
            break;
        case 4:
            opContinuarMenuPrin = 'n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');

}

void opcionesMenuUsuarioLibros()
{

    puts("[1] Devolver un libro"); //aumentar el contador de cantcopias +1
    puts("[2] Pedir un libro"); //es crear un prestamo, si el libro esta libre darselo y generar un prestamo, si no, meterlo en la fila de espera
    puts("[3] Buscar un libro"); //tenemos un menu
    puts("[4] Ver todos los libros disponibles en este momento"); // ver todos los que tienen la fila vacia
    puts("[5] Ver los libros que tienen cola de espera"); // ver todos los que tienen al menos un miembro en la fila
    puts("[6] Volver al menu principal");
    puts("----------------------------------------------------------------");
}

void opcionesMenuUsuarioPrestamos()
{

    puts("[1] Ver mis prestamos activos");
    puts("[2] Ver limite de prestamos");
    puts("[3] Ver todo el historial de prestamos");
    puts("[4] Volver al menu principal");
    puts("-------------------------------------------");
}

void opcionesMenuUsuarioMiembro()
{
    puts("[1] Cambiar nombre");
    puts("[2] Cambiar numero de telefono");
    puts("[3] Ingresar saldo a la cuenta");
    puts("[4] Ver mi usuario");
    puts("[5] Darse Alta o Baja");
    puts("[6] Volver al menu principal");
    puts("---------------------------------------");
}

void menuLibrosUsuario()
{
    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        opcionesMenuUsuarioLibros();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            opContinuarMenuPrin = 'n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');
}

void menuMiembroUsuario()
{
        int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        opcionesMenuUsuarioMiembro();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            opContinuarMenuPrin = 'n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');
}

void menuPrestamosUsuario()
{
        int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        opcionesMenuUsuarioPrestamos();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            opContinuarMenuPrin = 'n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');
}



void menuDeAccionesPrincipales()
{
    printf("Por favor, seleccione que accion desea realizar \n");
    printf("[1] Opciones Libros\n");
    printf("[2] Opciones Miembros\n");
    printf("[3] Opciones Prestamos \n");
    printf("[4] Salir \n");
    puts("-------------------------------------");
}

void opcionesMenuGestionarLibros()
{
    printf("Seleccione una opcion\n");

    printf("[1] Ingresar Nuevo Libro \n");
    printf("[2] Buscar libros\n");
    printf("[3] Prestar Libro\n");
    printf("[4] Devolver Libro\n");
    printf("[5] Reservar Libro\n");
    printf("[6] Actualizar Libro \n");
    printf("[7] Eliminar Libro\n");
    printf("[8] Mostrar todos los libros \n");
    printf("[9] Volver al menu principal \n");
    puts("---------------------------------------------------");
}

void menuLibros(estanteria arregloEstanterias[])
{
    int opSw=0;
    char opCont='s';
    stLibro aux;


    do
    {
        puts("---------------------------------------------------");
        opcionesMenuGestionarLibros();
        opSw=preguntarDatoEntero();
        limpiarPantalla();
        switch(opSw)
        {
        case 1: //crear un libro nuevo
            aux=crearUnLibro(arregloEstanterias);
            cargarEstanteriaOrdenada(arregloEstanterias,crearNodoSimple(aux));
            mostrarUnLibro(aux);
            break;
        case 2: //menu buscar libro
            menuBuscarLibros(arregloEstanterias);
            break;
        case 3: // prestar un libro

            break;
        case 4: // devolver un libro

            break;
        case 5: // reservar un libro
            break;
        case 6: // menu actualizar un libro
            actualizarLibro(arregloEstanterias);
            break;
        case 7: // eliminar un libro
            break;
        case 8:
            mostrarTodasLasEstanterias(arregloEstanterias);
            break;
        case 9:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont != 'n');


}

void opcionesMenuActualizarLibros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Actualizar Nombre \n");
    printf("[2] Actualizar Genero\n");
    printf("[3] Actualizar Autor \n");
    printf("[4] Actualizar Descripcion\n");
    printf("[5] Actualizar Estado \n"); // Activo o inactivo- No permitir poner que este prestado.
    printf("[6] Actualizar Cantiadad de Copias\n");
    printf("[7] Volver al menu de libros \n");
    puts("------------------------------------");
}

int preguntarID(estanteria arregloEstanterias[])
{

    char idBuscado[MAX_DIM];
    int idConvertido;
    int ultimoID;
    do
    {
        printf("Ingrese el ID que desea buscar");
        fflush(stdin);
        gets(idBuscado);

        ultimoID = retornarUltimoIDLibro(arregloEstanterias);
        idConvertido = convertirStringsDeNumerosAEntero(idBuscado);
    }
    while (validarCaracteresEnEnteros(idBuscado) == 0 || idConvertido > ultimoID);

    return idConvertido;
}

void actualizarLibro(estanteria arregloListas[])
{
    int opSw=0;
    char opCont='s';
    nodoSimple* buscado = inicListaSimple();
    do
    {
        puts("---------------------------------------------------");
        opcionesMenuActualizarLibros();

        opSw = preguntarDatoEntero();

        limpiarPantalla();

        if(opSw != 7)
        {
            int idBuscado = preguntarID(arregloListas);

            for(int i = 0; i < 5; i++)
            {
                buscado = retornarNodoSimpleXid(arregloListas[i].listaLibro, idBuscado);
                if(buscado != NULL)
                {
                    break;
                }
            }
        }
        switch(opSw)
        {
        case 1: //Actualizar Nombre
            buscado = modificarNombreLibro(buscado);
            break;
        case 2: //Actualizar Genero
            buscado = modificarGeneroLibro(buscado);
            break;
        case 3: // Actualizar Autor
            buscado = modificarAutorLibro(buscado);
            break;
        case 4: // Actualizar Descripción
            buscado = modificarDescripcionLibro(buscado);
            break;
        case 5: // Actualizar Estado
            buscado = modificarEstadoLibro(buscado);
            break;
        case 6: // Actualizar Cantidad de Copias
            buscado = modificarCantidadDeCopias(buscado);
            break;
        case 7:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        limpiarPantalla();
    }
    while(opCont != 'n');
}

void opcionesMenuBuscarLibros()
{

    printf("Seleccione una opcion\n");

    printf("[1] Buscar por Titulo \n");
    printf("[2] Buscar por Autor \n");
    printf("[3] Buscar por Genero \n");
    printf("[4] Buscar Palabra Clave \n");
    printf("[5] Buscar por Estado \n");
    printf("[6] Buscar por Copias \n"); //cuando la cant de copias es 0
    printf("[7] Volver al menu de libros \n");
    puts("-----------------------------------------");
}

void menuBuscarLibros(estanteria arregloEstanterias[])
{
    int opSw=0;
    char opCont='s';
    do
    {
        opcionesMenuBuscarLibros();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1:
            buscarLibroXTitulo(arregloEstanterias);
            break;
        case 2:
            buscarLibroXAutor(arregloEstanterias);
            break;
        case 3:
            buscarLibroXgenero(arregloEstanterias);
            break;
        case 4:
            //buscarLibroXClave(arregloEstanterias);
            break;
        case 5:
            buscarLibrosXEstado(arregloEstanterias);
            break;
        case 6:
            buscarLibrosXCopias(arregloEstanterias);
            break;
        case 7:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont!='n');

}

void opcionesMenuMiembros()
{

    puts("----------------------------------------------------");
    printf("Seleccione una opcion\n");
    printf("[1] Registrar Miembros \n");
    printf("[2] Buscar Miembros \n");
    printf("[3] Calcular Multas \n");
    printf("[4] Generar Informes  \n");
    printf("[5] Modificar limite de prestamo a un miembro\n");
    printf("[6] Volver al menu principal \n");
    puts("----------------------------------------------------");
}

void menuMiembros(nodoArbol * raiz)
{
    int opSw=0;
    char opCont='s';

    do
    {
        opcionesMenuMiembros();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1: //ingresar un nuevo miembro al arbol
            raiz=insertarPorDni(raiz,crearNodoArbol(crearUnMiembro(raiz)));
            break;
        case 2: //buscar un determinado miembro
            menuBuscarMiembros();
            break;
        case 3: //calcular multas
            break;
        case 4: ///informes sobre miembros (hacer un menu)
            break;
        case 5: //modificar el limite de prestamos en un miembro
            break;
        case 6:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont != 'n');

}


void opcionesMenuBuscarMiembros()
{

    puts("------------------------------------------");
    printf("Seleccione una opcion \n");
    printf("[1] Buscar por Nombre\n");
    printf("[2] Buscar por DNI\n");
    printf("[3] Buscar por Estado\n");
    printf("[4] Buscar por saldo\n"); //mayor o menor al dato buscado
    printf("[5] Buscar por Nro de prestamos activos\n");
    printf("[6] Buscar por Limite de prestamos\n");
    printf("[7] Volver al menu de miembros \n");
    puts("------------------------------------------");
}

void menuBuscarMiembros()
{
    int opSw=0;
    char opCont='s';
    do
    {
        opcionesMenuBuscarMiembros();
        opSw=preguntarDatoEntero();

        switch(opSw)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            limpiarPantalla();
            opCont='n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }

    }
    while(opCont != 'n');

}


/// funciones estanteria

void inicEstanterias(estanteria arregloEstanterias[])
{
    char*generos[]= {"Fantasia","Ciencia Ficcion","Romance","Terror","Aventura"};
    int dim=5;
    for(int i=0; i < dim; i++)
    {
        arregloEstanterias[i].listaLibro=inicListaSimple();
        strcpy(arregloEstanterias[i].generoEstanteria,generos[i]);
    }
}

void mostrarTodasLasEstanterias(estanteria arregloEstanterias[])
{
    int dim=5;
    for(int i=0; i < dim; i++)
    {
        mostrarUnaEstanteria(arregloEstanterias[i]);
    }
}

void mostrarUnaEstanteria(estanteria unaEstanteriaSola)
{
    puts("\n-----------------------------------------");
    printf("\nGENERO DE LA ESTANTERIA: %s \n",unaEstanteriaSola.generoEstanteria);

    if(unaEstanteriaSola.listaLibro != NULL)
    {
        mostrarListaSimple(unaEstanteriaSola.listaLibro);

    }
    else
    {
        puts("Estanteria vacia :(");
    }
}

void cargarEstanteriaOrdenada(estanteria arregloEstanterias[],nodoSimple*nuevoNodo)
{
    /// si el genero actual que esta en X estanteria es igual al genero del libro del nuevo nodo,
    /// se va a agregar al final en el genero correspondiente

    if(strcmp(arregloEstanterias[0].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[0].listaLibro=agregarAlFinalSimple(arregloEstanterias[0].listaLibro,nuevoNodo);

    }
    else if(strcmp(arregloEstanterias[1].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[1].listaLibro=agregarAlFinalSimple(arregloEstanterias[1].listaLibro,nuevoNodo);

    }
    else if(strcmp(arregloEstanterias[2].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[2].listaLibro=agregarAlFinalSimple(arregloEstanterias[2].listaLibro,nuevoNodo);

    }
    else if(strcmp(arregloEstanterias[3].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {

        arregloEstanterias[3].listaLibro=agregarAlFinalSimple(arregloEstanterias[3].listaLibro,nuevoNodo);

    }
    else
    {
        arregloEstanterias[4].listaLibro=agregarAlFinalSimple(arregloEstanterias[4].listaLibro,nuevoNodo);

    }

}

void opcionesMenuPrestamos()
{
    puts("[1] Pedir un libro"); //es crear un prestamo
    puts("[2] Consultar prestamos"); //cuantos libros quedan de un determinado titulo, precio de los prestamos, si hay cola en un libro, cuanto tiempo de espera hay
    puts("[3] Devolver un libro"); //aumentar el contador de cantcopias +1
    puts("[4] Modificar fecha de vencimiento de un prestamo");
    puts("[5] Volver al menu principal");
    puts("-------------------------------------------------------");
}

void menuPrestamos()
{

    int opSw=0;
    char opCont='s';
    opcionesMenuPrestamos();
    opSw=preguntarDatoEntero();
    do
    {

        switch(opSw)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            limpiarPantalla();
            opCont='n';
            break;
        default:
            puts("Ingrese una opcion valida");
            break;
        }

    }
    while(opCont != 'n');

}



void informeFinal(nodoArbol*raiz,estanteria arregloEstanterias[])
{

    ///aca tenemos que hacer muchas funciones que cumplan con los requerimientos del informe

    puts("-----------------------------------------------------------");
    printf("Total de miembros: \n");
    printf("Cantidad de miembros activos: \n");
    printf("Cantidad de miembros dados de baja: \n");
    printf("Total de libros: \n");
    printf("Total de prestamos: \n");
    printf("Libro mas prestado: \n");
    printf("Miembro con mayor sueldo: \n");
    printf("Libro con mayor cantidad de copias: \n");
    printf("Prestamo mas costoso: \n");
    printf("Miembro con mas prestamos: \n");
    puts("-----------------------------------------------------------");

}



