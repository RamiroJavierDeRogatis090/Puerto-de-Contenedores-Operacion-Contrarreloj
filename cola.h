#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "nodo.h"

#define COLA_LLENA 0
#define COLA_VACIA 0
#define OK 1
#define ACOLADO 1
#define DESACOLADO 1
#define ERROR 0
#define MIN(x,y) (x) <= (y) ? (x) : (y)

typedef struct
{
    tNodo *pri;
    tNodo *ult;
}tCola;

void crearCola(tCola *pC);
int colaLLena(const tCola *pC, unsigned cantBytes);
int colaVacia(const tCola *pC);
int acolar(tCola *pC, const void *dato, unsigned cantBytes);
int desacolar(tCola *pC, void *dato, unsigned cantBytes);
int verPrimeroEnCola(const tCola *pC, void *dato, unsigned cantBytes);
void vaciarCola(tCola *pC);

#endif // COLA_H_INCLUDED
