#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "filaReservas.h"

void inicFila(filaReservas*reservas)
{
    reservas->primero=inicListaDoble();
    reservas->ultimo=inicListaDoble();
}


