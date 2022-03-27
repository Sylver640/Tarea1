#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"

//crear lista de listas, global para que sea fácil de acceder desde distintas funciones (base de datos)
List* listaDeListas = NULL;
List* listaDeCanciones = NULL;

typedef struct{
    char nombreC[30];
    int year;
    char artista[15];
    char** generos; //por las funciones que debemos implementar debería ser char**
    char* Lista_reproduccion; //faltaba esta variable para agregar canciones
    //ListaCanciones* listaC; quizás no sea necesario esto 
} tipoCancion;

typedef struct{
    int cantidad;
    List* canciones;
    char nombre[30];
} ListaCanciones;

/*FILE* importCancion(char* nombre_archivo){
        
    while (nombre_archivo != NULL)
    {
        scanf("%s", &nombre_archivo);
        if (nombre_archivo == NULL)
            printf("NO EXISTE EL ARCHIVO CON ESE NOMBRE");
    } 
    FILE *archivoCanciones = fopen(nombre_archivo, "wt");
    return archivoCanciones;

}*/

void agregarCancion (char* nombre, char* artista, char** generos, int anyo, char* Lista_reproduccion) 
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
        pushBack(listaDeCanciones, cancionActual);
}

/*void buscar_cancion(char nombre)
{
   List* lista_revisora = createList();
   bool marcador = false;
   if( listaDeListas == NULL)
   {
        printf("La canción buscada no existe en ninguna lista");
   }
   lista_revisora=firstList(listaDeListas);
   char* revisor;
   revisor=lista_revisora->head->nombre;
   while(true)
   {
           if(revisor==nombre)
           {
                printf("los datos de la cancion");
                marcador= true;
           }
           if(revisor->next != NULL)
           {
                revisor=revisor->next->nombre;
           }
           else{
                  lista_revisora=nextList(listaDeListas);
                  if(lista_revisora==NULL) break;
                  revisor=lista_revisora->head->nombre;
             }
   }
   if(marcador==false)
   {
           printf("no ta la cancion");
   }
}*/

void main()
{
    char nombre[100], artista[100], Lista_reproduccion[100];
    char** generos = NULL;
    int anyo;
    tipoCancion* datos;
    FILE* archivoCanciones;
    int option;
    char* archivo;
    listaDeCanciones = createList();

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
            case 1: printf("\nIngrese el nombre del archivo: ");
                    scanf("%s", &archivo);
                    //archivoCanciones = importCancion(archivo);
                    break;
            case 2: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 3: printf("Ingrese el nombre de la canción: ");
                    scanf("%s\n", nombre);
                    printf("Ingrese el artista de la canción: ");
                    scanf("%s\n", artista); //FALTA HACER UN PRINTF EN AGREGAR CANCION SI ES QUE YA ESTA EN UNA LISTA O SI HAY QUE CREAR UNA LISTA ETC
                    //scanf("%s", generos);
                    printf("Ingrese el año de la canción: ");
                    scanf("%d\n", &anyo);
                    printf("Ingrese la lista de reproducción en donde quiere agregar la canción: ");
                    scanf("%s\n", Lista_reproduccion);
                    agregarCancion(nombre, artista, generos, anyo, Lista_reproduccion);
                    break;
            case 4: printf("Ingrese el nombre de la canción que desea buscar\n");
                    scanf("%s", &nombre);
                    buscar_cancion(nombre);
                    break;
            case 5: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 6: printf("FUNCION NO IMPLEMENTADA\n");
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
    }
    fclose(archivoCanciones);
    return;
}
