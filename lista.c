#include "lista.h"

void CrearLista(tLista *lista)
{
    *lista = NULL;
}

int InsertarAlFinalLista(tLista *pl, const void *dato, unsigned cantBytes)
{
    tNodo *nodoNuevo;

    while(*pl != NULL)
    {
        pl = &(*pl)->sig;
    }

    nodoNuevo = (tNodo*) malloc(sizeof(tNodo));

    if(nodoNuevo == NULL)
        return MEMORIA_LLENA;

    nodoNuevo->dato = malloc(cantBytes);

    if(nodoNuevo->dato == NULL)
    {
        free(nodoNuevo);
        return MEMORIA_LLENA;
    }

    memcpy(nodoNuevo->dato, dato, cantBytes);
    nodoNuevo->tamDato = cantBytes;
    nodoNuevo->sig = NULL;

    *pl = nodoNuevo;

    return LISTADO;
}

void VaciarLista(tLista *pl)
{
    tNodo *elim;

    while(*pl != NULL)
    {
        elim = *pl;
        *pl = elim->sig;

        free(elim->dato);
        free(elim);
    }
}

int ListaVacia(const tLista *pl)
{
    return *pl == NULL;
}

int ListaLlena(const tLista *pl, unsigned cantBytes)
{
    tNodo *nodo;

    nodo = (tNodo*) malloc(sizeof(tNodo));

    if(nodo == NULL)
        return MEMORIA_LLENA;

    nodo->dato = malloc(cantBytes);

    if(nodo->dato == NULL)
    {
        free(nodo);
        return MEMORIA_LLENA;
    }

    free(nodo->dato);
    free(nodo);

    return HAY_ESPACIO;
}
int InsertarEnOrdenLista(tLista *pl, void *dato, unsigned cantBytes, int cmp(const void*, const void*))
{
    tNodo *nodoNuevo;
    int comparador;

    while(*pl != NULL && (comparador = cmp((*pl)->dato, dato)) < 0)
    {
        pl = &(*pl)->sig;
    }

    nodoNuevo = (tNodo*) malloc(sizeof(tNodo));

    if(nodoNuevo == NULL)
        return MEMORIA_LLENA;

    nodoNuevo->dato = malloc(cantBytes);

    if(nodoNuevo == NULL)
    {
        free(nodoNuevo->dato);
        return MEMORIA_LLENA;
    }

    memcpy(nodoNuevo->dato, dato, cantBytes);
    nodoNuevo->tamDato = cantBytes;
    nodoNuevo->sig = *pl;

    *pl = nodoNuevo;

    return LISTADO;
}

int InsertarAlFinalListaSinDuplicados(tLista *pl, const void *dato, unsigned cantBytes, int cmp(const void*, const void*))
{
    tNodo *nodoNuevo;
    int comparador = 1;

    while(*pl != NULL && (comparador = cmp((*pl)->dato, dato)) != 0)
    {
        pl = &(*pl)->sig;
    }

    if(comparador == 0)
        return MISMO_DATO;

    nodoNuevo = (tNodo*) malloc(sizeof(tNodo));

    if(nodoNuevo == NULL)
        return MEMORIA_LLENA;

    nodoNuevo->dato = malloc(cantBytes);

    if(nodoNuevo->dato == NULL)
    {
        free(nodoNuevo);
        return MEMORIA_LLENA;
    }

    memcpy(nodoNuevo->dato, dato, cantBytes);
    nodoNuevo->tamDato = cantBytes;
    nodoNuevo->sig = NULL;

    *pl = nodoNuevo;

    return LISTADO;
}

int EliminarUltimoLista(tLista *pl)
{
    tNodo *elim;

    if(*pl == NULL)
        return LISTA_VACIA;

    while((*pl)->sig != NULL)
    {
        pl = &(*pl)->sig;
    }

    elim = *pl;

    free(elim->dato);
    free(elim);

    return ELIMINADO;
}

int insertarAlComienzo(tLista *pl, const void *dato, unsigned cantBytes)
{
    tNodo *nuevoNodo;

    if(*pl == NULL)
        return LISTA_VACIA;

    nuevoNodo = (tNodo*) malloc(sizeof(tNodo));

    if(nuevoNodo == NULL)
        return MEMORIA_LLENA;

    nuevoNodo->dato = malloc(cantBytes);

    if(nuevoNodo->dato == NULL)
    {
        free(nuevoNodo);
        return MEMORIA_LLENA;
    }

    nuevoNodo->sig = *pl;
    memcpy(nuevoNodo->dato, dato, cantBytes);
    nuevoNodo->tamDato = cantBytes;
    *pl = nuevoNodo;

    return LISTADO;
}

int verPrimeroLista(tLista *pl, void *dato, unsigned cantBytes)
{
    if(*pl == NULL)
        return LISTA_VACIA;

    memcpy(dato, (*pl)->dato, MINIMO((*pl)->tamDato, cantBytes));

    return VISTO;
}

int verUltimoLista(tLista *pl, void *dato, unsigned cantBytes)
{
    if(*pl == NULL)
        return LISTA_VACIA;

    while((*pl)->sig != NULL)
        pl = &(*pl)->sig;

    memcpy(dato, (*pl)->dato, MINIMO((*pl)->tamDato, cantBytes));

    return VISTO;
}



