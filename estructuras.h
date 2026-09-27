#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#include "pila.h"

#define TAM_ZONA 4
#define TAM_BUQUE 5
#define TAM_CAMION 5
#define TAM_MUELLE 5
#define TAM_CONTENEDOR 5

typedef struct
{
    char idZona[TAM_ZONA];
    tPila contenedores;
    unsigned capacidad;
    unsigned cantAlmacenada;
}tZona;

typedef struct
{
    char idBuque[TAM_BUQUE];
    tPila contenedores;
    unsigned capacidad;
    unsigned cantAlmacenada;
    unsigned tiempoArribo;
}tBuque;

typedef struct
{
    char idCamion[TAM_CAMION];
    char idContenedor[TAM_CONTENEDOR];
    unsigned tiempoArribo;
}tCamion;

typedef struct
{
    char idMuelle[TAM_MUELLE];
    tBuque *buque;
}tMuelle;

#endif // ESTRUCTURAS_H_INCLUDED
