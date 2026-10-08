#include "interfaz.h"

char menu(const char matriz_menu[][MAX_TEXTO_MENU], const char *titulo)
{
    char opc;
    opc = opcion(matriz_menu, titulo, "Ingrese opcion");
    while(!strchr(matriz_menu[0], opc))
    {
        opc = opcion(matriz_menu, titulo, "Opcion erronea. Ingrese nuevamente");
    }
    return opc;
}

char opcion(const char matriz_menu[][MAX_TEXTO_MENU], const char *titulo, const char *mensaje)
{
    char opc;
    int i;
    system ("CLS");
    printf("\n\n %s \n", titulo);
    for(i = 1; i <= strlen(matriz_menu[0]); i++)
    {
        printf("\n %c - %s", matriz_menu[0][i - 1], matriz_menu[i]);
    }
    printf("\n\n%s: ", mensaje);
    fflush(stdin);
    scanf("%c", &opc);
    return toupper(opc);
}
