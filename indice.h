#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"
#include "archivo.h"
#include "operador.h"  ///PORQUE YA TIENE MAX_TAM_NOMBRE

#define MAX_TAM_NOMBRE 50

#define ERROR_ARCHIVO_INDICE 0
#define TODO_OK 1
#define CLAVE_NO_ENCONTRADA 0
#define CLAVE_ENCONTRADA 1

typedef struct
{
    char nombre[MAX_TAM_NOMBRE];
}tClave;

typedef struct
{
    tClave clave;
    unsigned indiceRegistro;
}tIndice;

int compararClaveIdx(const void *a, const void *b);
int indexarArchivoOrdenado(tArbol *pa, const char *nombreArchivo);
void cargarArchivoEnIndice(tArbol *pa, FILE *arch, int inicio, int fin);
int grabarIndiceEnArchivo(const tArbol *pa, const char *nombreArchivo);
void grabarNodoEnArchivo(void *info, unsigned tam, unsigned n, void *params);
int registrarNuevoUsuarioEnIndice(tArbol *pa, const char *nombre, unsigned posNueva, const char *nombreArchivoIndice);

#endif // INDICE_H_INCLUDED
