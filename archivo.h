#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_APERTURA 0
#define TODO_OK 1

int abrirArchivo(FILE **pf, const char *nombreArchivo, const char *modo);

#endif // ARCHIVO_H_INCLUDED
