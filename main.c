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
    int option;

    while (option != 8)
    {
        printf("1. Importar canciones desde el archivo\n");
        printf("2. Exportar canciones (CSV)\n");
        printf("3. Agregar cancion\n");
        printf("4. Buscar cancion por nombre\n");
        printf("5. Buscar cancion por artista\n");
        printf("6. Buscar cancion por genero\n");
        printf("7. Eliminar cancion\n");
        printf("8. Salir\n");

        printf("Indique la opcion: ");
        scanf("%i", &option);

        switch(option)
        {
            case 1: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 2: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 3: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 4: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 5: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 6: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 7: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 8: break;
        }
    }
    return;
}