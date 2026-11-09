#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"
#include "operador.h"
#include "indice.h"
#include "opcionesMenu.h"

int main()
{
    tArbol indiceOperadores;
    tOperador operadorActual;
    char nombre[MAX_TAM_NOMBRE];
    const char menu_principal[][MAX_TEXTO_MENU] = {
                                                   "1234",
                                                   "Iniciar Jornada",
                                                   "Ver Ranking",
                                                   "Consultar historial de jornadas",
                                                   "Salir"
                                                  };
    const char *titulo = "=== OPERACION CONTRARRELOJ ===";
    char seleccion;
    if(iniciarGestionOperadores(&indiceOperadores, ARCH_OPERADORES, ARCH_INDICE) != TODO_OK)
    {
        return EXIT_FAILURE;
    }
    solicitarNombreOperador(nombre);
    if(obtenerOperadorActual(&indiceOperadores, nombre, &operadorActual, ARCH_OPERADORES, ARCH_INDICE) != TODO_OK)
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
            ejecutarOpcionJornada(&indiceOperadores, &operadorActual);
            break;
        case '2':
            ejecutarOpcionRanking(ARCH_OPERADORES);
            break;
        case '3':
            ejecutarOpcionHistorial(&indiceOperadores, &operadorActual);
            break;
        case '4':
            printf("\nSaliendo del programa\n");
            break;
        }
    }while(seleccion != '4');
    vaciarArbol(&indiceOperadores);
    return 0;
}
