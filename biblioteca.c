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
    //cargarLibrosPredeterminados(arregloEstanterias); // se cargan los libros automaticamente
    archivoAEstanteria(arregloEstanterias); // Se pasan los libros a la estanteria
    archivoAFilasPrestamos(arregloEstanterias); // se pasan los prestamos a los respectivos libros

    /// Cargar Arbol Miembros
    nodoArbol * arbolMiembros=inicArbol();
    arbolMiembros=archivoAlArbol(arbolMiembros); //pasamos los miembros al arbol

    /// Pila prestamos inactivos
    pilaPrestamos prestamosInactivos;
    inicPila(&prestamosInactivos);
    archivoAPila(&prestamosInactivos);


    //agregarAlFinalFila(&arregloEstanterias[0].listaLibro->datoLibro.reservasLibro,crearUnPrestamo("12345678",3,"Fantasia"));

    do
    {
        imprimirMensajeMarronOscuro("\t\t\t ||Bienvenido a la Biblioteca BookMaze||\n");
        imprimirMensajeMarronOscuro("\t\t      =============================================\n\n");

        puts("=============Menu general===============");
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

            do
            {
                printf("DNI: ");
                fflush(stdin);
                scanf("%s", &auxString);

            }
            while(validarRangoDNI(auxString)== 0 || validarCaracteresEnEnteros(auxString)== 0);

            auxNodoMiembro=buscarNodoPorDniArbol(arbolMiembros,auxString);

            if(auxNodoMiembro == NULL) //si no existe retorno 0
            {
                imprimirMensajeRojo("Ese Dni no existe, desea crear una cuenta? s/n: ");
                fflush(stdin);
                scanf("%c",&opCrearCuenta);

                if(opCrearCuenta== 's')
                {
                    //si el usuario desea crearse una cuenta, la creamos y ya le activamos el menu

                    auxNodoMiembro=crearNodoArbol(crearUnMiembro(arbolMiembros));
                    arbolMiembros=insertarPorDni(arbolMiembros,auxNodoMiembro);
                }
            }

            limpiarPantalla();
            if(auxNodoMiembro != NULL)
            {
                menuUsuario(arregloEstanterias, arbolMiembros,auxNodoMiembro->dato,&prestamosInactivos);
            }



            break;
        case 3:
            informeFinal(arbolMiembros,arregloEstanterias);
            imprimirMensajeVerde("HA FINALIZADO CORRECTAMENTE EL PROGRAMA...");
            continuarBucle = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(continuarBucle != 'n');

    mostrarPila(prestamosInactivos);

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


    /*
    Para solucionar el problema de los prestamos inactivos y seguirlos teniendo en el archivo pero no en las filas de los libros
    propusimos, para implementar el TDA de pilas, guardar todos los prestamos inactivos en una pila y luego cuando se cierre el programa,
    guardarlos en el archivo. por lo tanto nos quedarian los activos primeros y a lo ultimo los prestamos inactivos en el archivo

    crear una libreria mas de pilas.

    */

    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        puts("=============Menu admin===============");
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
            menuPrestamos();
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

    printf("Seleccione una opcion\n");

    printf("[1] Actualizar Nombre \n");
    printf("[2] Actualizar Genero\n");
    printf("[3] Actualizar Autor \n");
    printf("[4] Actualizar Descripcion\n");
    printf("[5] Actualizar Estado \n"); // Activo o inactivo- No permitir poner que este prestado.
    printf("[6] Volver al menu de libros \n");
    puts("============================================================");

}

void actualizarLibro(estanteria arregloListas[])
{
    int opSw=0;
    char opCont='s';
    nodoSimple* buscado = inicListaSimple();
    do
    {
        puts("============================================================");

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
        case 6:
            opCont='n';
            limpiarPantalla();
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
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
            //buscarLibroXClave(arregloEstanterias); // Esto esta en duda ( yo lo dejaria para el final final )
            break;
        case 5:
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
        //limpiarPantalla();
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
        case 4: ///informes sobre miembros (hacer un menu)
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
        case 1:
            buscarMiembroXNombre(raiz);
            break;
        case 2:
            buscarMiembroXDNI(raiz);
            break;
        case 3:
            buscarMiembroXEstado(raiz);
            break;
        case 4:
            buscarMiembroXSaldo(raiz);
            break;
        case 5:
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
    puts("[1] Pedir un libro"); //es crear un prestamo
    puts("[2] Consultar prestamos"); //cuantos libros quedan de un determinado titulo, precio de los prestamos, si hay cola en un libro, cuanto tiempo de espera hay
    puts("[3] Devolver un libro");
    puts("[4] Modificar fecha de vencimiento de un prestamo");
    puts("[5] Volver al menu principal");
    puts("============================================================");

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
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }

    }
    while(opCont != 'n');

}

///menu usuario

void menuUsuario(estanteria arregloEstanterias[],nodoArbol * arbolMiembro, stMiembro miembroActual, pilaPrestamos*prestamosInactivos)///verificar si faltan alguna estructura mas...
{
    //aca va todo lo que puede hacer un usuario y deberiamos retornar el miembro, asi solo puede modificar el suyo

    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        puts("=============Menu usuario===============");
        printf("Bienvenido %s \n",miembroActual.datosPersonales.nombre);
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
            menuPrestamosUsuario();
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

    puts("[1] Devolver un libro"); //aumentar el contador de cantcopias +1
    puts("[2] Pedir un libro"); //es crear un prestamo, si el libro esta libre darselo y generar un prestamo, si no, meterlo en la fila de espera
    puts("[3] Buscar un libro"); //tenemos un menu
    puts("[4] Ver todos los libros disponibles en este momento"); // ver todos los que tienen la fila vacia
    puts("[5] Ver los libros que tienen cola de espera"); // ver todos los que tienen al menos un miembro en la fila
    puts("[6] Volver al menu principal");
    puts("================================================================");
}

void opcionesMenuUsuarioPrestamos()
{

    puts("[1] Ver mis prestamos activos");
    puts("[2] Ver limite de prestamos");
    puts("[3] Ver todo el historial de prestamos");
    puts("[4] Volver al menu principal");
    puts("===============================================");
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

void menuLibrosUsuario(estanteria arregloEstanterias[],stMiembro miembroActual,pilaPrestamos*prestamosInactivos,nodoArbol*arbolMiembros)
{
    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    char auxString[MAX_DIM];



    char opSeguirBuscando;
    int flag=0,i=0,continuarBucle=1;
    stLibro datoLibro;
    stMiembro datoMiembro;


    do
    {
        opcionesMenuUsuarioLibros();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();
        switch(opMenuPrin)
        {
        case 1:
            devolverUnLibroUsuario(miembroActual,arregloEstanterias,prestamosInactivos,arbolMiembros);
            break;
        case 2: //pedir un libro

            do
            {
                mostrarTodasLasEstanterias(arregloEstanterias);
                printf("Ingrese el nombre del libro que quiere: ");
                fflush(stdin);
                gets(auxString);

                while(i < 5 && flag==0)
                {
                    flag=verificarSiExisteLibroXNombre(arregloEstanterias[i].listaLibro,auxString);
                    if(flag==0) //verifico la flag debido a que quiero la posicion del arreglo tmb, y esto me lo hace
                    {
                        i++;
                    }
                }

                if(flag==0) // si no existe
                {
                    imprimirMensajeRojo("El nombre de ese libro no existe, desea buscar otro libro?: s/n");
                    fflush(stdin);

                    scanf("%c",&opSeguirBuscando);
                    if(opSeguirBuscando != 's')
                    {
                        continuarBucle=0; // si no desea seguir buscando corto el bucle
                    }
                }
                else // si lo encuentro corto el bucle
                {
                    continuarBucle=0;
                }


            }
            while(continuarBucle);


            /*
                        if(flag) // si encontre el libro
                        {

                            datoLibro=retornarLibroXNombre(arregloEstanterias[i].listaLibro,auxString);

                            // tercero verifico si tengo copias disponibles osea cantCopias != 0, si tengo se le da el libro al usuario de manera inmediata, se disminye la cantCopias en 1, se guarda en prestamosActivosID del miembro y se aumenta las vecesPrestado
                            // cuarto retorno el libro y habra que modificarle sus stats
                            if(verificarSiHayCopiasEnUnLibro(datoLibro)) //funcion verificar si tengo copias
                            {

                                crearUnPrestamo(datoMiembro.datosPersonales.dni);
                                datoMiembro.prestamosActivosID[datoMiembro.validosPrestamosActivosID]=datoLibro.idLibro;
                                //datoLibro.cantidadDeCopias-=1;
                                datoLibro.vecesPrestadoLibro+=1;

                                //poner el libro modificado en la estructura de nuevi

                            }
                            else //si no tengo copias
                            {
                                //funcion agregar a la fila
                                puts("No hay copias disponibles en este momento, vas a ser ingresado a la fila de espera");
                            }
                        }
            */

            break;
        case 3:
            buscarLibrosUsuario(arregloEstanterias);
            break;
        case 4:
            verLibrosDisponiblesUsuario(arregloEstanterias);
            break;
        case 5:
            //verLibrosConEsperaUsuario();
            break;
        case 6:
            opContinuarMenuPrin = 'n';
            break;
        default:
            imprimirMensajeRojo("Ingrese una opcion valida");
            break;
        }
    }
    while(opContinuarMenuPrin != 'n');
}

void menuMiembroUsuario(stMiembro miembroActual, nodoArbol* arbolMiembro)
{
    int opMenuPrin=0;
    char opContinuarMenuPrin='s';
    do
    {
        opcionesMenuUsuarioMiembro();
        opMenuPrin=preguntarDatoEntero();
        limpiarPantalla();

        nodoArbol* miembroModifcable = buscarNodoPorDniArbol(arbolMiembro, miembroActual.datosPersonales.dni);

        switch(opMenuPrin)
        {
        case 1:
            miembroModifcable = cambiarNombreMiembro(miembroModifcable);
            break;
        case 2:
            miembroModifcable = cambiarNumeroDeTelefonoMiembro(miembroModifcable, arbolMiembro);
            break;
        case 3:
            miembroModifcable = cambiarSaldoDeCuentaMiembro(miembroModifcable);
            break;
        case 4:
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
            //buscarLibrosXPopularidad(arregloEstanterias);
            break;
        case 5:
            //buscarLibroXClave(arregloEstanterias);
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
    puts("[4] Buscar libro por Popularidad");
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
        printf("Ingrese el ID que desea buscar");
        fflush(stdin);
        gets(idBuscado);

        ultimoID = retornarUltimoIDLibro(arregloEstanterias);
        idConvertido = convertirStringsDeNumerosAEntero(idBuscado);
    }
    while (validarCaracteresEnEnteros(idBuscado) == 0 || idConvertido > ultimoID);

    return idConvertido;
}

///informe final funciones

void informeFinal(nodoArbol*raiz,estanteria arregloEstanterias[])
{

    ///aca tenemos que hacer muchas funciones que cumplan con los requerimientos del informe
    puts("============================================================");
    printf("Total de miembros................. [%i]\n",contarMiembrosArbol(raiz));
    printf("Cantidad de miembros activos.......[%i]\n",contarMiembrosActivos(raiz));
    printf("Cantidad de miembros dados de baja:[%i]\n",contarMiembrosInactivos(raiz));
    printf("Total de libros....................[%i]\n",contarCantidadDeLibros(arregloEstanterias));
    printf("Total de prestamos.................[%i]\n",contarLibrosPrestados(arregloEstanterias));
    printf("Libro mas prestado.................[%i]\n");///Mostrar el titulo
    printf("Miembro con mayor sueldo...........[%i]\n");///Mostrar el DNI
    printf("Prestamo mas costoso...............[%i]\n");///Mostrar el ID
    printf("Miembro con mas prestamos..........[%i]\n");///Mostrar el DNI
    puts("============================================================");


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



int contarLibrosPrestados(estanteria arregloEstanterias[])
{

    int librosPrestados = 0;

    nodoSimple* aux = inicListaSimple();

    for (int i = 0; i < 5; i++)
    {


        aux = arregloEstanterias[i].listaLibro;
        while (aux != NULL)
        {
            if (aux->datoLibro.estado == 2)
            {

                librosPrestados++;
            }
            aux = aux->siguiente;

        }
    }

    return librosPrestados;
}





/// funciones devolver un prestamo

// primero tengo que ver todos los libros que tiene activo el miembro
// segundo le pregunto cual libro quiere devolver
// tercero hago todas las validaciones sobre q si el libro existe
// cuarto le modifico las stats al libro, le aumento las veces prestado, si no tiene nadie en la fila le cambio el estado, sino sigue el mismo estado
// quinto muevo el prestamo a la pila de prestamos inactivos


void devolverUnLibroUsuario(stMiembro miembroActual,estanteria arregloEstanterias[],pilaPrestamos*prestamosInactivos,nodoArbol*arbolMiembros)
{
    char opDevolver;
    miembroActual.prestamoActivoID=1;
//    if(validarSiExistePrestamoXId(arregloEstanterias,miembroActual.prestamoActivoID) != 0)
//    {

        stPrestamo auxPrestamo=retornarPrestamoXId(arregloEstanterias,miembroActual.prestamoActivoID);
        puts("Este es su prestamo activo: ");
        mostrarUnPrestamo(auxPrestamo);
        printf("Desea devolver el libro actual? s/n: ");
        fflush(stdin);
        scanf("%c",&opDevolver);
        if(opDevolver == 's')
        {

            modificarPrestamoActivoIDMiembroEnArbol(arbolMiembros,miembroActual.datosPersonales.dni,0);//modificar el prestamo activo a 0 ya que devolvio el libro

            auxPrestamo.estado=0; //tambien modifico el estado del prestamo a 0
            apilar(prestamosInactivos,auxPrestamo); // y lo guardo en la pila

            libroDevuelto(arregloEstanterias,auxPrestamo);

        }
//    }
//    else
//    {
//        puts("Usted no tiene ningun libro prestado");
//    }

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
