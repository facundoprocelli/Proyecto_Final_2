#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"

#define ARCHIVO_MIEMBROS "archivoMiembros.bin"
#define ARCHIVO_PRESTAMOS "archivoPrestamos.bin"
#define ARCHIVO_LIBROS "archivoLibros.bin"
#define ARCHIVO_PRESTAMOS_INACTIVOS "archivoPrestamosInactivos.bin"




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


/// menu general
void menuGeneral()
{
    int opSw=0;
    char continuarBucle = 's';
    //menu admin
    char contraseniaAdmin[MAX_DIM];

    //menu usuario
    int flag=0;
    char opCrearCuenta;
    nodoArbol* auxNodoMiembro;
    char auxString[MAX_DIM];


    /// Cargar Estanterias
    estanteria arregloEstanterias[5];

    inicEstanterias(arregloEstanterias); /// a la iniciacion tmb deberiamos agregar las reservas de los libros pero todavia no lo tenemos
    cargarLibrosPredeterminados(arregloEstanterias); // se cargan los libros automaticamente
    archivoAEstanteria(arregloEstanterias); // Se pasan los libros a la estanteria

    /// Cargar Arbol Miembros
    nodoArbol * arbolMiembros=inicArbol();
    arbolMiembros = cargarMiembrosPredeterminados(arbolMiembros);
    arbolMiembros=archivoAlArbol(arbolMiembros); //pasamos los miembros al arbol

    /// Cargar Filas de prestamos
    archivoAFilasPrestamos(arregloEstanterias); // se pasan los prestamos a los respectivos libros

    /// Pila prestamos inactivos
    pilaPrestamos prestamosInactivos;
    inicPila(&prestamosInactivos);
    archivoAPila(&prestamosInactivos);


    do
    {
        imprimirMensajeMarronOscuro("\t\t\t ||Bienvenido a la Biblioteca BookMaze||");
        imprimirMensajeMarronOscuro("\t\t      =============================================\n\n");
        puts("\n========================|Menu general|========================");
        opcionesMenuGeneral();
        opSw=preguntarDatoEntero();
        limpiarPantalla();
        switch(opSw)
        {
        case 1:

            printf("Ingrese la contrasenia del admin: ");
            fflush(stdin);
            gets(contraseniaAdmin);
            if(strcmp(contraseniaAdmin,"Book Maze")==0)
            {
                imprimirMensajeVerde("Ha ingresado correctamente");
                arbolMiembros = biblioteca(arregloEstanterias, arbolMiembros);
            }
            else
            {
                imprimirMensajeRojo("Contrasenia incorrecta,Reintente\n");
            }
            break;
        case 2:


            printf("Ingrese su DNI si tiene una cuenta, sino le crearemos una:  \n");
            puts("============================================================");
            do
            {
                printf("DNI: ");
                fflush(stdin);
                scanf("%s", &auxString);

            }
            while(validarCaracteresEnEnteros(auxString)== 0||validarRangoDNI(auxString)== 0 || validarCaracteresEnEnteros(auxString)== 0);

            auxNodoMiembro=buscarNodoPorDniArbol(arbolMiembros,auxString);

            if(auxNodoMiembro == NULL) //si no existe
            {
                imprimirMensajeRojo("Ese Dni no existe, desea crear una cuenta? s/n: ");
                fflush(stdin);
                scanf("%c",&opCrearCuenta);

                if(opCrearCuenta== 's'||opCrearCuenta == 'S')
                {
                    //si el usuario desea crearse una cuenta, la creamos y ya le activamos el menu

                    auxNodoMiembro=crearNodoArbol(crearUnMiembro(arbolMiembros));
                    arbolMiembros=insertarPorDni(arbolMiembros,auxNodoMiembro);
                }
            }

                limpiarPantalla();
            if(auxNodoMiembro != NULL)
            {
                imprimirMensajeVerde("Ha ingresado correctamente");
                menuUsuario(arregloEstanterias, arbolMiembros,auxNodoMiembro,&prestamosInactivos);
            }



            break;
        case 3:
            informeFinal(arbolMiembros,arregloEstanterias,prestamosInactivos);
            imprimirMensajeVerde("HA FINALIZADO CORRECTAMENTE EL PROGRAMA...");
            continuarBucle = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(continuarBucle != 'n');


    arbolAlArchivo(arbolMiembros);
    prestamosAlArchivo(arregloEstanterias);
    estanteriaAlArchivo(arregloEstanterias);
    cargarPilaAlArchivo(&prestamosInactivos);


}




void opcionesMenuGeneral()
{

    puts("[1] Admin");
    puts("[2] Usuario");
    puts("[3] Finalizar programa");
    puts("========================================");

}

///menu admin
nodoArbol* biblioteca(estanteria arregloEstanterias[], nodoArbol* arbolMiembros)
{


    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        imprimirMensajeMarronOscuro("\n============================|Menu admin|============================\n");
        menuDeAccionesPrincipales();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            menuLibros(arregloEstanterias);
            break;
        case 2:
            arbolMiembros = menuMiembros(arbolMiembros);
            break;
        case 3:
            menuPrestamos(arregloEstanterias);
            break;
        case 4:

            opContinuarMenuPrin = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }

    }
    while(opContinuarMenuPrin != 'n');
    return arbolMiembros;
}

void menuDeAccionesPrincipales()
{
    printf("Por favor, seleccione que accion desea realizar \n\n");
    puts("============================================================");
    printf("[1] Opciones Libros\n");
    printf("[2] Opciones Miembros\n");
    printf("[3] Opciones Prestamos \n");
    printf("[4] Salir \n");
    puts("============================================================");

}

void opcionesMenuGestionarLibros()
{
    printf("Seleccione una opcion\n");
    puts("============================================================");
    printf("[1] Ingresar Nuevo Libro \n");
    printf("[2] Buscar libros\n");
    printf("[3] Actualizar Libro\n");
    printf("[4] Mostrar todos los libros\n");
    printf("[5] Volver al menu principal\n");
    puts("============================================================");

}

void menuLibros(estanteria arregloEstanterias[])
{
    int opSw=0;
    char opCont='s';
    stLibro aux;
    do
    {
        puts("============================================================");

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
        case 2:
            menuBuscarLibros(arregloEstanterias);
            break;
        case 3:
            actualizarLibro(arregloEstanterias);
            break;
        case 4:
            mostrarTodasLasEstanterias(arregloEstanterias);
            break;
        case 5:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }

    }
    while(opCont != 'n');


}

void opcionesMenuActualizarLibros()
{

    printf("Seleccione una opcion: \n");

    printf("[1] Actualizar Nombre\n");
    printf("[2] Actualizar Genero\n");
    printf("[3] Actualizar Autor\n");
    printf("[4] Actualizar Descripcion\n");
    printf("[5] Actualizar Estado\n"); // Activo o inactivo- No permitir poner que este prestado.
    printf("[6] Volver al menu de libros\n");
    puts("============================================================");

}

void actualizarLibro(estanteria arregloListas[])
{
    int opSw=0,flag = 0;
    char opCont='s';
    nodoSimple* buscado = inicListaSimple();
    do
    {
        puts("============================================================");
        opcionesMenuActualizarLibros();
        opSw = preguntarDatoEntero();
        if(opSw != 6 && flag == 0)//agrego un flag para seleccione a un libro y si quiere modificar otro va a tener que volver al menu
        {
        mostrarTodasLasEstanterias(arregloListas);
        int idBuscado = preguntarID(arregloListas);
        buscado = retornarLibroXIDEnEstanterias(arregloListas,idBuscado);
        limpiarPantalla();
        flag = 1;
        }
        imprimirMensajeVerde("=========================LIBRO SELECTO==============================");
        mostrarListaSimple(buscado);
        if(buscado != NULL)
        {

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
        case 6:
            imprimirMensajeVerde("=========================MODIFICADO==============================");
            mostrarListaSimple(buscado);
            opCont='n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }

    }

    }while(opCont != 'n');


}


void opcionesMenuBuscarLibros()
{

    printf("Seleccione una opcion: \n");

    printf("[1] Buscar por Titulo \n");
    printf("[2] Buscar por Autor \n");
    printf("[3] Buscar por Genero \n");
    printf("[4] Buscar Palabra Clave \n");
    printf("[5] Buscar por Estado \n");
    printf("[6] Volver al menu de libros \n");
    puts("============================================================");

}

void menuBuscarLibros(estanteria arregloEstanterias[])
{
    int opSw=0;
    char opCont='s';
    do
    {
        opcionesMenuBuscarLibros();
        opSw=preguntarDatoEntero();
        limpiarPantalla();
        switch(opSw)
        {
        case 1:// Buscar Libro por titulo
            buscarLibroXTitulo(arregloEstanterias);
            break;
        case 2://Buscar libro por autor
            buscarLibroXAutor(arregloEstanterias);
            break;
        case 3://Buscar libro por genero
            buscarLibroXgenero(arregloEstanterias);
            break;
        case 4:// buscar libro por clave
            buscarLibroXClave(arregloEstanterias); // Esto esta en duda ( yo lo dejaria para el final final )
            break;
        case 5:// buscar libro por clave
            buscarLibrosXEstado(arregloEstanterias);
            break;
        case 6:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(opCont!='n');

}

void opcionesMenuMiembros()
{


    printf("Seleccione una opcion\n");
    printf("[1] Registrar Miembros \n");
    printf("[2] Buscar Miembros \n");
    printf("[3] Calcular Multas \n");
    printf("[4] Generar Informes  \n");
    printf("[5] Mostrar todos los Miembros\n");
    printf("[6] Volver al menu principal \n");
    puts("============================================================");

}

nodoArbol* menuMiembros(nodoArbol * raiz)
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
            menuBuscarMiembros(raiz);
            break;
        case 3: //calcular multas
            break;
        case 4: //informes sobre miembros (hacer un menu)
            break;
        case 5:
            mostrarArbolInorden(raiz);
            break;
        case 6:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont != 'n');

    return raiz;
}


void opcionesMenuBuscarMiembros()
{


    printf("Seleccione una opcion \n");
    printf("[1] Buscar por Nombre\n");
    printf("[2] Buscar por DNI\n");
    printf("[3] Buscar por Estado\n");
    printf("[4] Buscar por Saldo\n"); //mayor o menor al dato buscado
    printf("[5] Buscar por Prestamos\n"); // Todos aquellos que tengan un libro prestado
    printf("[6] Volver al menu de miembros \n");
    puts("============================================================");

}


///Buscar miembros por diferentes parametros
void menuBuscarMiembros(nodoArbol* raiz)
{
    int opSw=0;
    char opCont='s';
    do
    {
        opcionesMenuBuscarMiembros();
        opSw=preguntarDatoEntero();

        switch(opSw)
        {
        case 1:// Buscar miembro por nombre
            buscarMiembroXNombre(raiz);
            break;
        case 2:// buscar miembro por DNI
            buscarMiembroXDNI(raiz);
            break;
        case 3:// buscar miembro por Estado
            buscarMiembroXEstado(raiz);
            break;
        case 4:// buscar miembro por Saldo
            buscarMiembroXSaldo(raiz);
            break;
        case 5:// buscar miembro por Prestamos
            buscarMiembroXPrestamos(raiz);
            break;
        case 6:
            limpiarPantalla();
            opCont='n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }

    }
    while(opCont != 'n');

}

void opcionesMenuPrestamos()
{
    puts("[1] Ver todos los prestamos"); //Ver todos los prestamos activos
    puts("[2] Volver al menu principal");
    puts("============================================================");

}

void menuPrestamos(estanteria arregloEstanterias[])
{

    int opSw=0;
    char opCont='s';
    do
    {

        opcionesMenuPrestamos();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1:
            mostrarTodosLosPrestamos(arregloEstanterias);
            break;
        case 2:
            limpiarPantalla();
            opCont='n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }

    }
    while(opCont != 'n');

}

void mostrarTodosLosPrestamos(estanteria arregloEstanteria[])
{

    int opSw;

    do
    {
        menuTodosPrestamos();
        opSw = preguntarDatoEntero();
    }
    while ((opSw != 1 && opSw != 2));


    if(opSw == 1)
    {
        mostrarPrestamosActivos(arregloEstanteria);
    }
    else if (opSw == 2)
    {
        mostrarPrestamosInactivos();
    }



}

void menuTodosPrestamos()
{
    puts("[1] Mostrar prestamos Activos");
    puts("[2] Mostrar prestamos Inactivos\n");
}

void mostrarPrestamosActivos(estanteria arregloEstanteria[])
{
    int flag = 0;

    for(int i = 0; i<5; i++)
    {
        nodoSimple* listaAux = arregloEstanteria[i].listaLibro;

        while (listaAux != NULL)
        {
            if(!filaVacia(listaAux->datoLibro.reservasLibro))
            {
                flag = 1;
                mostrarFila(listaAux->datoLibro.reservasLibro);
            }

            listaAux = listaAux ->siguiente;
        }
    }

    if(flag == 0){
        imprimirMensajeRojo("\n No hay prestamos activos");
    }
}


void mostrarPrestamosInactivos()
{
    stPrestamo aux;
    int flag = 0;
    FILE* archi = fopen(ARCHIVO_PRESTAMOS_INACTIVOS, "rb");

    if(archi != NULL)
    {
        while (fread(&aux, sizeof(stPrestamo), 1, archi) > 0)
        {
            if(aux.estado == 0)
            {
                mostrarUnPrestamo(aux);
                flag = 1;
            }
        }
    }


    if(flag == 0)
    {
        imprimirMensajeRojo("\nNo hay prestamos Inactivos\n");
    }

    fclose( archi);
}



///menu usuario

void menuUsuario(estanteria arregloEstanterias[],nodoArbol * arbolMiembro, nodoArbol* miembroActual, pilaPrestamos*prestamosInactivos)///verificar si faltan alguna estructura mas...
{
    //aca va todo lo que puede hacer un usuario y deberiamos retornar el miembro, asi solo puede modificar el suyo
    mostrarUnMiembro(miembroActual->dato);
    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        imprimirMensajeMarronOscuro("\n============================|Menu usuario|============================\n");
        printf("Bienvenido %s \n",miembroActual->dato.datosPersonales.nombre);
        menuDeAccionesPrincipales();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            menuLibrosUsuario(arregloEstanterias,miembroActual,prestamosInactivos,arbolMiembro);
            break;
        case 2:
            menuMiembroUsuario(miembroActual,arbolMiembro);
            break;
        case 3:
            menuPrestamosUsuario(arregloEstanterias,miembroActual,prestamosInactivos,arbolMiembro);
            break;
        case 4:
            opContinuarMenuPrin = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');



}

void opcionesMenuUsuarioLibros()
{
    puts("[1] Buscar un libro"); //tenemos un menu
    puts("[2] Ver todos los libros disponibles en este momento"); // ver todos los que tienen la fila vacia
    puts("[3] Ver los libros que tienen cola de espera"); // ver todos los que tienen al menos un miembro en la fila
    puts("[4] Volver al menu principal");
    puts("================================================================");
}



void opcionesMenuUsuarioMiembro()
{
    puts("[1] Cambiar nombre");
    puts("[2] Cambiar numero de telefono");
    puts("[3] Agregar saldo a la cuenta");
    puts("[4] Ver mi usuario");
    puts("[5] Volver al menu principal");
    puts("=======================================");
}

void menuLibrosUsuario(estanteria arregloEstanterias[],nodoArbol* miembroActual,pilaPrestamos*prestamosInactivos,nodoArbol*arbolMiembros)
{
    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    char auxString[MAX_DIM];



    char opSeguirBuscando;
    int flag=0,i=0,continuarBucle=1;


    do
    {
        opcionesMenuUsuarioLibros();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            buscarLibrosUsuario(arregloEstanterias);
            break;
        case 2:// mostrar libros disponibles
            verLibrosDisponiblesUsuario(arregloEstanterias);
            break;
        case 3:// mostrar libros con lista de espera
            verLibrosConEsperaUsuario(arregloEstanterias);
            break;
        case 4:
            opContinuarMenuPrin = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');
}

void menuMiembroUsuario(nodoArbol* miembroActual, nodoArbol* arbolMiembro)
{
    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        opcionesMenuUsuarioMiembro();
        opMenuPrin=preguntarDatoEntero();
        //limpiarPantalla();
mostrarUnMiembro(miembroActual->dato);


        nodoArbol* miembroModifcable = buscarNodoPorDniArbol(arbolMiembro, miembroActual->dato.datosPersonales.dni);

        if ( miembroModifcable == NULL){

            printf("asdfggfds");
        }

        switch(opMenuPrin)
        {
        case 1://modificar nombre miembro
            miembroModifcable = cambiarNombreMiembro(miembroModifcable);
            break;
        case 2:// modificar numero de telefono miembro
            miembroModifcable = cambiarNumeroDeTelefonoMiembro(miembroModifcable, arbolMiembro);
            break;
        case 3:// modificar saldo de cuenta de miembro
            miembroModifcable = cambiarSaldoDeCuentaMiembro(miembroModifcable);
            break;
        case 4:// mostrarse a si mismo
            mostrarUnMiembro(miembroModifcable->dato);
            break;
        case 5:
            opContinuarMenuPrin = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');
}


void opcionesMenuUsuarioPrestamos()
{
    puts("[1] Pedir un libro");
    puts("[2] Devolver un libro o eliminar mi prestamo de la cola de espera");
    puts("[3] Ver mis prestamos activos");
    puts("[4] Ver todo el historial de prestamos");
    puts("[5] Volver al menu principal");
    puts("===============================================");
}

void menuPrestamosUsuario(estanteria arregloEstanterias[],nodoArbol* miembroActual,pilaPrestamos*prestamosInactivos,nodoArbol*arbolMiembros)
{
    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    nodoDoble *  prestamoActual = inicListaDoble();
    do
    {
        opcionesMenuUsuarioPrestamos();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            pedirUnLibro(arregloEstanterias,miembroActual,*prestamosInactivos);
            break;
        case 2:
            devolverUnLibroUsuario(arregloEstanterias,prestamosInactivos,miembroActual);
            break;
        case 3:
            /// Mostrar prestamo activo del usuario
            if(miembroActual->dato.prestamoActivoID != 0)
            {
                prestamoActual= retornarNodoPrestamoXId(arregloEstanterias,miembroActual->dato.prestamoActivoID);
                mostrarUnPrestamo(prestamoActual->datoPrestamo);
            }
            else
            {
                imprimirMensajeRojo("No tenes prestamos activos");
            }
            break;
        case 4:
            /// Ver historial de prestamos
            break;
        case 5:
            opContinuarMenuPrin = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');
}

void buscarLibrosUsuario(estanteria arregloEstanterias[])
{

    int opSw=0;
    char opCont='s';
    do
    {
        opcionesMenuBuscarLibrosUsuario();
        opSw=preguntarDatoEntero();
        switch(opSw)
        {
        case 1:// buscar libro por titulo
            buscarLibroXTitulo(arregloEstanterias);
            break;
        case 2:// Buscar libro por autor
            buscarLibroXAutor(arregloEstanterias);
            break;
        case 3:// buscar libro por genero
            buscarLibroXgenero(arregloEstanterias);
            break;
        case 4:// buscar libro por popularidad
            buscarLibroXPopularidad(arregloEstanterias);
            break;
        case 5:// buscar libro por palabra clave
            buscarLibroXClave(arregloEstanterias);
            break;
        case 6:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
        //limpiarPantalla();
    }
    while(opCont!='n');
}

void opcionesMenuBuscarLibrosUsuario()
{

    puts("[1] Buscar libro por Titulo");
    puts("[2] Buscar libro por Autor");
    puts("[3] Buscar libro por Genero");
    puts("[4] Buscar libro mas popular");
    puts("[5] Buscar libro por palabra Clave");
    puts("[6] Volver al menu principal");
    puts("======================================");


}


/// funciones estanteria

void inicEstanterias(estanteria arregloEstanterias[])
{
    char *generos[]= {"Fantasia","Ciencia Ficcion","Romance","Terror","Aventura"};
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
    imprimirMensajeMarronOscuro("======================================================");
    printf("\nGENERO DE LA ESTANTERIA[%s]\n",unaEstanteriaSola.generoEstanteria);


    if(unaEstanteriaSola.listaLibro != NULL)
    {
        mostrarListaSimple(unaEstanteriaSola.listaLibro);

    }
    else
    {
        imprimirMensajeRojo("Estanteria vacia :(");
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
    else if(strcmp(arregloEstanterias[4].generoEstanteria,nuevoNodo->datoLibro.generoLibro) == 0)
    {
        arregloEstanterias[4].listaLibro=agregarAlFinalSimple(arregloEstanterias[4].listaLibro,nuevoNodo);
    }
    else
    {
        imprimirMensajeRojo("ERROR cargar estanteria ordenada");
    }

}

int preguntarID(estanteria arregloEstanterias[])
{

    char idBuscado[MAX_DIM];
    int idConvertido;
    int ultimoID;
    do
    {
        printf("Ingrese el ID que desea buscar: ");
        fflush(stdin);
        gets(idBuscado);

        ultimoID = retornarUltimoIDLibro(arregloEstanterias);
        idConvertido = convertirStringsDeNumerosAEntero(idBuscado);
    }
    while (validarCaracteresEnEnteros(idBuscado) == 0 || idConvertido > ultimoID);

    return idConvertido;
}

///informe final funciones

void informeFinal(nodoArbol*raiz,estanteria arregloEstanterias[],pilaPrestamos pila)
{

    ///aca tenemos que hacer muchas funciones que cumplan con los requerimientos del informe
    puts("==========================INFORME==================================");
    printf("Total de miembros................. [%i]\n",contarMiembrosArbol(raiz));
    printf("Cantidad de miembros activos.......[%i]\n",contarMiembrosActivos(raiz));
    printf("Cantidad de miembros dados de baja:[%i]\n",contarMiembrosInactivos(raiz));
    printf("Total de libros....................[%i]\n",contarCantidadDeLibros(arregloEstanterias));
    printf("Total de prestamos activos.........[%i]\n",contarPrestamos(arregloEstanterias));//activo
    printf("Total de prestamos inactivos.......[%i]\n",contarPrestamosInactivos(pila));//inactivo
    printf("ID del libro mas prestado..........[%i]\n",idLibroMasPrestado(arregloEstanterias));// Lo que se impime en esta funcion se pasa a los cosos de abajo
    printf("Miembro con mayor saldo............[%i]\n",miembroConMayorSaldo(raiz)); /*dniMiembroMayorSaldo(raiz));///Mostrar el DNI Estas funciones no andan del todo*/
    puts("==================================================================");


}

///funciones de informes

//contarmiembros ya existe
int contarMiembrosActivos(nodoArbol * raiz)///me devuelve los miembros activos en el arbol
{
    int cantidadActivos = 0;

    if(raiz != NULL)
    {
        if(raiz->dato.estado == 1)
        {

            cantidadActivos=1;
        }
        cantidadActivos+= contarMiembrosActivos(raiz->izquierda);
        cantidadActivos+= contarMiembrosActivos(raiz->derecha);

    }

    return cantidadActivos;
}
int contarMiembrosInactivos(nodoArbol * raiz)///me devuelve los miembros que esten inactivos o dados de baja en el sistema
{
    int cantidadInactivos = 0;

    if(raiz != NULL)
    {
        if(raiz->dato.estado == 0)
        {

            cantidadInactivos=1;
        }
        cantidadInactivos+= contarMiembrosInactivos(raiz->izquierda);
        cantidadInactivos+= contarMiembrosInactivos(raiz->derecha);

    }

    return cantidadInactivos;
}

int contarCantidadDeLibros(estanteria arregloEstanterias[])///me devuelve la cantidad de libros que haya en todo el sistema
{
    int dim = 5;///cantidad de estanterias por genero
    int cantidadLibros = 0;

    nodoSimple*aux=NULL;

    for(int i = 0; i<dim; i++)
    {
        aux= arregloEstanterias[i].listaLibro;
        while(aux != NULL)
        {
            cantidadLibros++;
            aux=aux->siguiente;
        }
    }
    return cantidadLibros;
}

int contarPrestamos(estanteria arregloEstanterias[])
{

    int librosPrestadosActivos = 0;

    nodoSimple* aux = inicListaSimple();
    nodoDoble * auxDoble = inicListaDoble();
    for (int i = 0; i < 5; i++)
    {
        aux = arregloEstanterias[i].listaLibro;
        while (aux != NULL)
        {
            auxDoble = aux->datoLibro.reservasLibro.primero;
            while(auxDoble != NULL)
                {
                    librosPrestadosActivos++;
                    auxDoble = auxDoble->siguiente;
                }
            aux = aux->siguiente;
        }
    }
    return librosPrestadosActivos;
}

int contarPrestamosInactivos(pilaPrestamos pilita)
{
    int contadorInactivos = 0;
    nodoDoble * aux = pilita.prestamoInactivo;
    if(aux!= NULL)
    {
        if(aux->datoPrestamo.estado == 0)
        {
            contadorInactivos++;
        }
        aux = aux->siguiente;
    }

    return contadorInactivos;
}

int miembroConMayorSaldo(nodoArbol * raiz)
{
    int saldo = 0;
    if(raiz != NULL)
    {
        if(raiz->dato.saldo > saldo)
        {
            saldo = raiz->dato.saldo;
        }
        else
        {
        saldo = miembroConMayorSaldo(raiz->izquierda);
        saldo = miembroConMayorSaldo(raiz->derecha);
        }
    }

    return saldo;
}

/// funciones devolver un prestamo

// primero tengo que ver todos los libros que tiene activo el miembro
// segundo le pregunto cual libro quiere devolver
// tercero hago todas las validaciones sobre q si el libro existe
// cuarto le modifico las stats al libro, le aumento las veces prestado, si no tiene nadie en la fila le cambio el estado, sino sigue el mismo estado
// quinto muevo el prestamo a la pila de prestamos inactivos


void devolverUnLibroUsuario(estanteria arregloEstanterias[],pilaPrestamos*prestamosInactivos,nodoArbol*miembroActual)
{
    char opDevolver = 's';

    if(miembroActual->dato.prestamoActivoID !=0)/// 0 es prestamo inactivo
    {

        nodoDoble* auxPrestamo = retornarNodoPrestamoXId(arregloEstanterias,miembroActual->dato.prestamoActivoID);

        puts("Este es su prestamo activo: ");
        mostrarUnPrestamo(auxPrestamo->datoPrestamo);

        printf("Desea devolver el libro actual? s/n: ");
        fflush(stdin);
        scanf("%c",&opDevolver);

        if(opDevolver == 's'||opDevolver == 'S')
        {
            libroDevuelto(arregloEstanterias,miembroActual,prestamosInactivos, auxPrestamo);
        }
    }
    else
    {
        imprimirMensajeRojo("Usted no tiene ningun libro prestado");
    }

}

int retornarPosEstanteriaXGenero(estanteria arregloEstanteria[], char generoBuscar[])
{
    int i=0,flag=0;
    while(i < 5 && flag==0)
    {
        if(strcmpi(arregloEstanteria[i].generoEstanteria,generoBuscar)==0)
        {
            flag=1;
        }

        if(flag==0)
        {
            i++;
        }
    }

    if(flag==0)
    {
        i=-1;
    }

    return i;
}


int idLibroMasPrestado(estanteria arregloEstanteria[])
{

    int mayor = 0;
    int i = 0;
    nodoSimple* aux = inicListaSimple();
    nodoSimple* maxNodo = inicListaSimple();

    int max = buscarLibroMasPrestado(arregloEstanteria, 0);


    while ((i < 5))
    {

        aux = retornarNodosLibroXMasPopularidad(arregloEstanteria[i].listaLibro, max);
        if (aux != NULL)
        {
            maxNodo = aux;
        }
        i++;
    }

    mayor = maxNodo->datoLibro.idLibro;

    return mayor ;

}


/// Esats funicones no funcionan del todo pero me quede sin BING por hoy
int dniMiembroMayorSaldo(nodoArbol* raiz)
{
    int dniEncontrado = -1;
    nodoArbol* aux = buscarMiembroMayorSaldo(raiz);
    if (aux != NULL)
    {
        dniEncontrado = aux->dato.datosPersonales.dni;
    }

    return dniEncontrado;
}

nodoArbol* buscarMiembroMayorSaldo(nodoArbol* raiz)
{
    nodoArbol* personaMayorSaldo = raiz;

    if (raiz == NULL)
    {
        return NULL;
    }
    else
    {
        nodoArbol* personaMayorSaldoIzq = buscarMiembroMayorSaldo(raiz->izquierda);
        nodoArbol* personaMayorSaldoDer = buscarMiembroMayorSaldo(raiz->derecha);


        if (personaMayorSaldoIzq != NULL && personaMayorSaldoIzq->dato.saldo > personaMayorSaldo->dato.saldo)
        {
            personaMayorSaldo = personaMayorSaldoIzq;
        }
        if (personaMayorSaldoDer != NULL && personaMayorSaldoDer->dato.saldo > personaMayorSaldo->dato.saldo)
        {
            personaMayorSaldo = personaMayorSaldoDer;
        }
    }
    return personaMayorSaldo;
}
