#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXTO_MENU 35

char menu(const char matriz_menu[][MAX_TEXTO_MENU], const char *titulo);
char opcion(const char matriz_menu[][MAX_TEXTO_MENU], const char *titulo, const char *mensaje);

#endif // INTERFAZ_H_INCLUDED
