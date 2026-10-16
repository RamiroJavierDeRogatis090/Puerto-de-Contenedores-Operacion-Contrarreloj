#include "comandos.h"

#define OK 0

#define ES_LETRA_MAY(c)  ((c) >= 'A' && (c) <= 'Z')
#define ES_LETRA_MIN(c)  ((c) >= 'a' && (c) <= 'z')
#define ES_DIGITO(c)     ((c) >= '0' && (c) <= '9')
#define ES_ALNUM(c)      (ES_LETRA_MAY(c) || ES_LETRA_MIN(c) || ES_DIGITO(c))

const char *comandoNombre(TipoComando tipo)
{
    switch(tipo)
    {
        case CMD_DES: return "DES";
        case CMD_REU: return "REU";
        case CMD_ENT: return "ENT";
        case CMD_VER: return "VER";
        case CMD_ESP: return "ESP";
        case CMD_FIN: return "FIN";
        default:      return "INVALIDO";
    }
}

/* Busca en la lista según los primeros 3 caracteres. NULL si no pertenece. */
const tDefComando *_buscarDefinicion(const char *comando)
{
    for(unsigned i = 0; i < CANT_COMANDOS; i++)
        if(strncmp(comando, COMANDOS[i].nombre, LON_CODIGO) == 0)
            return &COMANDOS[i];
    return NULL;
}

bool _esAlfanumericoN(const char *s, unsigned n)
{
    for(unsigned i = 0; i < n; i++)
        if(!ES_ALNUM(s[i]))
            return false;
    return true;
}

bool comandoValidar(const char *comando)
{
    const tDefComando *def = _buscarDefinicion(comando);
    unsigned lon = strlen(comando);

    if(!def)
        return false;                       // el código no pertenece a la lista

    if(def->cantArgs == 0)
        return lon == LON_SIN_ARGS;         // no admite nada más

    // Comandos con 2 argumentos: "XXX AA BB"
    return lon == LON_CON_ARGS
        && comando[3] == ' '
        && comando[6] == ' '
        && _esAlfanumericoN(comando + 4, LON_ARG)
        && _esAlfanumericoN(comando + 7, LON_ARG);
}

void comandoExtraer(const char *comando, tComando *cmd)
{
    const tDefComando *def = _buscarDefinicion(comando);

    cmd->tipo = def->tipo;
    cmd->arg_1[0] = '\0';                   // argumentos sin uso: cadena vacía
    cmd->arg_2[0] = '\0';

    if(def->cantArgs == 2)
    {
        memcpy(cmd->arg_1, comando + 4, LON_ARG);
        cmd->arg_1[LON_ARG] = '\0';
        memcpy(cmd->arg_2, comando + 7, LON_ARG);
        cmd->arg_2[LON_ARG] = '\0';
    }
}

void _mostrarComandos()
{
    puts("DES <Cod Muelle> <Cod Zona>");
    puts("REU <Cod Zona Origen> <Cod Zona Destino>");
    puts("ENT");
    puts("VER");
    puts("ESP");
    puts("FIN");
}

/* Insiste hasta obtener un comando válido y lo deja cargado en *cmd */
void comandoSolicitar(tComando *cmd)
{
    char buffer[TAM_BUFFER];
    bool comandoValido;

    puts("Ingrese un comando de lista:");
    _mostrarComandos();

    do
    {
        comandoValido = false;

        if(fgets(buffer, sizeof(buffer), stdin))
        {
            char *salto = strchr(buffer, '\n');
            if(salto)
            {
                *salto = '\0';
                comandoValido = comandoValidar(buffer);
            }
            else
            {
                // Input del usuario excede al buffer, se limpia para la siguiente entrada
                int c;
                while((c = getchar()) != '\n' && c != EOF);
            }
        }

        if(!comandoValido)
        {
            puts("El comando ingresado no respeta la sintaxis indicada o no existe. Intente nuevamente:");
            _mostrarComandos();
        }
    } while(!comandoValido);

    comandoExtraer(buffer, cmd);
}

void _comandoEsperar(unsigned *cronometro)
{
    (*cronometro)++;
}

void _comandoDescargar(unsigned *cronometro)
{
    (*cronometro)++;
}

void _comandoEntregar(unsigned *cronometro)
{
    (*cronometro)++;
}

void _comandoReubicar(unsigned *cronometro)
{
    (*cronometro)++;
}

void _comandoVer(unsigned *cronometro)
{
    (*cronometro)++;
}

unsigned comandoEjecutar(tComando *cmd, unsigned *cronometro)
{
    switch(cmd->tipo)
    {
    case CMD_ESP:
        _comandoEsperar(cronometro);
        break;
    case CMD_DES:
        _comandoDescargar(cronometro);
        break;
    case CMD_ENT:
        _comandoEntregar(cronometro);
        break;
    case CMD_REU:
        _comandoReubicar(cronometro);
        break;
    case CMD_VER:
        _comandoVer(cronometro);
        break;
    case CMD_FIN:
        return FIN;
    case CMD_INVALIDO:
        puts("\n[EJECUTAR COMANDO] Comando no reconocido");
        break;
    }

    return OK;
}
