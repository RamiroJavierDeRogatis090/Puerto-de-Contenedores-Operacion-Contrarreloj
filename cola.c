#include "cola.h"

void crearCola(tCola *pC)
{
    pC->pri = NULL;
    pC->ult = NULL;
}

int colaLLena(const tCola *pC, unsigned cantBytes)
{
    char *auxDato;
    tNodo *auxNodo;

    auxNodo = malloc(sizeof(tNodo));

    if(auxNodo == NULL)
        return COLA_LLENA;

    auxDato = malloc(cantBytes);

    if(auxDato == NULL)
    {
        free(auxNodo);
        return COLA_LLENA;
    }

    return OK;
}

int colaVacia(const tCola *pC)
{
    return pC->pri == NULL;
}

int acolar(tCola *pC, const void *dato, unsigned cantBytes)
{
    tNodo *nodoNuevo;
    char *auxDato;

    if(pC == NULL || dato == NULL)
        return ERROR;

    nodoNuevo = malloc(sizeof(tNodo));

    if(nodoNuevo == NULL)
        return COLA_LLENA;

    auxDato = malloc(cantBytes);

    if(auxDato == NULL)
    {
        free(nodoNuevo);
        return COLA_LLENA;
    }

    nodoNuevo->tamDato = cantBytes;
    nodoNuevo->dato = auxDato;
    memcpy(nodoNuevo->dato, dato, cantBytes);

    nodoNuevo->sig = NULL;

    if(pC->pri == NULL)
        pC->pri = nodoNuevo;
    else
        pC->ult->sig = nodoNuevo;

    pC->ult = nodoNuevo;

    return ACOLADO;
}

int desacolar(tCola *pC, void *dato, unsigned cantBytes)
{
    tNodo *elim;
    unsigned tamCopiar;

    if(pC == NULL || dato == NULL)
        return ERROR;

    if(pC->pri == NULL)
        return COLA_VACIA;

    elim = pC->pri;

    tamCopiar = MIN(elim->tamDato, cantBytes);

    memcpy(dato, elim->dato, tamCopiar);

    pC->pri = elim->sig;

    free(elim->dato);
    free(elim);

    if(pC->pri == NULL)
        pC->ult = NULL;

    return DESACOLADO;
}

int verPrimeroEnCola(const tCola *pC, void *dato, unsigned cantBytes)
{
    tNodo *nodo;
    unsigned tamCopiar;

    if(pC == NULL || dato == NULL)
        return ERROR;

    if(pC->pri == NULL)
        return COLA_VACIA;

    nodo = pC->pri;

    tamCopiar = MIN(nodo->tamDato, cantBytes);

    memcpy(dato, nodo->dato, tamCopiar);

    return OK;
}

void vaciarCola(tCola *pC)
{
    tNodo *elim;

    if(pC != NULL)
    {
        while(pC->pri != NULL)
        {
            elim = pC->pri;
            free(elim->dato);
            pC->pri = elim->sig;
            free(elim);
        }
    }
}












