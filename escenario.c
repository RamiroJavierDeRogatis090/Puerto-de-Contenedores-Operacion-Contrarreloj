
#include "escenario.h"
#include "lista.h"
#include "configuracion.h"
#include "estructuras.h"



int escenario_generar(tConfig cfg, const char* arch)
{
    FILE* pf;
    int i, j;
    unsigned totalCont,cantCam,nroBuque,nroCont;
    pf=fopen(arch,"wt");
    if(!pf)
    {
        fprintf(stderr,"Error: no se pudo crear '%s'\n",arch);
        return ERR_ARCH;
    }

    fprintf(pf,"JORNADA:%u\n",cfg.duracionJornada);
    fprintf(pf,"MUELLES:%u\n",cfg.cantMuelles);
    fprintf(pf,"ZONAS:%u\n",cfg.cantZonas);
    fprintf(pf,"CAPACIDAD_PILA:%u\n\n",cfg.capacidadPila);

    /* BUQUES */
    fprintf(pf, "[BUQUES]\n");

    for(i=1; i<=cfg.maxBuques; i++)
    {
        fprintf(pf,"B%03d;T=%u;C=",i,(i - 1)*3);
        for(j=1; j<=cfg.maxContPorBuque; j++)
        {
            fprintf(pf,"C%d%02d",i,j);
            if(j<cfg.maxContPorBuque)
                fprintf(pf,",");
        }
        fprintf(pf, "\n");
    }

    fprintf(pf, "\n");

    /* CAMIONES */

    fprintf(pf,"[CAMIONES]\n");
    totalCont=cfg.maxBuques*cfg.maxContPorBuque;
    cantCam=cfg.maxCamiones;

    if(cantCam>totalCont)
        cantCam=totalCont;

    for(i=1; i<=cantCam; i++)
    {
        nroBuque=((i-1)/cfg.maxContPorBuque)+1;
        nroCont=((i-1)%cfg.maxContPorBuque)+1;
        fprintf(pf,"K%03d;T=%u;C=C%d%02d\n",i,i*2,nroBuque,nroCont);
    }

    fclose(pf);
    return ESC_GEN;
}

int escenario_cargar(const char* arch, tEscenario* p)
{
    FILE*pf;
    char linea[TAM_LINEA], listaCont[TAM_LIS_CONT];
    char*salto;
    int seccion = 0;
    tBuque*buque;
    tCamion*camion;
    tArribo arribo;
    char*clave;

    if(arch == NULL || p == NULL)
        return ERR_ARCH;

    pf = fopen(arch,"rt");

    if(!pf)
    {
        fprintf(stderr,"Error al abrir '%s'\n", arch);
        return ERR_ARCH;
    }

    CrearLista(&p->arribos);

    while(fgets(linea,sizeof(linea), pf))
    {
        // Eliminar salto de linea //
        salto = strchr(linea, '\n');

        if(salto)
            *salto = '\0';

        if(*linea == '\0')
        {
            // Ignora línea vacia //
        }
        else if(strcmp(linea,"[BUQUES]") == 0)
        {
            seccion = 1;
        }
        else if(strcmp(linea,"[CAMIONES]") == 0)
        {
            seccion = 2;
        }
        else if(strncmp(linea,"JORNADA:",8) == 0 || strncmp(linea,"MUELLES:",8) == 0 || strncmp(linea,"ZONAS:", 6) == 0 || strncmp(linea,"CAPACIDAD_PILA:",15) == 0)
        {
            // ignora encabezado //
        }
        else if(seccion == 1)
        {
            buque = malloc(sizeof(tBuque));

            if(buque == NULL)
            {
                fprintf(stderr,"Memoria insuficiente para buque\n");
                fclose(pf);
                return ERR_ALM_BUQ;
            }

            crearCola(&buque->contenedores);
            buque->cantAlmacenada = 0;
            buque->capacidad = 0;

            if(sscanf(linea, "%[^;];T=%u;C=%s",buque->idBuque, &arribo.tiempoArribo, listaCont) == 3)
            {
                clave = strtok(listaCont, ",");

                while(clave != NULL)
                {
                    if(acolar(&buque->contenedores, clave, strlen(clave) + 1) == ACOLADO)
                    {
                        buque->cantAlmacenada++;
                    }
                    else
                    {
                        fprintf(stderr,"Error almacenando contenedor '%s'\n", clave);
                        vaciarCola(&buque->contenedores);
                        free(buque);
                        fclose(pf);
                        return ERR_ALM_CONT;
                    }

                    clave = strtok(NULL,",");
                }

                arribo.buque = buque;
                arribo.camion = NULL;

                if(InsertarEnOrdenLista(&p->arribos,&arribo,sizeof(tArribo),cmpArribo)!= LISTADO)
                {
                    fprintf(stderr, "Error insertando arribo de buque\n");
                    vaciarCola(&buque->contenedores);
                    free(buque);
                }
            }
            else
            {
                fprintf(stderr,"Formato inválido de buque: %s\n", linea);
                free(buque);
            }
        }
        else if(seccion == 2)
        {
            camion = malloc(sizeof(tCamion));

            if(camion == NULL)
            {
                fprintf(stderr,"Memoria insuficiente para camion\n");
                fclose(pf);
                return ERR_ALM_CAM;
            }

            if(sscanf(linea,"%[^;];T=%u;C=%s",camion->idCamion,&arribo.tiempoArribo,camion->idContenedor) == 3)
            {
                arribo.buque = NULL;
                arribo.camion = camion;

                if(InsertarEnOrdenLista(&p->arribos,&arribo,sizeof(tArribo),cmpArribo)!= LISTADO)
                {
                    fprintf(stderr,"Error insertando arribo de camion\n");
                    free(camion);
                }
            }
            else
            {
                fprintf(stderr,"Formato inválido de camion: %s\n", linea);
                free(camion);
            }
        }
    }

    fclose(pf);
    return ESC_CAR;
}





int cmpArribo(const void* d1, const void* d2)
{
    const tArribo* arribo1;
    const tArribo* arribo2;

    arribo1=(const tArribo*)d1;
    arribo2=(const tArribo*)d2;

    if(arribo1->tiempoArribo < arribo2->tiempoArribo)
    {
        return ARRIBO_MENOR;
    }

    if(arribo1->tiempoArribo > arribo2->tiempoArribo)
    {
        return ARRIBO_MAYOR;
    }

    return ARRIBO_IGUAL;
}
