#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

/// DEFINICIONES DE LISTA SIMPLE ENTRELAZADA DINAMICA

#include <stdlib.h>
#include <string.h>
#include "nodo.h"

#define MINIMO(x,y) (x) <= (y) ? (x) : (y)

#define MEMORIA_LLENA 0
#define LISTADO 1
#define HAY_ESPACIO 1
#define MISMO_DATO 0
#define LISTA_VACIA 0
#define ELIMINADO 1
#define VISTO 1
/*
typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
}tNodo;*/

typedef tNodo* tLista;

void CrearLista(tLista *lista);
int ListaVacia(const tLista *pl);
int ListaLlena(const tLista *pl, unsigned cantBytes);
void VaciarLista(tLista *pl);
int InsertarAlFinalLista(tLista *pl, const void *dato, unsigned cantBytes);
int EliminarUltimoLista(tLista *pl);
int insertarAlComienzo(tLista *pl, const void *dato, unsigned cantBytes);
int verPrimeroLista(tLista *pl, void *dato, unsigned cantBytes);
int verUltimoLista(tLista *pl, void *dato, unsigned cantBytes);

int InsertarEnOrdenLista(tLista *pl, void *dato, unsigned cantBytes, int cmp(const void*, const void*));
int InsertarAlFinalListaSinDuplicados(tLista *pl, const void *dato, unsigned cantBytes, int cmp(const void*, const void*));

#endif // LISTA_H_INCLUDED
