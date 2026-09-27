#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "nodo.h"

#define HAY_ESPACIO 1
#define PILA_LLENA 0
#define PILA_VACIA 0
#define APILADO 1
#define DESAPILADO 1
#define MIN(x,y) (x) <= (y) ? (x) : (y)
#define ERROR 0
#define OK 1

/*
typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
}tNodo;*/

typedef tNodo* tPila;

void crearPila(tPila *pl);
int pilaVacia(const tPila *pl);
int pilaLlena(const tPila *pl, unsigned cantBytes);
void vaciarPila(tPila *pl);
int apilar(tPila *pl, const void *dato, unsigned tam);
int desapilar(tPila *pl, void *dato, unsigned cantBytes);
int verTope(const tPila *pl, void *dato, unsigned cantBytes);

#endif // PILA_H_INCLUDED
