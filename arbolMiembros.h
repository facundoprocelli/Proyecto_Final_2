#ifndef ARBOLMIEMBROS_H_INCLUDED
#define ARBOLMIEMBROS_H_INCLUDED
#define MAX_DIM 26
///Estructura miembros

typedef struct
{

    char nombre[MAX_DIM];
    char direccion[MAX_DIM];
    char numeroDeTelefono[MAX_DIM];
    char dni[MAX_DIM];

} stPersona;

typedef struct
{

    stPersona datosPersonales;
    int historialDelPrestamo[100];///CHECKEAR SI USAR ARREGLO U OTRO TIPO DE DATO POR EL TAMA�O FIJO,Arreglo con las ID de los prestamos que leyo(luego si quiere ver el libro lo busca por ID en un archivo)
    int estado; //activo o de baja
    int saldo;// es el dinero que el miembro ingreso a la cuenta, se debera utilizar dinero para los prestamos, si no tiene, no puede pagar un prestamo
    int prestamosActivos; // nro de cuantos prestamos tiene activos/en propiedad
    int limitePrestamos; // el usuario decide el limite de prestamos que tendra esta persona

} stMiembro;

// Estrutura Arbol

typedef struct
{

    stMiembro dato;
    struct nodoArbol* derecha;
    struct nodoArbol* izquierda;

} nodoArbol;


// Estructura Persona

stPersona crearUnaPersona();
void mostrarUnaPersona(stPersona aux);
void mostrarUnMiembro(stMiembro aux);

///Estructura Miembro

stMiembro crearUnMiembro();


///Estructura Arbol
//basicas
nodoArbol *inicArbol();
nodoArbol *crearNodoArbol(stMiembro miembro);

//busqueda y muestra
nodoArbol * buscarNodoPorDniArbol(nodoArbol * raiz, char dniMiembro[]);

void mostrarArbolPreorden(nodoArbol *raiz);
void mostrarArbolInorden(nodoArbol *raiz);
void mostrarArbolPostorden(nodoArbol *raiz);

//insertar y borrar
nodoArbol * insertarPorDni(nodoArbol * raiz,nodoArbol * nuevo);
nodoArbol * borrarUnNodoPorDni(nodoArbol * raiz,char dniMiembro[]);

nodoArbol* nodoMasDerechaArbol(nodoArbol*raiz);
nodoArbol* nodoMasIzquierdaArbol(nodoArbol*raiz);

//consultas
int esHoja(nodoArbol*raiz);
int esGradoUnoArbol(nodoArbol*raiz);
int estaLlenoArbol(nodoArbol*raiz);
int arbolVacio(nodoArbol*raiz);
int contarMiembrosArbol(nodoArbol* raiz);

///validaciones
int validarRangoDeNombre(char nombreAux[]);///tamaño del nombre
int validarDigitosEnStrings(char nombreAux[]);///Que no se encuentren numeros en un nombre
int validarRangoDNI(char dniAux[]);
int validarCaracteresEnEnteros(char aux[]);
int validarRangoTelefono(char telefono[]);
int validarDentroDeUnRango(int dato,int minimo,int maximo);
int validarEstadoMiembro(int estadoAux);
int validarLimitePrestamoMiembro(int limiteAux);

///archivos
void cargarUnMiembroAlArchivo(stMiembro aux);
nodoArbol * archivoAlArbol(nodoArbol * raiz);
void mostrarArchivoDeMiembros();
void arbolAlArchivo(nodoArbol * raiz);
void escribirArchivoArbol(nodoArbol * raiz,FILE * buffer);


///modificaciones
nodoArbol * menuDeModificaciones(nodoArbol * raiz,char dniAModificar[]);
void opcionesMenuActualizarMiembros();
nodoArbol * actualizarUnMiembroDatosPersonales(nodoArbol * aux);
void opcionesActualizarUnMiembro();
nodoArbol * actualizarUnMiembroCampos(nodoArbol * aux);
void opcionesActualizarUnMiembroCampos();







#endif //ARBOLMIEMBROS_H_INCLUDED
