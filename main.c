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
    char** generos; //por las funciones que debemos implementar debería ser char**
    char* Lista_reproduccion; //faltaba esta variable para agregar canciones
    ListaCanciones* listaC; //quizás no sea necesario esto 
} tipoCancion;

typedef struct{
    int cantidad;
    List* canciones;
    char nombre[30];
} ListaCanciones;

FILE* importCancion(char* nombre_archivo){
        
    while (nombre_archivo != NULL)
    {
        scanf("%s", &nombre_archivo);
        if (nombre_archivo == NULL)
            printf("NO EXISTE EL ARCHIVO CON ESE NOMBRE");
    } 
    FILE *archivoCanciones = fopen(nombre_archivo, "wt");
    return archivoCanciones;

}

bool revisar_cancion(char *nombre,char * artista, char generos, int *ano,char * Lista_reproduccion, tipoCancion datos)
{
       void buscador;
       buscador = datos->listaC.head;
       while(buscador != NULL && buscador.data!=Lista_reproduccion)
       {
           buscador=buscador->next;
       }|
       if(buscador==NULL)
       {
          datos->listaC = createList();
       }

}

void agregar_cancion((char nombre, char* artista, char generos, int ano, char* Lista_reproducción)
{

        tipoCancion *ingresar;
        strcpy(nombre,ingresar->nombre );
        strcpy(artista, ingresar->artista );
        void pushFront( ingresar->generos, * generos);
        ingresar->year=ano;

}

void agregarCancion (char* nombre, char* artista, char** géneros, int año, char* Lista_reproduccion)
{
        List* listaDeReproduccion = NULL;
        //inicializar la lista de istas si no se ha ocupado antes
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
                }
        }
        //si la lista no existe, crearla
        if (listaDeReproduccion == NULL)
        {
                listaDeReproduccion = createList();
                //agregarla  a la lista de listas

        } 

}

void main()
{
    char nombre, artista, generos, Lista_reproduccion;
    int ano;
    tipoCancion* datos;
    FILE* archivoCanciones;
    int option;
    char* archivo;

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
            case 3: scanf("%s", &nombre);
                    scanf("%s", &artista);
                    scanf("%s", &generos);
                    scanf("%d", &ano);
                    scanf("%s", &Lista_reproduccion);
                    revisar_cancion(nombre, artista, generos, ano, Lista_reproduccion, datos);
                    agregar_cancion( nombre, artista,  generos, ano,  Lista_reproduccion);
                    break;
            case 4: printf("FUNCION NO IMPLEMENTADA\n");
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

/*agregar canción debe agregar un nodo a la lista 1, 2 o 3
deberían ser listas separadas por algunos requerimientos de la tarea, en especial el 8
lista enlazada de listas enlazadas, pueden ser tipos distintos (nodo de la lista base, nodo lista canciones etc) */

