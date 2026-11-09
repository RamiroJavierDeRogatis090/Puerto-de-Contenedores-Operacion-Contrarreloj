#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCH_OPERADORES "operadores.dat"
#define ARCH_INDICE "indice.dat"
#define ARCH_JORNADAS "jornadas.dat"
#define ARCH_CONFIGURACION "config.txt"
#define ARCH_PUERTO "puerto.txt"

#define ERROR_APERTURA 0
#define TODO_OK 1

int abrirArchivo(FILE **pf, const char *nombreArchivo, const char *modo);

#endif // ARCHIVO_H_INCLUDED
