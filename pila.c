#include "pila.h"

void crearPila(tPila *pl)
{
    *pl = NULL;
}

int pilaVacia(const tPila *pl)
{
    return *pl == NULL;
}

int pilaLlena(const tPila *pl, unsigned cantBytes)
{
    char *auxDato;
    tNodo *auxNodo;

    auxNodo = malloc(sizeof(tNodo));

    if(auxNodo == NULL)
        return PILA_LLENA;

    auxDato = malloc(cantBytes);

    if(auxDato == NULL)
    {
        free(auxNodo);
        return PILA_LLENA;
    }

    free(auxDato);
    free(auxNodo);
    return HAY_ESPACIO;
}

int apilar(tPila *pl, const void *dato, unsigned tam)
{
    tNodo *nodoNuevo;

    if(dato == NULL)
        return ERROR;

    nodoNuevo = (tNodo*) malloc(sizeof(tNodo));

    if(nodoNuevo == NULL)
        return PILA_LLENA;

    nodoNuevo->dato = malloc(tam);

    if(nodoNuevo->dato == NULL)
    {
        free(nodoNuevo);
        return PILA_LLENA;
    }

    nodoNuevo->sig = *pl;
    memcpy(nodoNuevo->dato, dato, tam);
    nodoNuevo->tamDato = tam;
    *pl = nodoNuevo;

    return APILADO;
}

int desapilar(tPila *pl, void *dato, unsigned cantBytes)
{
    tNodo *elim;

    if(*pl == NULL)
        return PILA_VACIA;

    elim = *pl;

    memcpy(dato, elim->dato, MIN(elim->tamDato, cantBytes));

    *pl = elim->sig;

    free(elim->dato);
    free(elim);

    return DESAPILADO;
}

void vaciarPila(tPila *pl)
{
    tNodo *elim;
    while(*pl != NULL)
    {
        elim = *pl;
        free(elim->dato);
        *pl = elim->sig;
        free(elim);
    }
}

int verTope(const tPila *pl, void *dato, unsigned cantBytes)
{
    tNodo *nodo;

    if(*pl == NULL)
        return PILA_VACIA;

    nodo = *pl;
    memcpy(dato, nodo->dato, MIN(nodo->tamDato, cantBytes));

    return OK;
}




