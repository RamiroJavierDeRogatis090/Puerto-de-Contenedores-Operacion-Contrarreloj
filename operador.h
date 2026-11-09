#ifndef OPERADOR_H_INCLUDED
#define OPERADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arbol.h"

#define MAX_TAM_NOMBRE 50

#define NOMBRE_INVALIDO -2
#define ERROR_LECTURA_OPERADOR -3
#define OPERADOR_EXISTENTE 2
#define OPERADOR_REGISTRADO 3
#define ERROR_ESCRITURA_OPERADOR -4
#define ERROR_ACTUALIZACION_INDICE -5
#define ERROR_INICIALIZACION -6
#define ERROR_ACTUALIZACION_OPERADOR -7
#define OPERADOR_ACTUALIZADO 4
#define ERROR_RANKING -8

typedef struct
{
    char nombre[MAX_TAM_NOMBRE];
    int puntajeAcumulado;
}tOperador;

char *normalizarNombre(char* cad);
int buscarOperador(const tArbol *pa, const char *nombre, tOperador *operador, const char *nombreArchivo);
int registrarOperador(tArbol *pa, const char *nombre, tOperador *operador, const char *nombreArchivo, const char *nombreArchivoIdx);
int iniciarGestionOperadores(tArbol *pa, const char *nombreArchivo, const char *nombreArchivoIdx);
int obtenerOperadorActual(tArbol *pa, const char *nombre, tOperador *operador, const char *nombreArchivo, const char *nombreArchivoIdx);
int actualizarPuntajeOperador(const tArbol *pa, tOperador *operador, int puntos, const char *nombreArchivo);

#endif // OPERADOR_H_INCLUDED
