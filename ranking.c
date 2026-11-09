#include "ranking.h"

int compararOperadoresRanking(const void *a, const void *b)
{
    const tOperador *op1 = (const tOperador *)a;
    const tOperador *op2 = (const tOperador *)b;
    int cmp = op2->puntajeAcumulado - op1->puntajeAcumulado;
    if(cmp == 0)
    {
        return strcmp(op1->nombre, op2->nombre);
    }
    return cmp;
}

void mostrarOperadorRanking(void *info, unsigned tam, unsigned n, void *params)
{
    tOperador *operador = (tOperador *)info;
    tRanking *ranking = (tRanking *)params;
    printf("%-5u %-49s %d\n", ranking->puesto, operador->nombre, operador->puntajeAcumulado);
    ranking->puesto++;
}

int mostrarRanking(const char *nombreArchivo)
{
    FILE *arch;
    tArbol arbolRanking;
    tOperador operador;
    tRanking ranking;
    crearArbol(&arbolRanking);
    if(abrirArchivo(&arch, nombreArchivo, "rb") != TODO_OK)
    {
        return ERROR_RANKING;
    }
    while(fread(&operador, sizeof(tOperador), 1, arch))
    {
        insertarEnArbol(&arbolRanking, &operador, sizeof(tOperador), compararOperadoresRanking);
    }
    fclose(arch);
    printf("\n%-5s %-49s %s\n", "Puesto", "Operador", "Puntaje");
    printf("-----------------------------------------------------------------\n");
    ranking.puesto = 1;
    recorrerInOrden(&arbolRanking, 0, &ranking, mostrarOperadorRanking);
    vaciarArbol(&arbolRanking);
    return TODO_OK;
}
