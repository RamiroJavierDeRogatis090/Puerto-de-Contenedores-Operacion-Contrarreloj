#include <stdio.h>
#include "comandos.h"
#include "pila.h"

#define SIEMPRE 1

int main(void)
{
    tComando cmd;

    unsigned cronometro = 0;
    //printf("\n[MAIN] Cronometro antes del comando: %d\n", cronometro);

    while(SIEMPRE)
    {
        comandoSolicitar(&cmd);

        printf("\n--- Comando recibido ---\n");
        printf("tipo : %s (%d)\n", comandoNombre(cmd.tipo), cmd.tipo);
        printf("arg_1: '%s'\n", cmd.arg_1);
        printf("arg_2: '%s'\n\n", cmd.arg_2);

        unsigned rdoEjecucion = comandoEjecutar(&cmd, &cronometro);
        if(rdoEjecucion == FIN)
        {
            puts("\nFinalizando ejecucion!");
            return FIN;
        }
        else if(rdoEjecucion)
        {
            puts("\nComando invalido!");
            return rdoEjecucion;
        }

        //printf("\n[MAIN] Cronometro luego del comando: %d\n", cronometro);
    }

    return OK;
}
