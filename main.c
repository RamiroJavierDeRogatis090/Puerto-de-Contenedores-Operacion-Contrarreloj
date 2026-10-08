#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"

int main()
{
    const char menu_principal[][MAX_TEXTO_MENU] = {
                                                   "123",
                                                   "Iniciar Jornada",
                                                   "Ver Ranking",
                                                   "Salir"
                                                  };
    const char *titulo = "=== OPERACION CONTRARRELOJ ===";
    char seleccion;
    do
    {
        seleccion = menu(menu_principal, titulo);
        switch(seleccion)
        {
        case '1':
            system("CLS");
            printf("\n--- JORNADA ---\n");
            system("PAUSE");
            break;
        case '2':
            system("CLS");
            printf("\n-- RANKING ---\n");
            system("PAUSE");
            break;
        case '3':
            printf("\nSaliendo del programa\n");
            break;
        }
    }
    while(seleccion != '3');
    return 0;
}
