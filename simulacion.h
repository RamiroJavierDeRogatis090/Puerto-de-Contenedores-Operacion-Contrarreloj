#ifndef SIMULACION_H_INCLUDED
#define SIMULACION_H_INCLUDED

#include "estructuras.h"
#include "configuracion.h"
#include "escenario.h"

typedef struct
{
    int puntos;
    unsigned contEntregados;
    unsigned buquesDesc;
    unsigned cantReorg;
}tPuntos;

typedef struct
{
    tEscenario *escenario;
    tCola colaBuques, colaCamiones;
    tLista zonas;
    tMuelle *muelle;
}tSimulacion;

void vaciarListaArribos(tLista *arribos);
int actualizarArribos(tLista *arribos, tCola *colaB, tCola *colaK, unsigned tiempo);
int asignarBuqueAMuelle(tMuelle *muelles, tCola *colaB, int cantMuelles);
tMuelle* crearMuelles(unsigned cantMuelles);
int crearZonas(tLista *zonas, unsigned cantZonas, unsigned capPilas);
int verEstadoMuelles(tMuelle *muelle, int cantMuelles);
void vaciarMuelles(tMuelle *muelle, int cantMuelles);
void vaciarColaBuques(tCola *cBuques);
void vaciarZonas(tLista *zonas);
int simulacionPrincipal(tEscenario *pEsc, const tConfig *pConfig);
void operaciones(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo);


#endif // SIMULACION_H_INCLUDED
