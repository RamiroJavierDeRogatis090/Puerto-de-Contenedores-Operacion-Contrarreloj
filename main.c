#include "estructuras.h"
#include "simulacion.h"
int main()
{
    tConfig config;
    tEscenario escenario;
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

    if(simulacionPrincipal(&escenario, &config))
        puts("SE EJECUTO LA SIMULACION.");

    puts("FIN DE LA SIMULACION");

    return 0;
}
