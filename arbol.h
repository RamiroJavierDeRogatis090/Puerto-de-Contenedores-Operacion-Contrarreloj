#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X,Y) ((X) <= (Y) ? (X) : (Y))

#define SIN_MEM -1
#define TODO_OK 1
#define DATO_NO_ENCONTRADO 0
#define DATO_ENCONTRADO 1
#define CLA_DUP 2

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *izq,
                 *der;
}tNodoArbol;

typedef tNodoArbol *tArbol;

void crearArbol(tArbol *pa);
int insertarEnArbol(tArbol *pa, const void *d, unsigned tam, int (*comparar)(const void *, const void *));
void recorrerInOrden(const tArbol *pa, unsigned n, void *params, void (*accion)(void *, unsigned, unsigned, void *));
int buscarEnArbol(const tArbol *pa, void *d, unsigned tam, int (*comparar)(const void *, const void *));
void vaciarArbol(tArbol *pa);

#endif // ARBOL_H_INCLUDED
