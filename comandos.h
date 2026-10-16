#ifndef COMANDOS_H_INCLUDED
#define COMANDOS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FIN 8

#define TAM_BUFFER   128
#define LON_CODIGO   3
#define LON_ARG      2    // Tamaño de los còdigos
#define LON_SIN_ARGS (LON_CODIGO)                                    // "ENT"
#define LON_CON_ARGS (LON_CODIGO + 1 + LON_ARG + 1 + LON_ARG)        // "DES AB CD"
#define CANT_COMANDOS (sizeof(COMANDOS) / sizeof(tDefComando))

typedef enum
{
    CMD_INVALIDO = -1,
    CMD_DES,
    CMD_REU,
    CMD_ENT,
    CMD_VER,
    CMD_ESP,
    CMD_FIN
} TipoComando;

typedef struct
{
    TipoComando tipo;
    char arg_1[LON_ARG + 1];   // 2 caracteres + '\0'
    char arg_2[LON_ARG + 1];
} tComando;

/* Lista de comandos conocidos: nombre, tipo y cantidad de argumentos */
typedef struct
{
    const char *nombre;
    TipoComando tipo;
    int cantArgs;
} tDefComando;

static const tDefComando COMANDOS[] =
{
    {"DES", CMD_DES, 2},
    {"REU", CMD_REU, 2},
    {"ENT", CMD_ENT, 0},
    {"VER", CMD_VER, 0},
    {"ESP", CMD_ESP, 0},
    {"FIN", CMD_FIN, 0},
};

const char *comandoNombre(TipoComando tipo);

const tDefComando *_buscarDefinicion(const char *comando);
bool _esAlfanumericoN(const char *s, unsigned n);
bool comandoValidar(const char *comando);
void comandoExtraer(const char *comando, tComando *cmd);
void _mostrarComandos();
void comandoSolicitar(tComando *cmd);

void _comandoEsperar(unsigned *cronometro);
void _comandoDescargar(unsigned *cronometro);
void _comandoEntregar(unsigned *cronometro);
void _comandoReubicar(unsigned *cronometro);
void _comandoVer(unsigned *cronometro);
unsigned comandoEjecutar(tComando *cmd, unsigned *cronometro);

#endif // COMANDOS_H_INCLUDED
