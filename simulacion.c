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


