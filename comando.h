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

///Defines
#define TAM_OP 4
#define TAM_COMANDO 15
#define TAM_ORIGEN 4
#define TAM_DESTINO 4
#define OP_DESCARGAR            "DES"
#define OP_ENTREGAR             "ENT"
#define OP_REUBICAR             "REU"
#define OP_ESPERAR              "ESP"
#define OP_VER                  "VER"
#define CANT_CAMIONES_VISIBLES  3
#define TIEMPO_ESPERA           1
#define SEPARADOR_CONTENEDORES  "|"
#define SIN_DATO       "-"
#define LINEA_TABLA    "------------------------------------------------------"

#define NO_ENCONTRADO -1
#define IGUALES 0
#define ERROR_PARAMETRO 0

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

void operaciones(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo, tCola *historialOp);
int comandoEntregar(tSimulacion *sim, tHistorial *opActual);
int buscarMuelle(tMuelle *muelles, unsigned cantMuelles, const char *codMuelle);
int comandoDescargar(tSimulacion *sim, const char *codMuelle, const char *codZona, tPuntos *puntaje, tHistorial *opActual);
int comandoReubicar(tSimulacion *sim, const char *codZonaA, const char *codZonaB, tHistorial *opActual);
int comandoVer(tSimulacion *sim);
void mostrarEstadoTurno(tSimulacion *sim, unsigned tiempo);
void mostrarHistorialOperaciones(tCola *historialOp);


#endif // COMANDO_H_INCLUDED
