#include "configuracion.h"


int configLeer(const char* arch,tConfig* salida)
{
    FILE* pf;
    char linea[TAM_LINEA];
    char clave[TAM_CLAVE];
    unsigned valor;

    pf=fopen(arch,"rt");

    if(!pf)
    {
        fprintf(stderr,"Error: no se pudo abrir '%s'\n",arch);
        return ERR_ARCH;
    }

    while(fgets(linea,sizeof(linea),pf))
    {
        if(sscanf(linea,"%99[^:]:%u",clave,&valor) == 2)
        {
            if(strcmp(clave,"duracion_jornada_minutos") == 0)
                salida->duracionJornada=valor;

            else if(strcmp(clave,"cantidad_muelles") == 0)
                salida->cantMuelles = valor;

            else if(strcmp(clave,"cantidad_zonas_almacenamiento") == 0)
                salida->cantZonas=valor;

            else if(strcmp(clave,"capacidad_pila") == 0)
                salida->capacidadPila=valor;

            else if(strcmp(clave,"maximo_buques") == 0)
                salida->maxBuques=valor;

            else if(strcmp(clave,"maximo_contenedores_por_buque") == 0)
                salida->maxContPorBuque=valor;

            else if(strcmp(clave,"maximo_camiones") == 0)
                salida->maxCamiones=valor;

            else if(strcmp(clave,"tiempo_descarga_contenedor") == 0)
                salida->tiempDesCont=valor;

            else if(strcmp(clave,"tiempo_reubicacion_contenedor") == 0)
                salida->tiempReuCont=valor;

            else if(strcmp(clave,"tiempo_carga_camion") == 0)
                salida->tiempCarCami=valor;

            else
            {
                fprintf(stderr,"Advertencia: clave desconocida '%s'\n",clave);
            }
        }
        else
        {
            fprintf(stderr,"Advertencia: linea invalida -> %s", linea);
        }
    }

    fclose(pf);

    return LECT_OK;
}
