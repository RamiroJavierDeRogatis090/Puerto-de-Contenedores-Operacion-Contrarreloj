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

//int simulacionPrincipal(tEscenario *pEsc, const tConfig *pConfig)
//{
//    unsigned tiempo = 0;
//    tPuntos puntaje = {0,0,0,0,0};
//    tSimulacion sim;
//    tCola historialOp;
//    int bandFin = 0;
//
//    sim.escenario = pEsc;
//
//    crearCola(&sim.colaBuques);
//    crearCola(&sim.colaCamiones);
//    CrearLista(&sim.zonas);
//    if(!crearZonas(&sim.zonas, sim.escenario->cantZonas, sim.escenario->capacidadPila))
//        return MEMORIA_LLENA;
//
//    sim.muelle = crearMuelles(sim.escenario->cantMuelles);
//
//    if(sim.muelle == NULL)
//    {
//        vaciarZonas(&sim.zonas);
//        return MEMORIA_LLENA;
//    }
//
//    crearCola(&historialOp);
//
//    actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);
//
//    asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);
//
//    while(tiempo <= pEsc->duracionJornada && !bandFin)
//    {
//        if(ListaVacia(&sim.escenario->arribos) && !verEstadoMuelles(sim.muelle, sim.escenario->cantMuelles) && colaVacia(&sim.colaBuques) && colaVacia(&sim.colaCamiones))
//            bandFin = 1;
//
//        if(!bandFin)
//        {
//            operaciones(&sim, pConfig, &puntaje, &tiempo, &historialOp);
//
//            actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);
//
//            asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);
//        }
//    }
//
//    printf("\nFIN DE SIMULACION\n");
//
//    contarPenalizaciones(&puntaje, &sim.colaCamiones);
//
//    printf("\n---PUNTAJE---\n");
//
//    printf("Tiempo utilizado: %d / %d.\n", tiempo, pEsc->duracionJornada);
//
//    printf("Puntos: %d\nBuques descargados: %u\nContenedores entregados: %u\nReubicaciones: %u\nCamiones penalizados: %u\n",
//           puntaje.puntos, puntaje.buquesDesc, puntaje.contEntregados, puntaje.cantReorg, puntaje.camionesPen);
//
//    system("pause");
//
//    system("cls");
//
//    mostrarHistorialOperaciones(&historialOp);
//
//    system("pause");
//
//    vaciarListaArribos(&sim.escenario->arribos);
//    vaciarMuelles(sim.muelle, sim.escenario->cantMuelles);
//    vaciarColaBuques(&sim.colaBuques);
//    vaciarCola(&sim.colaCamiones);
//    vaciarZonas(&sim.zonas);
//
//    return EXITO;
//}

//int simulacionPrincipal(tEscenario *pEsc, const tConfig *pConfig, tPuntos *puntajeFinal)
//{
//    unsigned tiempo = 0;
//    tPuntos puntaje = {0,0,0,0,0};
//    tSimulacion sim;
//    tCola historialOp;
//    int bandFin = 0;
//
//    sim.escenario = pEsc;
//
//    crearCola(&sim.colaBuques);
//    crearCola(&sim.colaCamiones);
//    CrearLista(&sim.zonas);
//    if(!crearZonas(&sim.zonas, sim.escenario->cantZonas, sim.escenario->capacidadPila))
//        return MEMORIA_LLENA;
//
//    sim.muelle = crearMuelles(sim.escenario->cantMuelles);
//
//    if(sim.muelle == NULL)
//    {
//        vaciarZonas(&sim.zonas);
//        return MEMORIA_LLENA;
//    }
//
//    crearCola(&historialOp);
//
//    actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);
//
//    asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);
//
//    while(tiempo <= pEsc->duracionJornada && !bandFin)
//    {
//        if(ListaVacia(&sim.escenario->arribos) && !verEstadoMuelles(sim.muelle, sim.escenario->cantMuelles) && colaVacia(&sim.colaBuques) && colaVacia(&sim.colaCamiones))
//            bandFin = 1;
//
//        if(!bandFin)
//        {
//            operaciones(&sim, pConfig, &puntaje, &tiempo, &historialOp);
//
//            actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);
//
//            asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);
//        }
//    }
//
//    printf("\nFIN DE SIMULACION\n");
//
//    contarPenalizaciones(&puntaje, &sim.colaCamiones);
//
//    *puntajeFinal = puntaje;
//
//    printf("\n---PUNTAJE---\n");
//
//    printf("Tiempo utilizado: %d / %d.\n", tiempo, pEsc->duracionJornada);
//
//    printf("Puntos: %d\nBuques descargados: %u\nContenedores entregados: %u\nReubicaciones: %u\nCamiones penalizados: %u\n",
//           puntaje.puntos, puntaje.buquesDesc, puntaje.contEntregados, puntaje.cantReorg, puntaje.camionesPen);
//
//    system("pause");
//
//    system("cls");
//
//    mostrarHistorialOperaciones(&historialOp);
//
//    system("pause");
//
//    vaciarListaArribos(&sim.escenario->arribos);
//    vaciarMuelles(sim.muelle, sim.escenario->cantMuelles);
//    vaciarColaBuques(&sim.colaBuques);
//    vaciarCola(&sim.colaCamiones);
//    vaciarZonas(&sim.zonas);
//
//    return EXITO;
//}

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

    while(tiempo <= pEsc->duracionJornada && !bandFin)
    {
        if(ListaVacia(&sim.escenario->arribos) && !verEstadoMuelles(sim.muelle, sim.escenario->cantMuelles) && colaVacia(&sim.colaBuques) && colaVacia(&sim.colaCamiones))
            bandFin = 1;

        if(!bandFin)
        {
            operaciones(&sim, pConfig, &puntaje, &tiempo, &historialOp);

            actualizarArribos(&sim.escenario->arribos, &sim.colaBuques, &sim.colaCamiones, tiempo);

            asignarBuqueAMuelle(sim.muelle, &sim.colaBuques, pEsc->cantMuelles);
        }
    }

    printf("\nFIN DE SIMULACION\n");

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
            return BUQUE_ATRACADO; //devuelve 1, para que se sepa que hay algun buque
    }
    return MUELLES_VACIOS; //no hay buques en los muelles
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

