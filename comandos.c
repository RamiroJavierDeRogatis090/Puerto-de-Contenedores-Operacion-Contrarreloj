#include "comandos.h"
#include "estructuras.h"

int _comandoVer(const tSimulacion* simulacion,const tPuntos* puntos,unsigned cronometro)
{
    tNodo *zonaActual;
    tNodo *nodoAux;
    unsigned cantBuquesEsperando;
    unsigned cantCamionesEsperando;
    int i;
    tZona *zona;
    tCamion *camion;

    if(simulacion == NULL || puntos == NULL)
    {
        fprintf(stderr,"Error: datos invalidos para mostrar estado\n");
        return DAT_INV;
    }

    printf("\nESTADO DE LA SIMULACION\n");
    printf("Minuto actual: %u\n", cronometro);

    printf("\nMUELLE\n");

    if(simulacion->muelle == NULL)
    {
        printf("Sin muelle configurado\n");
    }
    else if(simulacion->muelle->buque == NULL)
    {
        printf("%s -> LIBRE\n",simulacion->muelle->idMuelle);
    }
    else
    {
        printf("%s -> %s\n",simulacion->muelle->idMuelle,simulacion->muelle->buque->idBuque);
    }

    cantBuquesEsperando = 0;

    nodoAux = simulacion->colaBuques.pri;

    while(nodoAux != NULL)
    {
        cantBuquesEsperando++;
        nodoAux = nodoAux->sig;
    }

    printf("\nBUQUES ESPERANDO\n");
    printf("%u\n", cantBuquesEsperando);

    printf("\nZONAS DE ALMACENAMIENTO\n");

    if(simulacion->zonas == NULL)
    {
        printf("Sin zonas configuradas\n");
    }
    else
    {
        zonaActual = simulacion->zonas;

        while(zonaActual != NULL)
        {
            if(zonaActual->dato != NULL)
            {
                zona = (tZona*)zonaActual->dato;
                printf("%s -> %u/%u contenedores\n",zona->idZona,zona->cantAlmacenada,zona->capacidad);
            }

            zonaActual = zonaActual->sig;
        }
    }

    printf("\nVENTANA DE PLANIFICACION\n");

    cantCamionesEsperando = 0;

    nodoAux = simulacion->colaCamiones.pri;

    while(nodoAux != NULL)
    {
        cantCamionesEsperando++;
        nodoAux = nodoAux->sig;
    }

    if(cantCamionesEsperando == 0)
    {
        printf("Sin camiones en espera\n");
    }
    else
    {
        nodoAux = simulacion->colaCamiones.pri;

        for(i = 0; nodoAux != NULL && i < 3; i++)
        {
            if(nodoAux->dato != NULL)
            {
                camion = (tCamion*)nodoAux->dato;

                printf("%s -> %s\n",camion->idCamion,camion->idContenedor);
            }
            nodoAux = nodoAux->sig;
        }
    }

    printf("\nPUNTUACION PROVISORIA\n");
    printf("Puntos: %d\n", puntos->puntos);
    printf("Contenedores entregados: %u\n", puntos->contEntregados);
    printf("Buques descargados: %u\n", puntos->buquesDesc);
    printf("Reorganizaciones: %u\n", puntos->cantReorg);

    return DAT_MOS;
}


