#include "archivo.h"

int abrirArchivo(FILE **pf, const char *nombreArchivo, const char *modo)
{
    *pf = fopen(nombreArchivo, modo);
    if(*pf == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo: %s\n", nombreArchivo);
        return ERROR_APERTURA;
    }
    return TODO_OK;
}
