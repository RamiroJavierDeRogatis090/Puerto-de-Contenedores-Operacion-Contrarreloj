#include "escenario.h"
#include "lista.h"
#include "configuracion.h"
#include "estructuras.h"



int escenario_generar(tConfig cfg, const char* arch)
{
    FILE* pf;

    unsigned cantBuques,cantContBuque,cantCam,totalCont,disponibles,indice,i,j;

    tRefContenedor*contenedores;

    if(arch == NULL || cfg.duracionJornada == 0 || cfg.maxBuques == 0 || cfg.maxContPorBuque == 0)
    {
        return ERR_ARCH;
    }

    contenedores = (tRefContenedor*) malloc((size_t)cfg.maxBuques * cfg.maxContPorBuque * sizeof(tRefContenedor));

    if(contenedores == NULL)
    {
        fprintf(stderr,"Error: memoria insuficiente\n");
        return MEM_INS;
    }

    pf = fopen(arch,"wt");

    if(pf == NULL)
    {
        fprintf(stderr,"Error: no se pudo crear '%s'\n", arch);
        free(contenedores);
        return ERR_ARCH;
    }

    fprintf(pf,"JORNADA:%u\n", cfg.duracionJornada);
    fprintf(pf,"MUELLES:%u\n", cfg.cantMuelles);
    fprintf(pf,"ZONAS:%u\n", cfg.cantZonas);
    fprintf(pf,"CAPACIDAD_PILA:%u\n\n", cfg.capacidadPila);

    cantBuques=(unsigned)(rand() % cfg.maxBuques) + 1;

    totalCont = 0;

    fprintf(pf,"[BUQUES]\n");

    for(i = 1; i <= cantBuques; i++)
    {

        cantContBuque=(unsigned)(rand() % cfg.maxContPorBuque) + 1;

        fprintf(pf,"B%03u;T=%u;C=",i,(unsigned)(rand() % cfg.duracionJornada));

        for(j = 1; j <= cantContBuque; j++)
        {

            (contenedores + totalCont)->nroBuque = i;
            (contenedores + totalCont)->nroCont = j;

            fprintf(pf,"C%u%02u",i,j);

            if(j < cantContBuque)
            {
                fprintf(pf,",");
            }

            totalCont++;
        }

        fprintf(pf,"\n");
    }

    fprintf(pf,"\n");

    cantCam = 0;

    if(totalCont > 0 && cfg.maxCamiones > 0)
    {
        cantCam = cfg.maxCamiones;

        if(cantCam > totalCont)
        {
            cantCam = totalCont;
        }

        cantCam = (unsigned)(rand() % (cantCam + 1));
    }

    disponibles = totalCont;

    fprintf(pf,"[CAMIONES]\n");

    for(i = 1; i <= cantCam; i++)
    {

        indice = (unsigned)(rand() % disponibles);

        fprintf(pf,"K%03u;T=%u;C=C%u%02u\n",i,(unsigned)(rand() % cfg.duracionJornada),(contenedores + indice)->nroBuque,(contenedores + indice)->nroCont);


        *(contenedores + indice) = *(contenedores + disponibles - 1);

        disponibles--;
    }

    fclose(pf);

    free(contenedores);

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
        else if(strncmp(linea,"JORNADA:",8) == 0)
        {
            sscanf(linea,"JORNADA:%u",&p->duracionJornada);
        }
        else if(strncmp(linea,"MUELLES:",8) == 0)
        {
            sscanf(linea,"MUELLES:%u",&p->cantMuelles);
        }
        else if(strncmp(linea,"ZONAS:", 6) == 0)
        {
            sscanf(linea,"ZONAS:%u",&p->cantZonas);
        }
        else if(strncmp(linea,"CAPACIDAD_PILA:", 15) == 0)
        {
            sscanf(linea,"CAPACIDAD_PILA:%u",&p->capacidadPila);
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
