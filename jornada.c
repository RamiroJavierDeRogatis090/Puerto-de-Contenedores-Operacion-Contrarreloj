#include "jornada.h"

int guardarJornada(const tArbol *pa, const char *nombreOperador, const tPuntos *resultado, unsigned tiempoUtilizado, const char *nombreArchivo)
{
    FILE *arch;
    tIndice indice;
    tJornada jornada;
    strcpy(indice.clave.nombre, nombreOperador);
    if(buscarEnArbol(pa, &indice, sizeof(tIndice), compararClaveIdx) != DATO_ENCONTRADO)
    {
        return ERROR_OPERADOR_JORNADA;
    }
    jornada.indiceOperador = indice.indiceRegistro;
    jornada.resultado = *resultado;
    jornada.tiempoUtilizado = tiempoUtilizado;
    if(abrirArchivo(&arch, nombreArchivo, "ab") != TODO_OK)
    {
        return ERROR_ARCHIVO_JORNADAS;
    }
    fwrite(&jornada, sizeof(tJornada), 1, arch);
    fclose(arch);
    return JORNADA_GUARDADA;
}

int mostrarJornadasOperador(const char *nombreArchivo, unsigned indiceOperador)
{
    FILE *arch;
    tJornada jornada;
    unsigned numeroJornada = 1;
    unsigned jornadasEncontradas = 0;
    if(abrirArchivo(&arch, nombreArchivo, "rb") != TODO_OK)
    {
        return ERROR_LECTURA_JORNADAS;
    }
    printf("\n%-10s %-10s %-12s %-10s %-12s %-12s %-10s\n", "Jornada", "Puntaje", "Entregados", "Buques", "Reubicaciones", "Penalizados", "Tiempo");
    printf("---------------------------------------------------------------------------------------\n");
    while(fread(&jornada, sizeof(tJornada), 1, arch))
    {
        if(jornada.indiceOperador == indiceOperador)
        {
            printf("%-10u %-10d %-12u %-10u %-12u %-12u %-10u\n", numeroJornada, jornada.resultado.puntos, jornada.resultado.contEntregados,
                                                                  jornada.resultado.buquesDesc, jornada.resultado.cantReorg, jornada.resultado.camionesPen,
                                                                  jornada.tiempoUtilizado);
            jornadasEncontradas++;
            numeroJornada++;
        }
    }
    fclose(arch);
    if(jornadasEncontradas == 0)
    {
        return SIN_JORNADAS;
    }
    return TODO_OK;
}
