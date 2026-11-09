#ifndef SIMULACION_H_INCLUDED
#define SIMULACION_H_INCLUDED

#include "escenario.h"
#include "configuracion.h"
#include "estructuras.h"

#define PUNTOS_PEN_CAMION 2
#define PUNTOS_CONT_ENTREGADO 10
#define PUNTOS_BUQUE_LIBRE 5

#define AVANZADO 1
#define NO_AVANZADO 0

#define BLOQUEO_OP 1
#define NO_BLOQUEO_OP 0

#define FIN_NORMAL 1
#define FIN_BLOQUEO 2

typedef struct
{
    int puntos;
    unsigned contEntregados;
    unsigned buquesDesc;
    unsigned cantReorg;
    unsigned camionesPen;
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
int simulacionPrincipal(tEscenario *pEsc, const tConfig *pConfig, tPuntos *puntajeFinal, unsigned *tiempoUtilizado);
void contarPenalizaciones(tPuntos *puntaje, tCola *colaCamiones);
int verEstadoZonas(tLista *zonas);
int avanceAutomatico(tSimulacion *sim, unsigned *tiempo);
int obtenerProximoCamion(tSimulacion *sim, tCamion *camion);
int verificarBloqueoOperativo(tSimulacion *sim);

#endif // SIMULACION_H_INCLUDED
