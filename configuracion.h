#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

///Bibliotecas incluidas

#include <stdio.h>
#include <string.h>

///MACROS

#define ERR_ARCH 0
#define LECT_OK 1
#define TAM_LINEA 100
#define TAM_CLAVE 50
#define TAM_LIS_CONT 200

#include "pila.h"
#include "lista.h"
#include "cola.h"


typedef struct
{
    unsigned duracionJornada;

    unsigned cantMuelles;
    unsigned cantZonas;
    unsigned capacidadPila;

    unsigned maxBuques;
    unsigned maxContPorBuque;
    unsigned maxCamiones;

    unsigned tiempDesCont;
    unsigned tiempReuCont;
    unsigned tiempCarCami;

} tConfig;



int configLeer(const char* arch,tConfig* salida);


#endif // CONFIGURACION_H_INCLUDED
