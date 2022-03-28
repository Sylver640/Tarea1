#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"

//crear lista de listas, global para que sea fácil de acceder desde distintas funciones (base de datos)
List* listaDeListas = NULL;

typedef struct{
    char nombreC[30];
    int year;
    char artista[15];
    char* generos; //por las funciones que debemos implementar debería ser char**
    char* Lista_reproduccion; //faltaba esta variable para agregar canciones
    //ListaCanciones* listaC; quizás no sea necesario esto 
} tipoCancion;

typedef struct{
    int cantidad;
    List* canciones;
    char nombre[30];
} ListaCanciones;

void importCancion(char* nombre_archivo){

    FILE *archivoCanciones = fopen(nombre_archivo, "rt"); //Se busca y abre el archivo indicado por el usuario.
    if (archivoCanciones == NULL)
    {
        //Si no se haya el archivo, se avisa al usuario y se regresa al menú.    
        printf("Archivo no encontrado!");
        return;
    }
    fclose(archivoCanciones); //Se importan las canciones y se cierra el archivo.
}

void buscarCancionNombre (char* nombre)
{
        //bool para ver si se encontró alguna canción con el nombre ingresado
        bool encontrado = false;

        //primero iterar por cada lista de reproducción
        List* listaDeReproduccion = firstList(listaDeListas);
        while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción
                tipoCancion* cancion = firstList(listaDeReproduccion);
                while (cancion != NULL)
                {
                        if (strcmp(cancion->nombreC, nombre) == 0)
                        {
                                //se encontró una canción con ese nombre
                                printf("%s\n", cancion->nombreC);
                                printf("%s\n", cancion->artista);
                                printf("%s\n", cancion->generos);
                                printf("%i\n", cancion->year);
                                printf("%s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion);
                }
                listaDeReproduccion = nextList(listaDeListas);
        }
        if (encontrado == false)
        {
                printf("No se ha encontrado ninguna canción con el nombre ingresado.");
        }
}

void buscarCancionArtista (char* artista)
{
        //bool para ver si se encontró alguna canción con el artista ingresado
        bool encontrado = false;

        //primero iterar por cada lista de reproducción
        List* listaDeReproduccion = firstList(listaDeListas);
        while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción
                tipoCancion* cancion = firstList(listaDeReproduccion);
                while (cancion != NULL)
                {
                        if (strcmp(cancion->artista, artista) == 0)
                        {
                                //se encontró una canción con el artista ingresado
                                printf("%s\n", cancion->nombreC);
                                printf("%s\n", cancion->artista);
                                printf("%s\n", cancion->generos);
                                printf("%i\n", cancion->year);
                                printf("%s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion);
                }
                listaDeReproduccion = nextList(listaDeListas);
        }
        if (encontrado == false)
        {
                printf("No se ha encontrado ninguna canción con el artista ingresado.");
        }
}

void buscarCancionGenero (char* genero)
{
        //bool para ver si se encontró alguna canción con el genero ingresado
        bool encontrado = false;

        //primero iterar por cada lista de reproducción
        List* listaDeReproduccion = firstList(listaDeListas);
        while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción
                tipoCancion* cancion = firstList(listaDeReproduccion);
                while (cancion != NULL)
                {
                        if (strstr(cancion->generos, genero) == 0) //esta funcion tienen que coincidir mayusculas y minusculas, es un problema?
                        {
                                //se encontró una canción con ese genero
                                printf("%s\n", cancion->nombreC);
                                printf("%s\n", cancion->artista);
                                printf("%s\n", cancion->generos);
                                printf("%i\n", cancion->year);
                                printf("%s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion);
                }
                listaDeReproduccion = nextList(listaDeListas);
        }
        if (encontrado == false)
        {
                printf("No se ha encontrado ninguna canción con el genero ingresado.");
        }
}

void agregarCancion (char* nombre, char* artista, char* generos, int anyo, char* Lista_reproduccion) 
{
        List* listaDeReproduccion = NULL;
        //inicializar la lista de listas si no se ha ocupado antes
        if (listaDeListas == NULL)
        {
                listaDeListas = createList();
        }
        //buscar la lista especificada para ver si existe
        listaDeReproduccion = firstList(listaDeListas);

        //vemos el primer elemento de lista de la canción y ver si el elemento corresponde
        while (listaDeReproduccion != NULL)
        {
                //crear variable de tipo canción para poder usar strcmp
                tipoCancion* primeraCancion = firstList(listaDeReproduccion); 
                if (strcmp(primeraCancion->Lista_reproduccion, Lista_reproduccion) == 0)
                {
                        break; //encontramos que la lista ya existe
                }
                else 
                {
                        //pasar a la siguiente lista de reproducción
                       listaDeReproduccion = nextList(listaDeListas);
                }
        }
        //si la lista no existe, crearla
        if (listaDeReproduccion == NULL)
        {
                listaDeReproduccion = createList();
                //agregarla  a la lista de listas
                pushBack(listaDeListas, listaDeReproduccion);
        } 

        //validar que la canción no esté ya en la lista de reproducción
        tipoCancion* cancionActual = firstList(listaDeReproduccion); //primera canción de la lista de reproducción
        while(cancionActual != NULL)
        {
                //comparar nombre de la canción
                if (strcmp(cancionActual->nombreC, nombre) == 0)
                {
                        //la canción ya está en la lista
                        printf("LA CANCIÓN YA ESTÁ EN LA LISTA.\n");
                        return;
                }
                else
                {
                        //revisar siguiente canción
                        cancionActual = nextList(listaDeReproduccion);
                }
        }

        //la canción no está guardada, hay que agregarla en la lista (junto a todos los datos que trae)
        cancionActual = (tipoCancion*)malloc(sizeof(tipoCancion));
        strcpy(cancionActual->nombreC, nombre);
        strcpy(cancionActual->artista, artista);
        cancionActual->generos = generos;
        cancionActual->year = anyo;
        cancionActual->Lista_reproduccion = Lista_reproduccion;

        //agregar canción a lista de listas y a la lista de canciones
        pushBack(listaDeReproduccion, cancionActual);
        printf("Su cancion fue agregada.\n");
        //pushBack(listaDeCanciones, cancionActual);
}

void main()
{
    char nombre[100], artista[100], Lista_reproduccion[100];
    char generos[100]; //aca no debería ser char* ?
    int anyo;
    tipoCancion* datos;
    FILE* archivoCanciones;
    int option;
    char archivo[100];

    while (option != 11)
    {
        printf("1. Importar canciones desde el archivo\n");
        printf("2. Exportar canciones (CSV)\n");
        printf("3. Agregar cancion\n");
        printf("4. Buscar cancion por nombre\n");
        printf("5. Buscar cancion por artista\n");
        printf("6. Buscar cancion por genero\n");
        printf("7. Eliminar cancion\n");
        printf("8. Mostrar nombres de las listas de reproduccion\n");
        printf("9. Mostrar una lista de reproduccion\n");
        printf("10. Mostrar todas las canciones\n");
        printf("11. Salir\n");

        printf("Indique la opcion: ");
        scanf("%i", &option);

        switch(option)
        {
            case 1: printf("\nIngrese el ubicacion del archivo: ");
                    scanf("%s", &archivo);
                    importCancion(archivo);
                    break;
            case 2: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 3: printf("Ingrese el nombre de la cancion: ");
                    getchar();
                    scanf("%[^\n]s", nombre);
                    getchar();
                    printf("Ingrese el artista de la cancion: ");
                    scanf("%[^\n]s", artista); 
                    getchar();
                    printf("Ingrese el genero de la cancion: "); 
                    scanf("%[^\n]s", generos);
                    getchar();
                    printf("Ingrese el año de la cancion: ");
                    scanf("%d", &anyo);
                    getchar();
                    printf("Ingrese la lista de reproduccion en donde quiere agregar la cancion: ");
                    scanf("%[^\n]s", Lista_reproduccion);
                    getchar();
                    agregarCancion(nombre, artista, generos, anyo, Lista_reproduccion);
                    break;
            case 4: printf("Ingrese el nombre de la cancion que desea buscar\n");
                    scanf("%s", nombre);
                    getchar();
                    buscarCancionNombre(nombre);
                    break;
            case 5: printf("Ingrese el artista de la cancion que desea buscar\n");
                    scanf("%s", artista);
                    getchar();
                    buscarCancionArtista(artista);
                    break;
            case 6: printf("Ingrese el genero de la cancion que desea buscar\n");
                    scanf("%s", generos);
                    getchar();
                    buscarCancionGenero(generos);
                    break;
            case 7: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 8: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 9: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 10: printf("FUNCION NO IMPLEMENTADA\n");
                     break;
            case 11: break;
        }
        printf("\n\n");
    }
    return;
}
