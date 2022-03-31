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
    char generos[50]; //por las funciones que debemos implementar debería ser char**
    char Lista_reproduccion[50]; //faltaba esta variable para agregar canciones
    //ListaCanciones* listaC; quizás no sea necesario esto 
} tipoCancion;

typedef struct{
    int cantidad;
    List* canciones;
    char nombre[30];
} listaCanciones;

char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}

void exportarCanciones (char* nombre_archivo)
{
        FILE *archivoCanciones = fopen(nombre_archivo, "wt");
        return;
}

void importarCanciones(char* nombre_archivo){

    FILE *archivoCanciones = fopen(nombre_archivo, "rt"); //Se busca y abre el archivo indicado por el usuario.
    if (archivoCanciones == NULL)
    {
        //Si no se haya el archivo, se avisa al usuario y se regresa al menú.    
        printf("\nArchivo no encontrado!\n");
        return;
    }
    else
    {
        printf("\nSu archivo fue abierto correctamente!\n");
    }
    
    //Se inicializan variables a utilizar en la funcion get_csv_field
    char linea[1024];
    int i;
    int k = 0;
    //Para este while, se empieza desde la primera línea del archivo, hasta que llegue al final.
    //FALTA TERMINAR ESTA PARTE. LO ÚNICO QUE HACE ES IMPRIMIR LAS LÍNEAS.
    while (fgets(linea, 1023, archivoCanciones) != NULL)
    {
        for (i = 0; i < 1; i++)
        {
                char *aux = get_csv_field(linea, i);
                printf("%s ", aux);
        }
        printf("\n");
        k++;
    }

    fclose(archivoCanciones); //Se importan las canciones y se cierra el archivo.
}

void buscarCancionNombre (char* nombre)
{
        //bool para ver si se encontró alguna canción con el nombre ingresado
        bool encontrado = false;

        //primero iterar por cada lista de reproducción
        listaCanciones* listaDeReproduccion = firstList(listaDeListas);
        while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción
                tipoCancion* cancion = firstList(listaDeReproduccion->canciones);
                while (cancion != NULL)
                {
                        if (strcmp(cancion->nombreC, nombre) == 0)
                        {
                                //se encontró una canción con ese nombre
                                printf("Nombre: %s\n", cancion->nombreC);
                                printf("Artista: %s\n", cancion->artista);
                                printf("Genero(s): %s\n", cancion->generos);
                                printf("Año: %i\n", cancion->year);
                                printf("Lista de reproduccion: %s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
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
        listaCanciones* listaDeReproduccion = firstList(listaDeListas);
        while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción
                tipoCancion* cancion = firstList(listaDeReproduccion->canciones);
                while (cancion != NULL)
                {
                        if (strcmp(cancion->artista, artista) == 0)
                        {
                                //se encontró una canción con el artista ingresado
                                printf("Nombre: %s\n", cancion->nombreC);
                                printf("Artista: %s\n", cancion->artista);
                                printf("Genero(s): %s\n", cancion->generos);
                                printf("Año: %i\n", cancion->year);
                                printf("Lista de reproduccion: %s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
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
        listaCanciones* listaDeReproduccion = firstList(listaDeListas);
        while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción
                tipoCancion* cancion = firstList(listaDeReproduccion->canciones);
                while (cancion != NULL)
                {
                        if (strcmp(cancion->generos, genero) == 0) //esta funcion tienen que coincidir mayusculas y minusculas, es un problema?
                        {
                                //se encontró una canción con ese genero
                                printf("Nombre: %s\n", cancion->nombreC);
                                printf("Artista: %s\n", cancion->artista);
                                printf("Genero(s): %s\n", cancion->generos);
                                printf("Año: %i\n", cancion->year);
                                printf("Lista de reproduccion: %s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
                }
                listaDeReproduccion = nextList(listaDeListas);
        }
        if (encontrado == false)
        {
                printf("No se ha encontrado ninguna canción con el genero ingresado.");
        }
}

void agregarCancion (char nombre[], char artista[], char generos[], int anyo, char Lista_reproduccion[]) 
{
        listaCanciones* listaDeReproduccion;
        tipoCancion * cancionActual = (tipoCancion*)malloc(sizeof(tipoCancion));
        
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
                tipoCancion* primeraCancion = firstList(listaDeReproduccion->canciones);
                if (strcmp(primeraCancion->Lista_reproduccion, Lista_reproduccion) == 0)
                {
                        break; //encontramos que la lista ya existe
                }
                else 
                {
                        //pasar a la siguiente lista de reproducción
                       listaDeReproduccion = nextList(listaDeListas);
                }

                //si la lista no existe, crearla
                if (listaDeReproduccion->canciones == NULL)
                {
                        listaDeReproduccion->canciones = createList();
                        //agregarla  a la lista de listas
                        pushBack(listaDeListas, listaDeReproduccion);
                }
        }

        //validar que la canción no esté ya en la lista de reproducción
        if (listaDeReproduccion != NULL)
        {
                cancionActual = firstList(listaDeReproduccion->canciones); //primera canción de la lista de reproducción
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
                                cancionActual = nextList(listaDeReproduccion->canciones);
                        }
                }
        }
        else
        {
                listaDeReproduccion = (listaCanciones *) malloc (sizeof(listaCanciones));
                strcpy(listaDeReproduccion->nombre, Lista_reproduccion);
                listaDeReproduccion->canciones = createList();
                pushBack(listaDeListas, listaDeReproduccion);
        }

        //la canción no está guardada, hay que agregarla en la lista (junto a todos los datos que trae)
        strcpy(cancionActual->nombreC, nombre);
        strcpy(cancionActual->artista, artista);
        strcpy(cancionActual->generos, generos);
        cancionActual->year = anyo;     
        strcpy(cancionActual->Lista_reproduccion, Lista_reproduccion);
   
        //Aumenta el número de canciones que tiene la lista
        listaDeReproduccion->cantidad++;

        //agregar canción a lista de listas y a la lista de canciones
        pushBack(listaDeReproduccion->canciones, cancionActual);
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

    while (option != 0)
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
        printf("0. Salir\n");

        printf("Indique la opcion: ");
        scanf("%i", &option);

        switch(option)
        {
            case 1: printf("\nIngrese el nombre del archivo: ");
                    scanf("%s", &archivo);
                    importarCanciones(archivo);
                    break;
            case 2: printf("\nIngrese el nombre del archivo que desea crear (o sobreescribir): ");
                    scanf("%s", &archivo);
                    exportarCanciones(archivo);
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
                    getchar();
                    scanf("%[^\n]s", nombre);
                    getchar();
                    buscarCancionNombre(nombre);
                    break;
            case 5: printf("Ingrese el artista de la cancion que desea buscar\n");
                    getchar();
                    scanf("%[^\n]s", artista);
                    getchar();
                    buscarCancionArtista(artista);
                    break;
            case 6: printf("Ingrese el genero de la cancion que desea buscar\n");
                    getchar();
                    scanf("%[^\n]s", generos);
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
            case 0: break;
        }
        printf("\n\n");
    }
    return;
}