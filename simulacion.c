#include "estructuras.h"
#include "simulacion.h"
#include "comando.h"


int actualizarArribos(tLista *arribos, tCola *colaB, tCola *colaK, unsigned tiempo)
{
    tArribo arriboActual;

    while(verPrimeroLista(arribos, &arriboActual, sizeof(tArribo)) == 1 && tiempo >= arriboActual.tiempoArribo)
    {
        sacarPrimeroLista(arribos, &arriboActual, sizeof(tArribo));

        if(arriboActual.buque == NULL)
        {
            acolar(colaK, arriboActual.camion, sizeof(tCamion));
            free(arriboActual.camion);
        }
        else
        {
            acolar(colaB, arriboActual.buque, sizeof(tBuque));
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
            vaciarPila(&local.buque->contenedores);
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
    unsigned i;
    tMuelle *muelles = malloc(sizeof(tMuelle)*cantMuelles);

    if(muelles == NULL)
        return NULL;

    for(i = 0; i < cantMuelles; i++)
    {
        sprintf((muelles+i)->idMuelle, "M%u", (i+1)%100);
        (muelles+i)->buque = NULL;
    }
    return muelles;
}

int crearZonas(tLista *zonas, unsigned cantZonas, unsigned capPilas)
{
    unsigned i;
    tZona zonaLocal;

    for(i=0; i < cantZonas; i++)
    {
        sprintf(zonaLocal.idZona, "Z%u", (i+1)%100 );
        zonaLocal.capacidad = capPilas;
        zonaLocal.cantAlmacenada = 0;

        crearPila(&zonaLocal.contenedores);

        if(!InsertarAlFinalLista(zonas, &zonaLocal, sizeof(tZona)))
            return MEMORIA_LLENA;
    }
    return EXITO;
}

int simulacionPrincipal(tEscenario *pEsc, const tConfig *pConfig, tPuntos *puntajeFinal, unsigned *tiempoUtilizado)
{
    unsigned tiempo = 0;
    tPuntos puntaje = {0,0,0,0,0};
    tSimulacion sim;
    tCola historialOp;
    int bandFin = 0;

    sim.escenario = pEsc;

    crearCola(&sim.colaBuques);
    crearCola(&sim.colaCamiones);
    CrearLista(&sim.zonas);
    if(!crearZonas(&sim.zonas, sim.escenario->cantZonas, sim.escenario->capacidadPila))
        return MEMORIA_LLENA;

    sim.muelle = crearMuelles(sim.escenario->cantMuelles);

    if(sim.muelle == NULL)
    {
        vaciarZonas(&sim.zonas);
        return MEMORIA_LLENA;
    }

    crearCola(&historialOp);

    actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);

    asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);

    if(avanceAutomatico(&sim, &tiempo))
    {
        actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);
        asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);
        printf("AVANCE AUTOMATICO");
        system("pause");
    }

    while(tiempo <= pEsc->duracionJornada && !bandFin)
    {
        if(ListaVacia(&sim.escenario->arribos) && !verEstadoMuelles(sim.muelle, sim.escenario->cantMuelles) &&
           colaVacia(&sim.colaBuques) && colaVacia(&sim.colaCamiones))
        {
            bandFin = 1;
        }
        else if(verificarBloqueoOperativo(&sim))
        {
            bandFin = 2;
        }

        if(!bandFin)
        {
            operaciones(&sim, pConfig, &puntaje, &tiempo, &historialOp);

            actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);

            asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);

            if(avanceAutomatico(&sim, &tiempo))
            {
                actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);
                asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);
                printf("\nAVANCE AUTOMATICO\n");
                system("pause");
            }
        }
    }

    if(bandFin == 2)
    {
        printf("\n---BLOQUEO OPERATIVO---\n---LAS ZONAS DE ALMACENAMIENTO ESTAN LLENAS Y NO HAY CAMIONES QUE PIDAN LOS CONTENEDORES---\n");
        actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, pEsc->duracionJornada);
    }

    printf("\nFIN DE JORNADA\n");

    system("pause");

    contarPenalizaciones(&puntaje, &sim.colaCamiones);

    *puntajeFinal = puntaje;

    *tiempoUtilizado = tiempo;

    printf("\n---PUNTAJE---\n");

    printf("Tiempo utilizado: %d / %d.\n", tiempo, pEsc->duracionJornada);

    printf("Puntos: %d\nBuques descargados: %u\nContenedores entregados: %u\nReubicaciones: %u\nCamiones penalizados: %u\n",
           puntaje.puntos, puntaje.buquesDesc, puntaje.contEntregados, puntaje.cantReorg, puntaje.camionesPen);

    system("pause");

    system("cls");

    mostrarHistorialOperaciones(&historialOp);

    system("pause");

    vaciarListaArribos(&sim.escenario->arribos);
    vaciarMuelles(sim.muelle, sim.escenario->cantMuelles);
    vaciarColaBuques(&sim.colaBuques);
    vaciarCola(&sim.colaCamiones);
    vaciarZonas(&sim.zonas);

    return EXITO;
}

int verEstadoMuelles(tMuelle *muelle, int cantMuelles)
{
    for(int i=0; i < cantMuelles ; i++)
    {
        if((muelle+i)->buque != NULL)
            return BUQUE_ATRACADO;
    }
    return MUELLES_VACIOS;
}

void vaciarMuelles(tMuelle *muelle, int cantMuelles)
{
    for(int i = 0; i < cantMuelles; i++)
    {
        if((muelle+i)->buque != NULL)
        {
            vaciarPila(&(muelle+i)->buque->contenedores);
            free((muelle+i)->buque);
        }
    }
    free(muelle);
}

void vaciarColaBuques(tCola *cBuques)
{
    tBuque local;

    while(desacolar(cBuques, &local, sizeof(tBuque)))
    {
        vaciarPila(&local.contenedores);
    }
}

void vaciarZonas(tLista *zonas)
{
    tZona local;
    while(sacarPrimeroLista(zonas, &local, sizeof(tZona)))
    {
        vaciarPila(&local.contenedores);
    }
}

void contarPenalizaciones(tPuntos *puntaje, tCola *colaCamiones)
{
    tCamion camion;

    while(desacolar(colaCamiones, &camion, sizeof(tCamion)))
        puntaje->camionesPen++;

    puntaje->puntos -= (puntaje->camionesPen * PUNTOS_PEN_CAMION);
}

int verEstadoZonas(tLista *zonas)
{
    tLista listaAux;
    tZona zonaLocal;
    int zonasOcupadas = 0;

    CrearLista(&listaAux);

    while(sacarPrimeroLista(zonas, &zonaLocal, sizeof(tZona)))
    {
        if(zonaLocal.cantAlmacenada > 0)
        {
            zonasOcupadas = 1;
        }

        InsertarAlFinalLista(&listaAux, &zonaLocal, sizeof(tZona));
    }

    while(sacarPrimeroLista(&listaAux   , &zonaLocal, sizeof(tZona)))
    {
        InsertarAlFinalLista(zonas, &zonaLocal, sizeof(tZona));
    }

    return zonasOcupadas;
}

int avanceAutomatico(tSimulacion *sim, unsigned *tiempo)
{
    tArribo arriboProx;
    if(!ListaVacia(&sim->escenario->arribos) && !verEstadoMuelles(sim->muelle, sim->escenario->cantMuelles) && !verEstadoZonas(&sim->zonas) && colaVacia(&sim->colaCamiones))
    {
        if(verPrimeroLista(&sim->escenario->arribos, &arriboProx, sizeof(tArribo)))
        {
            *tiempo = arriboProx.tiempoArribo;
            return AVANZADO;
        }
    }

    return NO_AVANZADO;
}

int obtenerProximoCamion(tSimulacion *sim, tCamion *camion)
{
    tLista listaAux;
    tArribo arriboLocal;
    int encontrado = 0;

    if(verPrimeroEnCola(&sim->colaCamiones, camion, sizeof(tCamion)))
    {
        return OK;
    }

    CrearLista(&listaAux);
    while(sacarPrimeroLista(&sim->escenario->arribos, &arriboLocal, sizeof(tArribo)))
    {
        if(!encontrado && arriboLocal.camion != NULL)
        {
            *camion = *(arriboLocal.camion);
            encontrado = 1;
        }
        InsertarAlFinalLista(&listaAux, &arriboLocal, sizeof(tArribo));
    }

    while(sacarPrimeroLista(&listaAux, &arriboLocal, sizeof(tArribo)))
    {
        InsertarAlFinalLista(&sim->escenario->arribos, &arriboLocal, sizeof(tArribo));
    }

    return encontrado;
}

int verificarBloqueoOperativo(tSimulacion *sim)
{
    tLista listaAux;
    tZona zonaLocal;
    tCamion camionLocal;
    char contTope[TAM_CONTENEDOR];
    int hayCamion = 0, zonasLlenas = 0, topeCoincide = 0;

    hayCamion = obtenerProximoCamion(sim, &camionLocal);

    CrearLista(&listaAux);

    while(sacarPrimeroLista(&sim->zonas, &zonaLocal, sizeof(tZona)))
    {
        if(zonaLocal.cantAlmacenada == zonaLocal.capacidad)
        {
            zonasLlenas++;
        }

        if(hayCamion && !topeCoincide &&
           verTope(&zonaLocal.contenedores, contTope, TAM_CONTENEDOR))
        {
            if(strcmp(contTope, camionLocal.idContenedor) == 0)
                topeCoincide = 1;
        }
        InsertarAlFinalLista(&listaAux, &zonaLocal, sizeof(tZona));
    }

    while(sacarPrimeroLista(&listaAux, &zonaLocal, sizeof(tZona)))
    {
        InsertarAlFinalLista(&sim->zonas, &zonaLocal, sizeof(tZona));
    }

    if(zonasLlenas == sim->escenario->cantZonas && !topeCoincide)
    {
        return BLOQUEO_OP;
    }
    return NO_BLOQUEO_OP;
}
