#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"




int main()
{
    int opSw=0;
    int flag=1;

    char auxString[MAX_DIM];

//    do
//    {

    printf("\t\t\t ||Bienvenido a la Biblioteca BookMaze||\n");
    printf("\t\t      =============================================\n\n");


//    printf("Que tipo de cuenta es? ");
//    printf("[1] Administrador \n");
//    printf("[2] Usuario \n");
//    puts("----------------------------");
//    printf("Ingrese una opcion: ");
//    scanf("%i",&opSw);
//
//    switch(opSw)
//    {
//    case 1:
//
//        printf("Ingrese la contrasenia del admin: ");
//        fflush(stdin);
//        scanf("%s",&auxString);
//
//        if(strcmpi(auxString,"BookMaze")==0)
//        {
//
//        }
//        else
//        {
//            puts("Contrasenia incorrecta");
//        }
//
//        break;
//    case 2:
//
//        printf("Si usted no es miembro debera registrarse primero");
//        printf("Ingrese su DNI:");
//        fflush(stdin);
//        scanf("%s",&auxString);
//
//
//
//
//
//
//        break;
//    default:
//        puts("Ingrese una opcion correcta");
//        break;
//    }
//
//    }while(flag);


    puts("[1] Admin");
    puts("[2] Usuario");

    opSw=preguntarDatoEntero();


    /// Cargar Estanterias
    cargarLibrosPredeterminados(); // se cargan los libros automaticamente
    estanteria arregloEstanterias[5];
    inicEstanterias(arregloEstanterias); /// a la iniciacion tmb deberiamos agregar las reservas de los libros pero todavia no lo tenemos
    archivoAEstanteria(arregloEstanterias); // Se pasan los libros a la estanteria

    /// Cargar Arbol Miembros
    nodoArbol * arbolMiembros=inicArbol();
    arbolMiembros=archivoAlArbol(arbolMiembros); //pasamos los miembros al arbol



    switch(opSw)
    {
    case 1:
        biblioteca(arregloEstanterias, arbolMiembros);
        break;
    case 2:
        menuUsuario(arregloEstanterias, arbolMiembros);
        break;
    default:

        break;
    }
    return 0;
}



