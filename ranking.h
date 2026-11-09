#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operador.h"
#include "arbol.h"
#include "archivo.h"

typedef struct
{
    unsigned puesto;
}tRanking;

int compararOperadoresRanking(const void *a, const void *b);
void mostrarOperadorRanking(void *info, unsigned tam, unsigned n, void *params);
int mostrarRanking(const char *nombreArchivo);

#endif // RANKING_H_INCLUDED
