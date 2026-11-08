#ifndef COMANDO_H_INCLUDED
#define COMANDO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuracion.h"
#include "escenario.h"
#include "simulacion.h"
#include "estructuras.h"
#include "pila.h"
#include "cola.h"
#include "lista.h"


#define TAM_OP 4
#define TAM_COMANDO 15
#define TAM_ORIGEN 4
#define TAM_DESTINO 4

/// -- Auxiliares --
#define NO_ENCONTRADO -1

/// -- Salidas --
#define IGUALES 0
#define ERROR_PARAMETRO 0

/// Defines
#define CMD_INVALIDO -1
#define CMD_DES 1
#define CMD_ENT 2
#define CMD_REU 3
#define CMD_ESP 4
#define CMD_VER 5

typedef struct
{
    char op[TAM_OP];
    unsigned t_inicio;
    unsigned t_fin;
    char contenedor[TAM_CONTENEDOR];
    char origen[TAM_ORIGEN];
    char destino[TAM_DESTINO];
}tHistorial;

void operaciones(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo);
int comandoEntregar(tSimulacion *sim);
int _buscarMuelle(tMuelle *muelles, unsigned cantMuelles, const char *codMuelle);
int comandoDescargar(tSimulacion *sim, const char *codMuelle, const char *codZona, tPuntos *puntaje);
int comandoReubicar(tSimulacion *sim, const char *codZonaA, const char *codZonaB);
int comandoVer(tSimulacion *sim);

#endif // COMANDO_H_INCLUDED
