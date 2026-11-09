#ifndef JORNADA_H_INCLUDED
#define JORNADA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulacion.h"
#include "indice.h"

#define JORNADA_GUARDADA 1
#define ERROR_OPERADOR_JORNADA -1
#define ERROR_ARCHIVO_JORNADAS -2
#define ERROR_ESCRITURA_JORNADA -3
#define SIN_JORNADAS 0
#define ERROR_LECTURA_JORNADAS -4

typedef struct
{
    unsigned indiceOperador;
    tPuntos resultado;
    unsigned tiempoUtilizado;
}tJornada;

int guardarJornada(const tArbol *pa, const char *nombreOperador, const tPuntos *resultado, unsigned tiempoUtilizado, const char *nombreArchivo);
int mostrarJornadasOperador(const char *nombreArchivo, unsigned indiceOperador);

#endif // JORNADA_H_INCLUDED
