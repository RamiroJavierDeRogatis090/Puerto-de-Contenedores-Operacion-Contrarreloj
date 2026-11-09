#include "escenario.h"
#include "simulacion.h"


int escenario_generar(tConfig cfg, const char* arch)
{
    FILE* pf;

    unsigned cantBuques, cantContBuque, cantCam, totalCont, disponibles, indice, i, j, tiempoMaxCamion, tiempoMaxBuque;

    tRefContenedor*contenedores;

    srand((unsigned)time(NULL));

    if(arch == NULL || cfg.duracionJornada == 0 || cfg.maxBuques == 0 || cfg.maxContPorBuque == 0 || cfg.cantMuelles == 0 || cfg.cantZonas == 0 || cfg.capacidadPila == 0)
    {
        return ERR_ARCH;
    }

    contenedores = (tRefContenedor*) malloc((size_t)cfg.maxBuques * cfg.maxContPorBuque * sizeof(tRefContenedor));

    if(contenedores == NULL)
    {
        fprintf(stderr,"Error: memoria insuficiente\n");
        return MEM_INS;
    }

    if(abrirArchivo(&pf, arch, "wt") != TODO_OK)
    {
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
        tiempoMaxBuque = (cfg.duracionJornada * 60) / 100;
        fprintf(pf,"B%03u;T=%u;C=",i,(unsigned)(rand() % tiempoMaxBuque));

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

        cantCam = (unsigned)(rand() % (cantCam))+ 1;
    }

    disponibles = totalCont;

    fprintf(pf,"[CAMIONES]\n");

    for(i = 1; i <= cantCam; i++)
    {

        indice = (unsigned)(rand() % disponibles);
        tiempoMaxCamion = (cfg.duracionJornada * 80) / 100;

        fprintf(pf,"K%03u;T=%u;C=C%u%02u\n",i,(unsigned)(rand() % tiempoMaxCamion),(contenedores + indice)->nroBuque,(contenedores + indice)->nroCont);


        *(contenedores + indice) = *(contenedores + disponibles - 1);

        disponibles--;
    }

    fclose(pf);

    free(contenedores);

    return ESC_GEN;
}


int escenario_cargar(const char* arch, tEscenario* p, tConfig *conf)
{
    FILE*pf;
    char linea[TAM_LINEA];
    char*salto;
    int seccion = 0;
    tBuque*buque;
    tCamion*camion;
    tArribo arribo;

    if(arch == NULL || p == NULL)
        return ERR_ARCH;

    if(abrirArchivo(&pf, arch, "rt") != TODO_OK)
    {
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
                vaciarListaArribos(&p->arribos);
                return ERR_ALM_BUQ;
            }

            buque->capacidad = conf->maxContPorBuque;

            guardarBuque(linea, buque, &arribo);

             if(InsertarEnOrdenLista(&p->arribos,&arribo,sizeof(tArribo),cmpArribo)!= LISTADO)
            {
                fprintf(stderr, "Error insertando arribo de buque\n");
                vaciarPila(&buque->contenedores);
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
                vaciarListaArribos(&p->arribos);
                return ERR_ALM_CAM;
            }

            guardarCamion(linea, camion, &arribo);

            if(InsertarEnOrdenLista(&p->arribos,&arribo,sizeof(tArribo),cmpArribo)!= LISTADO)
            {
                fprintf(stderr,"Error insertando arribo de camion\n");
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

void guardarBuque(char *linea, tBuque *buque, tArribo *arribo)
{
    char *aux;

    crearPila(&buque->contenedores);
    buque->cantAlmacenada = 0;

    while((aux = strrchr(linea, ',')) != NULL)
    {
        *aux = '\0';
        apilar(&buque->contenedores, aux + 1, strlen(aux + 1) + 1);
        buque->cantAlmacenada++;
    }

    aux = strrchr(linea, '=');
    apilar(&buque->contenedores, aux + 1, strlen(aux + 1) + 1);
    buque->cantAlmacenada++;

    aux = strrchr(linea, ';');
    *aux = '\0';

    aux = strrchr(linea, '=');
    arribo->tiempoArribo = atoi(aux + 1);

    aux = strrchr(linea, ';');
    *aux = '\0';

    strcpy(buque->idBuque, linea);

    arribo->buque = buque;
    arribo->camion = NULL;
}

void guardarCamion(char *linea, tCamion *camion, tArribo *arribo)
{
    char *aux;

    aux = strrchr(linea, '=');
    strcpy(camion->idContenedor, aux+1);

    aux = strrchr(linea, ';');
    *aux = '\0';

    aux = strrchr(linea, '=');
    arribo->tiempoArribo = atoi(aux+1);

    aux = strrchr(linea, ';');
    *aux = '\0';

    strcpy(camion->idCamion, linea);

    arribo->camion = camion;
    arribo->buque = NULL;
}
