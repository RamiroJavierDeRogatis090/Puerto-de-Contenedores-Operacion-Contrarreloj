#ifndef ESCENARIO_H_INCLUDED
#define ESCENARIO_H_INCLUDED

#define MEM_INS 1
#define ESC_GEN 1
#define ESC_CAR 1
#define ERR_ALM_BUQ 0
#define ERR_ALM_CONT 0
#define ERR_ALM_CAM 0
#define ARRIBO_MENOR   -1
#define ARRIBO_IGUAL    0
#define ARRIBO_MAYOR    1

#include <time.h>
#include "configuracion.h"
#include "estructuras.h"
#include "pila.h"
#include "cola.h"
#include "lista.h"


typedef struct
{
    unsigned duracionJornada;
    unsigned cantMuelles;
    unsigned cantZonas;
    unsigned capacidadPila;
    tLista arribos;
}tEscenario;


typedef struct
{
    unsigned nroBuque;
    unsigned nroCont;
} tRefContenedor;


int escenario_generar(tConfig cfg, const char*arch);
int escenario_cargar(const char* arch, tEscenario* p, tConfig *conf);
int cmpArribo(const void*d1, const void*d2);
void guardarBuque(char *linea, tBuque *buque, tArribo *arribo);
void guardarCamion(char *linea, tCamion *camion, tArribo *arribo);




#endif // ESCENARIO_H_INCLUDED
