#include "arbol.h"

void crearArbol(tArbol *pa)
{
    *pa = NULL;
}

int insertarEnArbol(tArbol *pa, const void *d, unsigned tam, int (*comparar)(const void *, const void *))
{
    tNodoArbol *nue;
    int cmp;
    while(*pa)
    {
        cmp = comparar((*pa)->info, d);
        if(cmp > 0)
        {
            pa = &(*pa)->izq;
        }
        else
        {
            if(cmp < 0)
            {
                pa = &(*pa)->der;
            }
            else
            {
                return CLA_DUP;
            }
        }
    }
    nue = (tNodoArbol *)malloc(sizeof(tNodoArbol));
    if(nue == NULL)
    {
        return SIN_MEM;
    }
    nue->info = malloc(tam);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info, d, tam);
    nue->tamInfo = tam;
    nue->izq = NULL;
    nue->der = NULL;
    *pa = nue;
    return TODO_OK;
}

void recorrerInOrden(const tArbol *pa, unsigned n, void *params, void (*accion)(void *, unsigned, unsigned, void *))
{
    if(*pa == NULL)
    {
        return;
    }
    recorrerInOrden(&(*pa)->izq, n, params, accion);
    accion((*pa)->info, (*pa)->tamInfo, n, params);
    recorrerInOrden(&(*pa)->der, n, params, accion);
}

int buscarEnArbol(const tArbol *pa, void *d, unsigned tam, int (*comparar)(const void *, const void *))
{
    int cmp;
    while(*pa)
    {
        cmp = comparar((*pa)->info, d);
        if(cmp > 0)
        {
            pa = &(*pa)->izq;
        }
        else
        {
            if(cmp < 0)
            {
                pa = &(*pa)->der;
            }
            else
            {
                memcpy(d, (*pa)->info, MINIMO(tam, (*pa)->tamInfo));
                return DATO_ENCONTRADO;
            }
        }
    }
    return DATO_NO_ENCONTRADO;
}

void vaciarArbol(tArbol *pa)
{
    if(*pa == NULL)
    {
        return;
    }
    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);
    free((*pa)->info);
    free(*pa);
    *pa = NULL;
}
