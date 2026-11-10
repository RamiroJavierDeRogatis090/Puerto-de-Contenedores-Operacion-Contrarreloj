#include "operador.h"
#include "indice.h"

int validarNombre(const char *nombre)
{
    int tieneLetra = 0;
    while(*nombre)
    {
        if(isalpha((unsigned char)*nombre))
        {
            tieneLetra = 1;
        }
        else
        {
            if(!isspace((unsigned char)*nombre))
            {
                return 0;
            }
        }
        nombre++;
    }
    return tieneLetra;
}

int solicitarNombreOperador(char *nombre)
{
    do
    {
        printf("Ingrese su apellido y nombre: ");
        scanf(" %49[^\n]", nombre);
        if(!validarNombre(nombre))
        {
            puts("NOMBRE INVALIDO. INGRESE CORRECTAMENTE");
        }
    }while(!validarNombre(nombre));
    normalizarNombre(nombre);
    return TODO_OK;
}

char *normalizarNombre(char* cad)
{
    char *lect = cad;
    char *esc = cad;


    while (*lect && isspace((unsigned char)*lect)) lect++;

    int primeraLetra = 1;

    while (*lect) {
        if (isspace((unsigned char)*lect)) {

            if (esc > cad && *(esc - 1) != ' ')
                *esc++ = ' ';
            while (*lect && isspace((unsigned char)*lect)) lect++;
            primeraLetra = 1;
        } else if (*lect == ',') {
            if (esc > cad && *(esc - 1) == ' ') esc--;
            *esc++ = ',';
            lect++;


            if (*lect != ' ')
            {
                size_t len = strlen(lect);
                memmove(esc + 1, lect, len + 1);
                *esc = ' ';
                esc++;
                lect = esc;
            }

            primeraLetra = 1;
        } else {
            if (primeraLetra)
            {
                *esc++ = toupper((unsigned char)*lect);
                primeraLetra = 0;
            } else {
                *esc++ = tolower((unsigned char)*lect);
            }
            lect++;
        }
    }

    if (esc > cad && isspace((unsigned char)*(esc - 1))) esc--;
    *esc = '\0';


    if (!strchr(cad, ',')) {
        char *primerEspacio = strchr(cad, ' ');
        if (primerEspacio)
        {
            memmove(primerEspacio + 2, primerEspacio + 1, strlen(primerEspacio + 1) + 1);
            *primerEspacio = ',';
            *(primerEspacio + 1) = ' ';
        }
    }

    return cad;
}

int buscarOperador(const tArbol *pa, const char *nombre, tOperador *operador, const char *nombreArchivo)
{
    FILE *arch;
    tIndice clave;
    if(strlen(nombre) >= MAX_TAM_NOMBRE)
    {
        return NOMBRE_INVALIDO;
    }
    strcpy(clave.clave.nombre, nombre);
    if(buscarEnArbol(pa, &clave, sizeof(tIndice), compararClaveIdx) != DATO_ENCONTRADO)
    {
        return DATO_NO_ENCONTRADO;
    }
    if(abrirArchivo(&arch, nombreArchivo, "rb") != TODO_OK)
    {
        return ERROR_LECTURA_OPERADOR;
    }
    fseek(arch, (long)clave.indiceRegistro * sizeof(tOperador), SEEK_SET);
    fread(operador, sizeof(tOperador), 1, arch);
    fclose(arch);
    return DATO_ENCONTRADO;
}

int registrarOperador(tArbol *pa, const char *nombre, tOperador *operador, const char *nombreArchivo, const char *nombreArchivoIdx)
{
    FILE *arch;
    unsigned posNueva;
    int ret;
    if(strlen(nombre) >= MAX_TAM_NOMBRE)
    {
        return NOMBRE_INVALIDO;
    }
    ret = buscarOperador(pa, nombre, operador, nombreArchivo);
    if(ret == DATO_ENCONTRADO)
    {
        return OPERADOR_EXISTENTE;
    }
    if(ret != DATO_NO_ENCONTRADO)
    {
        return ret;
    }
    if(abrirArchivo(&arch, nombreArchivo, "ab") != TODO_OK)
    {
        return ERROR_ESCRITURA_OPERADOR;
    }
    fseek(arch, 0L, SEEK_END);
    posNueva = (unsigned)(ftell(arch) / sizeof(tOperador));
    strcpy(operador->nombre, nombre);
    operador->puntajeAcumulado = 0;
    fwrite(operador, sizeof(tOperador), 1, arch);
    fclose(arch);
    ret = registrarNuevoUsuarioEnIndice(pa, nombre, posNueva, nombreArchivoIdx);
    if(ret != TODO_OK)
    {
        return ERROR_ACTUALIZACION_INDICE;
    }
    return OPERADOR_REGISTRADO;
}

int iniciarGestionOperadores(tArbol *pa, const char *nombreArchivo, const char *nombreArchivoIdx)
{
    FILE *archOp, *archIdx;
    crearArbol(pa);
    if(abrirArchivo(&archOp, nombreArchivo, "rb") != TODO_OK)
    {
        if(abrirArchivo(&archOp, nombreArchivo, "wb") != TODO_OK)
        {
            return ERROR_INICIALIZACION;
        }
        fclose(archOp);
        if(abrirArchivo(&archIdx, nombreArchivoIdx, "wb") != TODO_OK)
        {
            return ERROR_INICIALIZACION;
        }
        fclose(archIdx);
        return TODO_OK;
    }
    fclose(archOp);
    if(indexarArchivoOrdenado(pa, nombreArchivoIdx) != TODO_OK)
    {
        return ERROR_INICIALIZACION;
    }
    return TODO_OK;
}

int obtenerOperadorActual(tArbol *pa, const char *nombre, tOperador *operador, const char *nombreArchivo, const char *nombreArchivoIdx)
{
    int ret;
    ret = buscarOperador(pa, nombre, operador, nombreArchivo);
    if(ret == DATO_ENCONTRADO)
    {
        return TODO_OK;
    }
    if(ret != DATO_NO_ENCONTRADO)
    {
        return ret;
    }
    ret = registrarOperador(pa, nombre, operador, nombreArchivo, nombreArchivoIdx);
    if(ret == OPERADOR_REGISTRADO)
    {
        return TODO_OK;
    }
    return ret;
}

int actualizarPuntajeOperador(const tArbol *pa, tOperador *operador, int puntos, const char *nombreArchivo)
{
    FILE *arch;
    tIndice indice;
    strcpy(indice.clave.nombre, operador->nombre);
    if(buscarEnArbol(pa, &indice, sizeof(tIndice), compararClaveIdx) != DATO_ENCONTRADO)
    {
        return DATO_NO_ENCONTRADO;
    }
    if(abrirArchivo(&arch, nombreArchivo, "r+b") != TODO_OK)
    {
        return ERROR_ACTUALIZACION_OPERADOR;
    }
    fseek(arch, (long)indice.indiceRegistro * sizeof(tOperador), SEEK_SET);
    fread(operador, sizeof(tOperador), 1, arch);
    operador->puntajeAcumulado += puntos;
    fseek(arch, (long)indice.indiceRegistro * sizeof(tOperador), SEEK_SET);
    fwrite(operador, sizeof(tOperador), 1, arch);
    fclose(arch);
    return OPERADOR_ACTUALIZADO;
}
