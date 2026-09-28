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
    tCola contenedores;
    unsigned capacidad;
    unsigned cantAlmacenada;
}tBuque;

typedef struct
{
    char idCamion[TAM_CAMION];
    char idContenedor[TAM_CONTENEDOR];
}tCamion;

typedef struct
{
    char idMuelle[TAM_MUELLE];
    tBuque *buque;
}tMuelle;

typedef struct
{
    tBuque *buque;
    tCamion *camion;
    unsigned tiempoArribo;
}tArribo;


#endif // ESTRUCTURAS_H_INCLUDED
