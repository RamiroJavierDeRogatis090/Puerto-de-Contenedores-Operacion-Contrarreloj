#ifndef COMANDOS_H_INCLUDED
#define COMANDOS_H_INCLUDED

///Biblotecas
#include "simulacion.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

///Defines
#define DAT_MOS 1
#define DAT_INV 0

int _comandoVer(const tSimulacion* simulacion,const tPuntos* puntos,unsigned cronometro);

#endif // COMANDOS_H_INCLUDED
