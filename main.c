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

void agregarCancion (char *nombre, char *artista, char *generos, int anyo, char *Lista_reproduccion, List* listaGlobal) 
{
         //inicializar la lista de listas si no se ha ocupado antes
        if (listaDeListas == NULL)
        {
                listaDeListas = createList();
        }

        listaCanciones* listaDeReproduccion;
        tipoCancion* cancionAgregada = (tipoCancion*)malloc(sizeof(tipoCancion));
        tipoCancion* cancionAuxiliar;
        //la canción no está guardada, hay que agregarla en la lista (junto a todos los datos que trae)
        strcpy(cancionAgregada->nombreC, nombre);
        strcpy(cancionAgregada->artista, artista);
        strcpy(cancionAgregada->generos, generos);
        cancionAgregada->year = anyo;
        strcpy(cancionAgregada->Lista_reproduccion, Lista_reproduccion);
        
        //buscar la lista especificada para ver si existe
        listaDeReproduccion = firstList(listaDeListas);
        
        while (listaDeReproduccion != NULL)
        {
                //tipoCancion* primeraCancion = firstList(listaDeReproduccion->canciones);
                if (strcmp(listaDeReproduccion->nombre, Lista_reproduccion) == 0)
                {
                        break; //encontramos que la lista ya existe
                }
                else
                {
                        listaDeReproduccion = nextList(listaDeListas);
                }
        }

        //si la lista no existe, crearla
        if (listaDeReproduccion == NULL)
        {
                listaDeReproduccion = (listaCanciones*) malloc(sizeof(listaCanciones));
                strcpy(listaDeReproduccion->nombre, Lista_reproduccion);
                listaDeReproduccion->cantidad = 0;
                listaDeReproduccion->canciones = createList();
                pushBack(listaDeListas, listaDeReproduccion);
        }

        if (!firstList(listaDeReproduccion->canciones))
        {
                pushFront(listaDeReproduccion->canciones, cancionAgregada); //primera canción de la lista de reproducción
        }
        else
        {
                cancionAuxiliar = firstList(listaDeReproduccion->canciones);
                printf("%s\n", cancionAgregada->nombreC);
                while(cancionAuxiliar != NULL)
                {
                        //comparar nombre de la canción
                        //if (strcmp(cancionAgregada->nombreC, nombre) == 0 && strcmp(cancionAgregada->artista, artista) == 0 &&
                        //    strcmp(cancionAgregada->generos, generos) == 0 && cancionAgregada->year == anyo)
                        if (cancionAuxiliar == cancionAgregada)
                        {
                                //la canción ya está en la lista
                                printf("LA CANCIÓN YA ESTÁ EN LA LISTA.\n");
                                return;
                        }
                        else
                        {
                                //revisar siguiente canción
                                cancionAuxiliar = nextList(listaDeReproduccion->canciones);
                        }
                }
        }
   
        //Aumenta el número de canciones que tiene la lista
        listaDeReproduccion->cantidad++;

        //agregar canción a lista de listas y a la lista de canciones
        pushBack(listaDeReproduccion->canciones, cancionAgregada);
        printf("Su cancion fue agregada.\n");
        pushBack(listaGlobal, cancionAgregada);
}

void importarCanciones(char* nombre_archivo, List* listaGlobal){

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
                char *nombre = get_csv_field(linea, i);
                char *artista = get_csv_field(linea, i+1);
                char *generos = get_csv_field(linea, i+2);
                char *anyo = get_csv_field(linea, i+3);
                int anyoAEntero = atoi(anyo);
                char *lista = get_csv_field(linea, i+4);
                agregarCancion(nombre, artista, generos, anyoAEntero, lista, listaGlobal);
        }
        k++;
    }

    fclose(archivoCanciones); //Se importan las canciones y se cierra el archivo.
}

void mostrarListasRep(List* listaDeListas){
        listaCanciones* aux = firstList(listaDeListas);
        if(aux == NULL){
                printf("NO HAY LISTAS CREADAS\n");
                return;
        } else{
                while (aux != NULL)
                {
                   if (aux->cantidad == 1)
                        printf("La lista denominada %s contiene 1 cancion\n", aux->nombre);
                   else
                        printf("La lista denominada %s contiene %i canciones\n", aux->nombre, aux->cantidad);
                   aux = nextList(listaDeListas);
                }
        }
}

void eliminar_cancion(char* nombre, char* artista, int anyo)
{
   listaCanciones* listaDeReproduccion = firstList(listaDeListas);
     while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción
                tipoCancion* cancion = firstList(listaDeReproduccion->canciones);
                while (cancion != NULL)
                {
                        if (strcmp(cancion->artista, artista) == 0 && strcmp(cancion->nombreC, nombre) == 0 && cancion->year == anyo)
                        {
                              popCurrent(listaDeReproduccion->canciones);
                              printf("Cancion eliminada correctamente\n");
                              return;
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
                }
                listaDeReproduccion = nextList(listaDeListas);
        }
    printf("No existe ninguna cancion que coincida con los datos ingresados.\n");
}


void main()
{
    List* listaGlobal = createList();
    char* nombre = (char*) malloc (100*sizeof(char)); 
    char* artista = (char*) malloc (100*sizeof(char));
    char* Lista_reproduccion = (char*) malloc (100*sizeof(char));
    char* generos = (char*) malloc (100*sizeof(char)); //aca no debería ser char* ?
    int anyo;
    tipoCancion* datos;
    FILE* archivoCanciones;
    int option;
    char archivo[101];
    bool existe_cancion;

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
                    importarCanciones(archivo, listaGlobal);
                    break;
            case 2: printf("\nIngrese el nombre del archivo que desea crear (o sobreescribir): ");
                    scanf("%s", &archivo);
                    exportarCanciones(archivo);
                    break;
            case 3: printf("Ingrese el nombre de la cancion: ");
                    getchar();
                    scanf("%100[^\n]s", nombre);
                    getchar();
                    printf("Ingrese el artista de la cancion: ");
                    scanf("%100[^\n]s", artista); 
                    getchar();
                    printf("Ingrese el genero de la cancion: "); 
                    scanf("%100[^\n]s", generos);
                    getchar();
                    printf("Ingrese el año de la cancion: ");
                    scanf("%d", &anyo);
                    getchar();
                    printf("Ingrese la lista de reproduccion en donde quiere agregar la cancion: ");
                    scanf("%100[^\n]s", Lista_reproduccion);
                    getchar();
                    agregarCancion(nombre, artista, generos, anyo, Lista_reproduccion, listaGlobal);
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
            case 7: printf("Ingrese el nombre de la canción a eliminar\n");
                    getchar();
                    scanf("%[^\n]s", nombre);
                    getchar();
                    printf("Ingrese el/la artista de la cancion: ");
                    scanf("%[^\n]s", artista); 
                    getchar();
                    printf("Ingrese el año de la cancion: ");
                    scanf("%d", &anyo);
                    getchar();
                    eliminar_cancion(nombre, artista, anyo);
                    break;
            case 8: mostrarListasRep(listaDeListas);
                    break;
            case 9: printf("FUNCION NO IMPLEMENTADA\n");
                    break;
            case 10: printf("FUNCION NO IMPLEMENTADA\n");
                     break;
            case 0: break;
        }
        printf("\n");
    }
    return;
}