#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"
#include "estructuras.h"
#include "simulacion.h"
#include "operador.h"
#include "indice.h"
#include "jornada.h"
#include "ranking.h"

int main()
{
    tArbol indiceOperadores;
    tOperador operadorActual;
    char nombre[MAX_TAM_NOMBRE];
    tConfig config;
    tEscenario escenario;
    tPuntos resultadoJornada;
    int retActualizacion;
    unsigned tiempoUtilizado;
    int retJornada;
    tIndice indiceOperador;
    const char menu_principal[][MAX_TEXTO_MENU] = {
                                                   "1234",
                                                   "Iniciar Jornada",
                                                   "Ver Ranking",
                                                   "Consultar historial de jornadas",
                                                   "Salir"
                                                  };
    const char *titulo = "=== OPERACION CONTRARRELOJ ===";
    char seleccion;
    if(iniciarGestionOperadores(&indiceOperadores, "operadores.dat", "indice.dat") != TODO_OK)
    {
        return EXIT_FAILURE;
    }
    printf("Ingrese su nombre: ");
    scanf(" %49[^\n]", nombre);
    if(obtenerOperadorActual(&indiceOperadores, nombre, &operadorActual, "operadores.dat", "indice.dat") != TODO_OK)
    {
        return EXIT_FAILURE;
    }
    printf("Bienvenido: %s\n", operadorActual.nombre);
    printf("Puntaje acumulado: %d\n", operadorActual.puntajeAcumulado);
    system("PAUSE");
    do
    {
        seleccion = menu(menu_principal, titulo);
        switch(seleccion)
        {
        case '1':
            system("CLS");
            printf("\n--- JORNADA ---\n");

            if(configLeer("config.txt", &config))
                puts("SE LEYO EL ARCH DE CONFIGURACION.");
            else
                puts("NO SE PUDO LEER EL ARCHIVO DE CONFIGURACION.");

            if(escenario_generar(config, "puerto.txt"))
                puts("SE LEYO EL ARCH DE PUERTO.");
            else
                puts("NO SE PUDO LEER EL ARCHIVO DE CONFIGURACION.");

            if(escenario_cargar("puerto.txt", &escenario, &config))
                puts("SE GENERO EL ARCHIVO DEL PUERTO.");
            else
                puts("NO SE PUDO CARGAR EL ARCHIVO DE PUERTO.");

            if(simulacionPrincipal(&escenario, &config, &resultadoJornada, &tiempoUtilizado))
            {
                puts("SE EJECUTO LA SIMULACION.");
                printf("\nPuntaje obtenido: %d\n", resultadoJornada.puntos);
                retJornada = guardarJornada(&indiceOperadores, operadorActual.nombre, &resultadoJornada, tiempoUtilizado, "jornada.dat");
                if(retJornada == JORNADA_GUARDADA)
                {
                    puts("JORNADA GUARDADA CORRECTAMENTE.");
                    retActualizacion = actualizarPuntajeOperador(&indiceOperadores, &operadorActual, resultadoJornada.puntos, "operadores.dat");
                    if(retActualizacion == OPERADOR_ACTUALIZADO)
                    {
                        printf("\nPuntaje acumulado: %d\n", operadorActual.puntajeAcumulado);
                    }
                    else
                    {
                        printf("\nERROR AL ACTUALIZAR EL PUNTAJE DEL OPERADOR\n");
                    }
                }
            }
            else
            {
                puts("NO SE PUDO EJECUTAR LA SIMULACION.");
            }

            puts("FIN DE LA SIMULACION");
            system("PAUSE");
            break;
        case '2':
            system("CLS");
            printf("\n-- RANKING ---\n");
            mostrarRanking("operadores.dat");
            system("PAUSE");
            break;
        case '3':
            system("CLS");
            printf("\n-- HISTORIAL DE JORNADAS ---\n");
            strcpy(indiceOperador.clave.nombre, operadorActual.nombre);
            if(buscarEnArbol(&indiceOperadores, &indiceOperador, sizeof(tIndice), compararClaveIdx) == DATO_ENCONTRADO)
            {
                retJornada = mostrarJornadasOperador("jornada.dat", indiceOperador.indiceRegistro);
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
            break;
        case '4':
            printf("\nSaliendo del programa\n");
            break;
        }
    }while(seleccion != '4');
    vaciarArbol(&indiceOperadores);
    return 0;
}
