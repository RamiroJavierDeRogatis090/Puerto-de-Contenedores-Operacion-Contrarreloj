#include "estructuras.h"
#include "simulacion.h"

int actualizarArribos(tLista *arribos, tCola *colaB, tCola *colaK, unsigned tiempo)
{
    tArribo arriboActual;

    while(verPrimeroLista(arribos, &arriboActual, sizeof(tArribo)) == 1 && tiempo >= arriboActual.tiempoArribo)
    {
        sacarPrimeroLista(arribos, &arriboActual, sizeof(tArribo));

        if(arriboActual.buque == NULL)
        {
            acolar(colaK, &arriboActual.camion, sizeof(tCamion));
            free(arriboActual.camion);
        }
        else
        {
            acolar(colaB, &arriboActual.buque, sizeof(tBuque));
            free(arriboActual.buque);
        }
    }

    return  EXITO;
}

void vaciarListaArribos(tLista *arribos)
{
    tArribo local;
    while(sacarPrimeroLista(arribos, &local, sizeof(tArribo)))
    {
        if(local.buque != NULL)
        {
            vaciarCola(&local.buque->contenedores);
            free(local.buque);
        }
        if(local.camion != NULL)
        {
            free(local.camion);
        }
    }
}

int asignarBuqueAMuelle(tMuelle *muelles, tCola *colaB, int cantMuelles)
{
    tBuque buqueLocal;
    int i = 0;

    if(colaVacia(colaB))
        return COLA_VACIA;

    while(i < cantMuelles && !colaVacia(colaB))
    {
        if((muelles+i)->buque == NULL)
        {
            if(desacolar(colaB, &buqueLocal, sizeof(tBuque)))
            {
                (muelles+i)->buque = malloc(sizeof(tBuque));
                if((muelles+i)->buque == NULL)
                    return MEMORIA_LLENA;
                *(muelles+i)->buque = buqueLocal;
            }
        }
        i++;
    }
    return EXITO;
}

tMuelle* crearMuelles(unsigned cantMuelles)
{
    int i;
    tMuelle *muelles = malloc(sizeof(tMuelle)*cantMuelles);

    if(muelles == NULL)
        return NULL;

    for(i = 0; i < cantMuelles; i++)
    {
        sprintf((muelles+i)->idMuelle, "M%d", i + 1);
        (muelles+i)->buque = NULL;
    }
    return muelles;
}

int crearZonas(tLista *zonas, unsigned cantZonas, unsigned capPilas)
{
    int i;
    tZona zonaLocal;

    for(i=0; i < cantZonas; i++)
    {
        sprintf(zonaLocal.idZona, "Z%d", i+1);
        zonaLocal.capacidad = capPilas;
        zonaLocal.cantAlmacenada = 0;

        crearPila(&zonaLocal.contenedores);

        if(!InsertarAlFinalLista(zonas, &zonaLocal, sizeof(tZona)))
            return MEMORIA_LLENA;
    }
    return EXITO;
}

