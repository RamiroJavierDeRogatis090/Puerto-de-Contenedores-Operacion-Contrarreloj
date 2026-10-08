#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED

#define ESC_GEN 1
#define ESC_CAR 1
#define ERR_ALM_BUQ 0
#define ERR_ALM_CONT 0
#define ERR_ALM_CAM 0
#define ARRIBO_MENOR   -1
#define ARRIBO_IGUAL    0
#define ARRIBO_MAYOR    1

#include "pila.h"
#include "lista.h"
#include "cola.h"
#include "configuracion.h"


typedef struct
{
    tLista arribos;
} tEscenario;


int escenario_generar(tConfig cfg, const char*arch);
int escenario_cargar(const char*arch, tEscenario*p);
int cmpArribo(const void*d1, const void*d2);




#endif // ESCENARIO_H_INCLUDED
