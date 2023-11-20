#ifndef PILAPRESTAMOSINACTIVOS_H_INCLUDED
#define PILAPRESTAMOSINACTIVOS_H_INCLUDED
#define MAX_DIM 26

///Estructura prestamos
typedef struct{

    int diaTiempo;
    int mesTiempo;
    int anioTiempo;

} stFecha;


typedef struct{

    int idPrestamo; //id propio
    int idLibro; //id del libro prestado
    int estado; // 0 inactivo y 1 activo
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

///estructura de pila

typedef struct
{
    nodoDoble * prestamoInactivo;//lista doble

} pilaPrestamos;



///funciones de pilas
void inicPila(pilaPrestamos * pila);//inicializa la lista que tiene la pila en null
void archivoAPila(pilaPrestamos * pila);//no pasarle un dato ya que lo agarramos desde el archivo
void mostrarPila(pilaPrestamos pila);//muestra los prestamos inactivos
void apilar(pilaPrestamos * pila,stPrestamo aux);//los prestamos que sean de estado 0 que se encuentren en la fila, los pasamos directamente a la pila.
void cargarPilaAlArchivo(pilaPrestamos * pila);//De la pila lo pasamos a un archivo que sea de prestamos inactivos para tener un registro

#endif // PILAPRESTAMOSINACTIVOS_H_INCLUDED
