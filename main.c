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

    switch(opSw)
    {
    case 1:
        biblioteca();
        break;
    case 2:
        menuUsuario();
        break;
    default:
        break;
    }
    return 0;
}



