#include "comando.h"

void operaciones(tSimulacion *sim, const tConfig *pConfig, tPuntos *puntaje, unsigned *tiempo)
{
    char op[TAM_OP], origen[TAM_ORIGEN], destino[TAM_DESTINO], comando[TAM_COMANDO];
    int operacionCompletada = 0, codigoOp;

    while(operacionCompletada == 0)
    {
        op[0] = '\0';
        origen[0] = '\0';
        destino[0] = '\0';

        printf("\nOPERADOR>");
        fflush(stdin);
        fgets(comando, TAM_COMANDO, stdin);

        sscanf(comando, "%s %s %s", op, origen, destino);

        printf("\nCOMANDO DEL OPERADOR: %s %s %s\n", op, origen, destino);

        if(strcmpi(op, "DES") == 0)
            codigoOp = CMD_DES;
        else if(strcmpi(op, "ENT") == 0)
            codigoOp = CMD_ENT;
        else if(strcmpi(op, "REU") == 0)
            codigoOp = CMD_REU;
        else if(strcmpi(op, "ESP") == 0)
            codigoOp = CMD_ESP;
        else if(strcmpi(op, "VER") == 0)
            codigoOp = CMD_VER;
        else
            codigoOp = CMD_INVALIDO;

        switch(codigoOp)
        {
            case CMD_DES:
                if(comandoDescargar(sim, origen, destino, puntaje, &opActual))
                {
                    operacionCompletada = 1;

                    *tiempo += pConfig->tiempDesCont;
                }
                else
                    puts("--ERROR AL INGRESAR ORIGEN/DESTINO O ZONAS DE ALMACENAMIENTO LLENAS--");
                break;
            case CMD_ENT:
                if(comandoEntregar(sim, &opActual))
                {
                    operacionCompletada = 1;

                    *tiempo += pConfig->tiempCarCami;
                }
                else
                    puts("--ERROR AL ENTREGAR UN CONTENEDOR: NO SE ENCUENTRA EL CONTENEDOR O NO HAY CAMION PARA ENTREGAR--");
                break;
            case CMD_REU:
                if(comandoReubicar(sim, origen, destino, &opActual))
                {
                    operacionCompletada = 1;
                    *tiempo += pConfig->tiempReuCont;
                }
                else
                    puts("--ERROR AL INGRESAR LAS ZONAS O REVISE LA DISPONIBILIDAD DE LAS ZONAS--");
                break;
            case CMD_ESP:
                (*tiempo)++;
                operacionCompletada = 1;
                break;
            case CMD_VER:
                if(comandoVer(sim))
                    operacionCompletada = 1;
                else
                    puts("ERROR DE VISTA.");
                break;
            default:
                puts("--OPERACION INVALIDA: INGRESE UNA OPERACION VALIDA--");
                break;
        }


        //system("pause");
    }
}

int comandoEntregar(tSimulacion *sim)
{
    tZona zonaLocal;
    tCamion camionLocal;
    tLista listaAux;
    char contTope[TAM_CONTENEDOR];
    int exito = 0;

    if(!verPrimeroEnCola(&sim->colaCamiones, &camionLocal, sizeof(tCamion)))
    {
        printf("No hay camiones esperando.");
        return exito;
    }

    CrearLista(&listaAux);

    while(sacarPrimeroLista(&sim->zonas, &zonaLocal, sizeof(tZona)))
    {
        if(!exito &&
           verTope(&zonaLocal.contenedores, contTope, TAM_CONTENEDOR) &&
           strcmp(contTope, camionLocal.idContenedor) == 0)
        {
            desapilar(&zonaLocal.contenedores, contTope, TAM_CONTENEDOR);
            zonaLocal.cantAlmacenada--;

            desacolar(&sim->colaCamiones, &camionLocal, sizeof(tCamion));
            exito = 1;

            printf("Entrega exitosa: Contenedor %s (Zona %s) entregado al camion %s.\n",
                   contTope, zonaLocal.idZona, camionLocal.idCamion);
        }

        InsertarAlFinalLista(&listaAux, &zonaLocal, sizeof(tZona));
    }

    while(sacarPrimeroLista(&listaAux, &zonaLocal, sizeof(tZona)))
        InsertarAlFinalLista(&sim->zonas, &zonaLocal, sizeof(tZona));

    if(!exito)
        printf("Operacion invalida: El contenedor %s (pedido por %s) no esta en el tope de ninguna zona.\n",
               camionLocal.idContenedor, camionLocal.idCamion);

    return exito;
}

int comandoReubicar(tSimulacion *sim, const char *codZonaA, const char *codZonaB)
{
    tLista listaAux;
    tZona zonaAux;
    char contMover[TAM_CONTENEDOR];
    int origenOk = 0, destinoOk = 0;

    if(strcmp(codZonaA, codZonaB) == 0)
    {
        printf("Error: La zona de origen y destino no pueden ser la misma.\n");
        return 0;
    }

    CrearLista(&listaAux);

    while(sacarPrimeroLista(&sim->zonas, &zonaAux, sizeof(tZona)))
    {
        if(strcmpi(zonaAux.idZona, codZonaA) == 0)
        {
            if(verTope(&zonaAux.contenedores, contMover, TAM_CONTENEDOR))
                origenOk = 1;
            else
                printf("Error: La zona origen %s esta vacia.\n", codZonaA);
        }
        else if(strcmpi(zonaAux.idZona, codZonaB) == 0)
        {
            if(zonaAux.cantAlmacenada < zonaAux.capacidad)
                destinoOk = 1;
            else
                printf("Error: La zona destino %s esta llena.\n", codZonaB);
        }

        InsertarAlFinalLista(&listaAux, &zonaAux, sizeof(tZona));
    }

    if(!origenOk || !destinoOk)
    {
        while(sacarPrimeroLista(&listaAux, &zonaAux, sizeof(tZona)))
            InsertarAlFinalLista(&sim->zonas, &zonaAux, sizeof(tZona));

        if(!origenOk && !destinoOk)
            printf("Error: Verifique los codigos de zona ingresados.\n");
        return ERROR;
    }

    while(sacarPrimeroLista(&listaAux, &zonaAux, sizeof(tZona)))
    {
        if(strcmp(zonaAux.idZona, codZonaA) == 0)
        {
            desapilar(&zonaAux.contenedores, contMover, TAM_CONTENEDOR);
            zonaAux.cantAlmacenada--;
        }
        else if(strcmp(zonaAux.idZona, codZonaB) == 0)
        {
            apilar(&zonaAux.contenedores, contMover, strlen(contMover) + 1);
            zonaAux.cantAlmacenada++;
        }

        InsertarAlFinalLista(&sim->zonas, &zonaAux, sizeof(tZona));
    }

    printf("Reubicacion exitosa: %s movido de %s a %s.\n", contMover, codZonaA, codZonaB);
    return OK;

}

int _buscarMuelle(tMuelle *muelles, unsigned cantMuelles, const char *codMuelle)
{
    int i = 0, indice = NO_ENCONTRADO;
    while(i < cantMuelles && indice == NO_ENCONTRADO)
    {
        if(strcmpi(codMuelle, muelles[i].idMuelle) == 0)
            indice = i;
        i++;
    }
    return indice;
}

int comandoDescargar(tSimulacion *sim, const char *codMuelle, const char *codZona)
{
    int muelleEncontrado = NO_ENCONTRADO;
    tZona bufferZona;
    int zonaEncontrada = 0, exito = 0;
    tLista listaAux;
    char contDes[TAM_CONTENEDOR];

    muelleEncontrado = _buscarMuelle(sim->muelle, sim->escenario->cantMuelles, codMuelle);
    if(muelleEncontrado == NO_ENCONTRADO)
    {
        printf("El muelle '%s' no fue encontrado en el listado...\n", codMuelle);
        return ERROR_PARAMETRO;
    }

    if(!sim->muelle[muelleEncontrado].buque)
    {
        printf("El muelle '%s' no tiene buques...\n", codMuelle);
        return MUELLES_VACIOS;
    }

    CrearLista(&listaAux);

    while(sacarPrimeroLista(&sim->zonas, &bufferZona, sizeof(tZona)))
    {
        if(strcmpi(bufferZona.idZona, codZona) == 0)
        {
            zonaEncontrada = 1;
            if(bufferZona.cantAlmacenada < bufferZona.capacidad)
            {
                desapilar(&sim->muelle[muelleEncontrado].buque->contenedores, contDes, TAM_CONTENEDOR);
                sim->muelle[muelleEncontrado].buque->cantAlmacenada--;

                apilar(&bufferZona.contenedores, contDes, TAM_CONTENEDOR);
                bufferZona.cantAlmacenada++;
                exito = 1;

                if(sim->muelle[muelleEncontrado].buque->cantAlmacenada == 0)
                {
                    free(sim->muelle[muelleEncontrado].buque);
                    sim->muelle[muelleEncontrado].buque = NULL;
                }
            }
        }
        InsertarAlFinalLista(&listaAux, &bufferZona, sizeof(tZona));
    }

    while(sacarPrimeroLista(&listaAux, &bufferZona, sizeof(tZona)))
        InsertarAlFinalLista(&sim->zonas, &bufferZona, sizeof(tZona));

    if(!zonaEncontrada)
        return ERROR_PARAMETRO;

    return exito;
}

int comandoVer(tSimulacion *sim)
{
    tCola colaAux;
    tCamion camionLocal;
    int cont = 0;

    if(colaVacia(&sim->colaCamiones))
    {
        printf("No hay camiones esperando.\n");
        return COLA_VACIA;
    }

    crearCola(&colaAux);

    while(desacolar(&sim->colaCamiones, &camionLocal, sizeof(tCamion)))
    {
        if(cont < 3)
            printf("%d - %s ---> solicita %s.\n", cont+1, camionLocal.idCamion, camionLocal.idContenedor);
        cont++;
        acolar(&colaAux, &camionLocal, sizeof(tCamion));
    }

    while(desacolar(&colaAux, &camionLocal, sizeof(tCamion)))
        acolar(&sim->colaCamiones, &camionLocal, sizeof(tCamion));

    return OK;
}


