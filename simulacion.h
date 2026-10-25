#ifndef SIMULACION_H_INCLUDED
#define SIMULACION_H_INCLUDED

#include "estructuras.h"

void vaciarListaArribos(tLista *arribos);
int actualizarArribos(tLista *arribos, tCola *colaB, tCola *colaK, unsigned tiempo);
int asignarBuqueAMuelle(tMuelle *muelles, tCola *colaB, int cantMuelles);
tMuelle* crearMuelles(unsigned cantMuelles);
int crearZonas(tLista *zonas, unsigned cantZonas, unsigned capPilas);


#endif // SIMULACION_H_INCLUDED
