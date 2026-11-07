#include "comando.h"

void operaciones(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo)
{
    char op[TAM_OP], origen[TAM_ORIGEN], destino[TAM_DESTINO], comando[20];
    int operacionCompletada = 0, codigoOp;
    //tHistorial opActual;

    while(operacionCompletada == 0)
    {
        printf("\nOPERADOR>");

        gets(comando);

        sscanf(comando, "%s %s %s", op, origen, destino);

        printf("\nCOMANDO DEL OPERADOR: %s %s %s\n", op, origen, destino);

        operacionCompletada = 1;
        if(strcmpi(op, "DES") == 0)
        {
            codigoOp = CMD_DES;
        }
        else if(strcmpi(op, "ENT") == 0)
        {
            codigoOp = CMD_ENT;
        }
        else if(strcmpi(op, "REU") == 0)
        {
            codigoOp = CMD_REU;
        }
        else if(strcmpi(op, "ESP") == 0)
        {
            codigoOp = CMD_ESP;
        }
        else if(strcmpi(op, "VER") == 0)
        {
            codigoOp = CMD_VER;
        }
        else
            codigoOp = CMD_INVALIDO;

        switch(codigoOp)
        {
            case DES:
                operacionCompletada = 1;
                /*
                if(comandoDescarga())
                {
                    operacionCompletada = 1;
                    ///opActual; --> se guarda el historial. y se encola
                }*/
                puts("ERROR DE DESCARGA.");
                break;
            case ENT:
                if(comandoEntregar(sim, origen, destino) != OK)
                {
                    puts("ERROR DE DESCARGA");
                    return;
                }
                sim->escenario->duracionJornada += pConfig->tiempDesCont;
                /// opActual; --> se guarda el historial. y se encola
                break;
            case REU:
                operacionCompletada = 1;
                /*if(comandoReubicar())
                {
                    operacionCompletada = 1;
                    ///opActual; --> se guarda el historial. y se encola
                }*/
                puts("ERROR DE REUBICACION.");
                break;
            case ESP:
                (*tiempo)++;
                operacionCompletada = 1;
                break;
            case VER:
                operacionCompletada = 1;
                /*if(comandoVer())
                {
                    operacionCompletada = 1;
                }*/
                puts("ERROR DE VISTA.");
                break;
            default:
                puts("OPERACION INVALIDA.");
                break;
        }


        //system("pause");
    }
}

int comandoEntregar(tSimulacion *sim, const char *origen, const char *destino)
{


    return OK;
}

int _buscarMuelle(tMuelle *muelles, unsigned cantMuelles, const char *codMuelle)
{
    int i = 0, indice = NO_ENCONTRADO;
    while(i < cantMuelles && indice == NO_ENCONTRADO)
    {
        if(strcmpi(codMuelle, (const char *)muelles[i].idMuelle) == IGUALES)
            indice = i;
        i++;
    }
    return indice;
}

tZona * _buscarZona(tLista *zonas, const char *codZona)
{
    tZona bufferZona, *dirZona = NULL;
    tNodo *aux = *zonas;

    /// Lista: [z1] [z2] [z3] [z4]
    /// z1: [c1] [c3]
    /// z2: NULL
    /// z3: [c2] [c5]
    /// z4: [c4] [c6] [c7]

    while(!aux)
    {
        memcpy(&bufferZona, (const tZona *)(aux->dato), aux->tamDato);
        if(strcmpi((const char *)bufferZona.idZona, codZona) == IGUALES)
            dirZona = aux->dato;
        aux = aux->sig;
    }

    return dirZona;
}

int comandoDescargar(tSimulacion *sim, const char *codMuelle, const char *codZona)
{
    int muelleEncontrado = NO_ENCONTRADO;
    tZona *zona = NULL;

    char contDes[TAM_CONTENEDOR], contSig[TAM_CONTENEDOR];

    /// -- Validaciones --
    /// Recorrer los puertos hasta encontrar el ingresado por parámetro
    muelleEncontrado = _buscarMuelle(sim->muelle, sim->escenario->cantMuelles, codMuelle);
    if(muelleEncontrado == NO_ENCONTRADO)
    {
        printf("El muelle '%s' no fue encontrado en el listado...\n", codMuelle);
        return ERROR_PARAMETRO;
    }

    /// Recorrer las zonas hasta encontrar la zona elegida
    zona = _buscarZona(&sim->zonas, codZona);
    if(zona == NULL)
    {
        printf("La zona '%s' no fue encontrada en el listado...\n", codZona);
        return ERROR_PARAMETRO;
    }

    /// Validar que el puerto no esté vacío
    if(!sim->muelle[muelleEncontrado].buque)
    {
        printf("El muelle '%s' no tiene buques...\n", codMuelle);
        return PUERTO_VACIO;
    }

    /// Validar que hay espacio en la zona
    if(zona->cantAlmacenada == zona->capacidad)
    {
        printf("La zona '%s' no tiene espacio para almacenar mas contenedores...\n", codZona);
        return ZONA_LLENA;
    }

    /// -- Extraer contenedor --
    if(desapilar(&sim->muelle[muelleEncontrado].buque->contenedores, contDes, sim->muelle[muelleEncontrado].buque->contenedores->tamDato) == PILA_VACIA)
        return PILA_VACIA;

    /// -- Mostrar siguiente contenedor en el buque --
    if(verTope(&sim->muelle[muelleEncontrado].buque->contenedores, contSig, sim->muelle[muelleEncontrado].buque->contenedores->tamDato) == PILA_VACIA)
    {
        printf("No quedan mas contenedores en el buque %s\n", sim->muelle[muelleEncontrado].buque->idBuque);

        /// Liberar muelle
        sim->muelle[muelleEncontrado].buque = NULL;
    }

    printf("[DEBBUG] Contenedor descargado: %s\n", contDes);
    printf("Siguiente contenedor: %s\n", contSig);

    /// -- Mover contenedor --
    if(apilar(&zona->contenedores, contDes, strlen(contDes)) != OK)
    {
        printf("No se pudo realizar la acción de descargue del contenedor: %s\nMuelle: %s -> Zona: %s\n\n",
               contDes,
               codMuelle,
               codZona);
        return ERROR_MEMORIA;
    }

    return OK;
}

int comandoReubicar(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo)
{
    return OK;
}

int comandoVer(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo)
{
    return OK;
}
































