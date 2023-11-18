#ifndef LISTADOBLERESERVAS_H_INCLUDED
#define LISTADOBLERESERVAS_H_INCLUDED
#define MAX_DIM 26

///Estructura prestamos

typedef struct{

    int diaTiempo;
    int mesTiempo;
    int anioTiempo;

} stFecha;

typedef struct{

    int idPrestamo;
    int estado; // 0 de baja y 1 activo
    char dniUsuarioPrestado[MAX_DIM]; //dni del miembro al que le prestamos el libro
    char precioPrestamo[MAX_DIM];

    stFecha inicioPrestamo;
    stFecha vencimientoPrestamo;

} stPrestamo;


typedef struct
{
    stPrestamo datoPrestamo;
    struct nodoDoble*anterior;
    struct nodoDoble*siguiente;

} nodoDoble;


///funciones estructura prestamos

stPrestamo crearUnPrestamo(char dniUsuarioPrestadoAux[]);

//mostrar
void mostrarUnaFecha(stFecha aux);
void mostrarUnPrestamo(stPrestamo aux);

void asignarTiempo(stFecha * aux,struct tm * info_tiempo);
void calcularVencimiento(stFecha *vencimiento, stFecha inicio,int duracionPrestamo);

///funciones lista doble

//basicas
nodoDoble*inicListaDoble();
nodoDoble*crearNodoDoble(stPrestamo aux);
void mostrarListaDoble(nodoDoble*listaDoble);

//insertar
nodoDoble*agregarAlPpioDoble(nodoDoble*listaDoble, nodoDoble*nuevoNodo);
nodoDoble*agregarAlFinalDoble(nodoDoble*listaDoble,nodoDoble*nuevoNodo);


//buscar
nodoDoble*buscarUltimoNodoDoble(nodoDoble*listaDoble);

//borrar
nodoDoble*borrarPrimerNodoDoble(nodoDoble*listaDoble);


//validaciones
int validarDias(int dias);
int validarPrecioPrestamo(char aux[]);

///Funciones archivo
int retornarUltimoIDPrestamo();

#endif // LISTADOBLERESERVAS_H_INCLUDED
