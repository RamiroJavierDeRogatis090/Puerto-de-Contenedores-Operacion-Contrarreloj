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

/// -- Auxiliares --
#define NO_ENCONTRADO -1

/// -- Salidas --
// #define OK 0 -> Me apareció un WARNING pq ya se definió en otro archivo
#define IGUALES 0
#define ERROR_PARAMETRO 1001
#define PUERTO_VACIO 1002
#define ZONA_LLENA 1003
#define ERROR_MEMORIA 1004

/// -- Tamaños de string --
#define TAM_OP 4
#define TAM_COMANDO 15
#define TAM_ORIGEN 4
#define TAM_DESTINO 4

/// -- Subindices de if's --
#define CMD_INVALIDO -1
#define CMD_DES 1
#define CMD_ENT 2
#define CMD_REU 3
#define CMD_ESP 4
#define CMD_VER 5

/// -- Subindices de switch--
#define DES 0
#define ENT 1
#define REU 2
#define ESP 3
#define VER 4

typedef struct
{
    char op[TAM_OP];
    unsigned t_inicio;
    unsigned t_fin;
    char origen[TAM_ORIGEN];
    char destino[TAM_DESTINO];
}tHistorial;

int comandoEntregar(tSimulacion *sim, const char *origen, const char *destino);
int _buscarMuelle(tMuelle *muelles, unsigned cantMuelles, const char *codMuelle);
tZona * _buscarZona(tLista *zonas, const char *codZona);
int comandoDescargar(tSimulacion *sim, const char *codMuelle, const char *codZona);
int comandoReubicar(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo);
int comandoVer(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo);
void operaciones(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo);

#endif // COMANDO_H_INCLUDED
