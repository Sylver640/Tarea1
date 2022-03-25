#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"

typedef struct{
    int cantidad;
    // canciones(Lista);
    char nombre[30];

} ListaCanciones;

typedef struct{
    char nombreC[30];
    int year;
    char artista[15];
    // generos(Lista);
    // listaC(ListaCanciones);


} tipoCancion;

int main()
{
    printf("Hola Mundo\n");
    printf("Hola\n");
    printf("rodrigo gracias por la ayuda");
    printf("de nada, jota");
    return 0;
}