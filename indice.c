#include "indice.h"

int compararClaveIdx(const void *a, const void *b)
{
    const tIndice *idx1 = (const tIndice *)a;
    const tIndice *idx2 = (const tIndice *)b;
    return strcmp(idx1->clave.nombre, idx2->clave.nombre);
}

int indexarArchivoOrdenado(tArbol *pa, const char *nombreArchivo)
{
    FILE *arch;
    if(abrirArchivo(&arch, nombreArchivo, "rb") != TODO_OK)
    {
        return ERROR_APERTURA;
    }
    fseek(arch, 0L, SEEK_END);
    cargarArchivoEnIndice(pa, arch, 0, ftell(arch) / sizeof(tIndice) - 1);
    fclose(arch);
    return TODO_OK;
}

void cargarArchivoEnIndice(tArbol *pa, FILE *arch, int inicio, int fin)
{
    int medio;
    tIndice indice;
    if(inicio > fin)
    {
        return;
    }
    medio = (fin + inicio) / 2;
    fseek(arch, medio * sizeof(tIndice), SEEK_SET);
    fread(&indice, 1, sizeof(tIndice), arch);
    insertarEnArbol(pa, &indice, sizeof(tIndice), compararClaveIdx);
    cargarArchivoEnIndice(pa, arch, inicio, medio - 1);
    cargarArchivoEnIndice(pa, arch, medio + 1, fin);
}

int grabarIndiceEnArchivo(const tArbol *pa, const char *nombreArchivo)
{
    FILE *arch;
    if(abrirArchivo(&arch, nombreArchivo, "wb") != TODO_OK)
    {
        return ERROR_ARCHIVO_INDICE;
    }
    recorrerInOrden(pa, 0, arch, grabarNodoEnArchivo);
    fclose(arch);
    return TODO_OK;
}

void grabarNodoEnArchivo(void *info, unsigned tam, unsigned n, void *params)
{
    FILE *arch = (FILE *)params;
    fwrite(info, tam, 1, arch);
}

int registrarNuevoUsuarioEnIndice(tArbol *pa, const char *nombre, unsigned posNueva, const char *nombreArchivoIndice)
{
    tIndice nuevo;
    int ret;
    strncpy(nuevo.clave.nombre, nombre, TAM_MAX_NOMBRE - 1);
    nuevo.clave.nombre[TAM_MAX_NOMBRE - 1] = '\0';
    nuevo.indiceRegistro = posNueva;
    ret = insertarEnArbol(pa, &nuevo, sizeof(tIndice), compararClaveIdx);
    if(ret != TODO_OK)
    {
        return ret;
    }
    return grabarIndiceEnArchivo(pa, nombreArchivoIndice);
}
