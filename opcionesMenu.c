#include "opcionesMenu.h"

int ejecutarOpcionJornada(tArbol *indiceOperadores, tOperador *operadorActual)
{
    tConfig config;
    tEscenario escenario;
    tPuntos resultadoJornada;
    unsigned tiempoUtilizado;
    int retJornada;
    int retActualizacion;
    system("CLS");
    printf("\n--- JORNADA ---\n");

    if(!configLeer(ARCH_CONFIGURACION, &config))
    {
        puts("NO SE PUDO LEER EL ARCHIVO DE CONFIGURACION.");
        system("PAUSE");
        return ERROR;
    }

    if(!escenario_generar(config, ARCH_PUERTO))
    {
        puts("NO SE PUDO LEER EL ARCHIVO DE CONFIGURACION.");
        system("PAUSE");
        return ERROR;
    }

    if(!escenario_cargar(ARCH_PUERTO, &escenario, &config))
    {
        puts("NO SE PUDO CARGAR EL ARCHIVO DE PUERTO.");
        system("PAUSE");
        return ERROR;
    }

    if(simulacionPrincipal(&escenario, &config, &resultadoJornada, &tiempoUtilizado))
    {
        puts("SE EJECUTO LA SIMULACION.");
        printf("\nPuntaje obtenido: %d\n", resultadoJornada.puntos);
        retJornada = guardarJornada(indiceOperadores, operadorActual->nombre, &resultadoJornada, tiempoUtilizado, ARCH_JORNADAS);
        if(retJornada == JORNADA_GUARDADA)
        {
            puts("JORNADA GUARDADA CORRECTAMENTE.");
            retActualizacion = actualizarPuntajeOperador(indiceOperadores, operadorActual, resultadoJornada.puntos, ARCH_OPERADORES);
            if(retActualizacion == OPERADOR_ACTUALIZADO)
            {
                printf("\nPuntaje acumulado: %d\n", operadorActual->puntajeAcumulado);
            }
            else
            {
                puts("\nERROR AL ACTUALIZAR EL PUNTAJE DEL OPERADOR\n");
            }
        }
        else
        {
            puts("ERROR AL GUARDAR LA JORNADA.");
        }
    }
    else
    {
        puts("NO SE PUDO EJECUTAR LA SIMULACION.");
    }

    puts("FIN DE LA SIMULACION");
    system("PAUSE");
    return TODO_OK;
}

int ejecutarOpcionRanking(const char *nombreArchivo)
{
    system("CLS");
    printf("\n-- RANKING ---\n");
    mostrarRanking(nombreArchivo);
    system("PAUSE");
    return TODO_OK;
}

int ejecutarOpcionHistorial(tArbol *indiceOperadores, const tOperador *operadorActual)
{
    tIndice indiceOperador;
    int retJornada;
    system("CLS");
    printf("\n-- HISTORIAL DE JORNADAS ---\n");
    strcpy(indiceOperador.clave.nombre, operadorActual->nombre);
    if(buscarEnArbol(indiceOperadores, &indiceOperador, sizeof(tIndice), compararClaveIdx) == DATO_ENCONTRADO)
    {
        retJornada = mostrarJornadasOperador(ARCH_JORNADAS, indiceOperador.indiceRegistro);
        if(retJornada == SIN_JORNADAS)
        {
            puts("EL OPERADOR NO TIENE JORNADAS REGISTRADAS.");
        }
        else
        {
            if(retJornada == ERROR_LECTURA_JORNADAS)
            {
                puts("ERROR AL LEER EL ARCHIVO DE JORNADAS.");
            }
        }
    }
    else
    {
        puts("NO SE PUDO LOCALIZAR AL OPERADOR EN EL INDICE.");
    }
    system("PAUSE");
    return TODO_OK;
}
