#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"

typedef struct{
    int cantidad;
    List* canciones;
    char nombre[30];
} ListaCanciones;

typedef struct{
    char nombreC[30];
    int year;
    char artista[15];
    List* generos;
    ListaCanciones* listaC;
} tipoCancion;

void main()
{
    FILE *archivoCanciones = fopen("Canciones.csv", "rw");
    return;
}