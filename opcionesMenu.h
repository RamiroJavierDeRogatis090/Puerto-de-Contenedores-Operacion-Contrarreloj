#ifndef OPCIONESMENU_H_INCLUDED
#define OPCIONESMENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivo.h"
#include "configuracion.h"
#include "escenario.h"
#include "simulacion.h"
#include "jornada.h"
#include "ranking.h"

int ejecutarOpcionJornada(tArbol *indiceOperadores, tOperador *operadorActual);
int ejecutarOpcionRanking(const char *nombreArchivo);
int ejecutarOpcionHistorial(tArbol *indiceOperadores, const tOperador *operadorActual);

#endif // OPCIONESMENU_H_INCLUDED
