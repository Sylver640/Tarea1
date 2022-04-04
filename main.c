#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"

//Crear lista de listas, global para que sea fácil de acceder desde distintas funciones (base de datos)
List* listaDeListas = NULL;

//Struct que guarda los datos de cada canción.
typedef struct{
    char nombreC[50];
    int year;
    char artista[30];
    char **generos; 
    int cantidadGeneros;
    char Lista_reproduccion[50];
} tipoCancion;

//Struct que guarda todos los datos necesarios para trabajar con una lista.
typedef struct{
    int cantidad;
    List* canciones;
    char nombre[30];
} listaCanciones;

//Función que recibe campos de un archivo CSV separado por comas.
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

void exportarCanciones (char* nombre_archivo, List *listaGlobal)
{
        //Se abre, o crea si no existe, el archivo con el nombre indicado por el usuario
        FILE *archivoCanciones = fopen(nombre_archivo, "wt");
        if (archivoCanciones == NULL)
        {
                //no pudimos abrir/crear el archivo
                return;
        }
        tipoCancion* cancion2Archivo = firstList(listaGlobal); //Para recorrer la lista global
        while (cancion2Archivo != NULL)
        {
                //Con diferentes comandos, como fputs y fputc, se escribe directamente en el archivo
                fputs(cancion2Archivo->nombreC, archivoCanciones);
                fputc(',', archivoCanciones);
                fputs(cancion2Archivo->artista, archivoCanciones);
                fputc(',', archivoCanciones);
                if (cancion2Archivo->cantidadGeneros > 1) //si es más de un género, se va a un ciclo para escribirlos uno por uno con el formato habitual.
                {
                        fputc('"', archivoCanciones);
                        fputs(cancion2Archivo->generos[0], archivoCanciones);
                        for (int i = 1; i < cancion2Archivo->cantidadGeneros; i++)
                        {
                                fputc(',', archivoCanciones);
                                fputc(' ', archivoCanciones);
                                fputs(cancion2Archivo->generos[i], archivoCanciones);
                        }
                        fputc('"', archivoCanciones);
                }
                else
                        fputs(cancion2Archivo->generos[0], archivoCanciones); //En cambio, solo se imprime sin comillas ni comas extras.
                fputc(',', archivoCanciones);       
                fprintf(archivoCanciones, "%d", cancion2Archivo->year);
                fputc(',', archivoCanciones);
                fputs(cancion2Archivo->Lista_reproduccion, archivoCanciones);
                fputc('\n', archivoCanciones);
                cancion2Archivo = nextList(listaGlobal);
                if (!cancion2Archivo)
                        break;    
        }
        fclose(archivoCanciones);
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
                                printf("Generos: ");
                                for (int i = 0; i < cancion->cantidadGeneros; i++)
                                {
                                        printf("%s ", cancion->generos[i]);
                                }
                                printf("\n");
                                printf("Año: %i\n", cancion->year);
                                printf("Lista de reproduccion: %s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
                }
                //Si no se encuentra en una lista, avanza a la otra.
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
                                printf("Generos: ");
                                for (int i = 0; i < cancion->cantidadGeneros; i++)
                                {
                                        printf("%s ", cancion->generos[i]);
                                }
                                printf("\n");
                                printf("Año: %i\n", cancion->year);
                                printf("Lista de reproduccion: %s\n", cancion->Lista_reproduccion);
                                encontrado = true;
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
                }
                //Si no se encuentra en una lista, avanza a la otra.
                listaDeReproduccion = nextList(listaDeListas);
        }
        if (encontrado == false)
        {
                printf("No se ha encontrado ninguna canción con el artista ingresado.");
        }
}

void buscarCancionGenero (char* generoABuscar)
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
                        for (int i = 0; i < cancion->cantidadGeneros; i++) //según la cantidad de géneros, se va buscando por cada canción
                        {
                                if (strcmp(cancion->generos[i], generoABuscar) == 0) //si se encuentra exactamente un género, se entra a este if
                                {
                                        //se encontró una canción con ese genero
                                        printf("Nombre: %s\n", cancion->nombreC);
                                        printf("Artista: %s\n", cancion->artista);
                                        printf("Generos: ");
                                        for (int i = 0; i < cancion->cantidadGeneros; i++)
                                        {
                                                printf("%s ", cancion->generos[i]);
                                        }
                                        printf("\n");
                                        printf("Año: %i\n", cancion->year);
                                        printf("Lista de reproduccion: %s\n", cancion->Lista_reproduccion);
                                        encontrado = true;
                                }
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
                }
                //Si no se encuentra en una lista, avanza a la otra.
                listaDeReproduccion = nextList(listaDeListas);
        }
        if (encontrado == false)
        {
                printf("No se ha encontrado ninguna canción con el genero ingresado.");
        }
}

void agregarCancion (char *nombre, char *artista, char **generos, int anyo, char *Lista_reproduccion, List* listaGlobal, int cantidadGeneros) 
{
        //inicializar la lista de listas si no se ha ocupado antes
        if (listaDeListas == NULL)
        {
                listaDeListas = createList();
        }

        listaCanciones* listaDeReproduccion;
        tipoCancion* cancionAgregada = (tipoCancion*)malloc(sizeof(tipoCancion));
        tipoCancion* cancionAuxiliar; //esta variable nos servirá para comprobar los datos

        //Se copian todos los datos dados por el usuario a canciónAgregada
        strcpy(cancionAgregada->nombreC, nombre);
        strcpy(cancionAgregada->artista, artista);
        //Se reserva memoria para la variable generos
        cancionAgregada->generos = (char**) malloc (cantidadGeneros * sizeof(char*));
        for (int i = 0; i < cantidadGeneros; i++)
        {
                cancionAgregada->generos[i] = (char *) malloc (100*sizeof(char));
                strcpy(cancionAgregada->generos[i], generos[i]); //se copia cada genero indicado por el usuario en el main
        }
        cancionAgregada->cantidadGeneros = cantidadGeneros;
        cancionAgregada->year = anyo;
        strcpy(cancionAgregada->Lista_reproduccion, Lista_reproduccion);
        
        //Para comenzar a buscar, nos ubicamos al inicio de la lista de listas.
        listaDeReproduccion = firstList(listaDeListas);
        
        while (listaDeReproduccion != NULL)
        {
                if (strcmp(listaDeReproduccion->nombre, Lista_reproduccion) == 0)
                {
                        break; //al ver que los nombres son iguales, encontramos que la lista ya existe y termina el while
                }
                else
                {
                        listaDeReproduccion = nextList(listaDeListas); //si no, se pasa a la siguiente posición
                }
        }

        //si la lista no existe, se crea
        if (listaDeReproduccion == NULL)
        {
                listaDeReproduccion = (listaCanciones*) malloc(sizeof(listaCanciones));
                strcpy(listaDeReproduccion->nombre, Lista_reproduccion);
                listaDeReproduccion->cantidad = 0; //como no tiene canciones, se inicializa su cantidad en 0.
                listaDeReproduccion->canciones = createList();
                pushBack(listaDeListas, listaDeReproduccion); //la lista se agrega a la lista de listas.
        }

        //Si la lista no contiene ninguna canción, se agrega al principio de ésta y retorna.
        if (!firstList(listaDeReproduccion->canciones))
        {
                pushFront(listaDeReproduccion->canciones, cancionAgregada);
                printf("Su cancion fue agregada.\n");
                listaDeReproduccion->cantidad++;
                pushBack(listaGlobal, cancionAgregada);
                return;
        }
        else
        {
                //La canción auxilar se vuelve en la primera de la lista para empezar a buscar.
                cancionAuxiliar = firstList(listaDeReproduccion->canciones);
                while(cancionAuxiliar != NULL)
                {
                        //Comparación de canciones.
                        if (cancionAuxiliar == cancionAgregada)
                        {
                                //Si la canción ya está en la lista, se retorna al main.
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

char** separarGeneros(char *generos)
{       
        int i = 0;
        const char* limite = ", "; //indica hasta qué parte se debe copiar una parte del string
        char* token; //utilizado por la función strtok, proveída por string.h
        int cantidadGeneros = 1; //inicializada en 1 para facilitar la ejecución
        for (int i = 0; generos[i] != '\0'; i++)
        {
                if (generos[i] == ',')
                        cantidadGeneros++; //solo se aumenta en uno si detecta una coma entre cada género
        }

        //Reserva de memoria del arreglo a retornar con todos los géneros
        char **generosDivididos = (char**) malloc (cantidadGeneros * sizeof(char*));
        //Si solo es un género, solo se copia en un espacio el string entero por cada carácter
        if (cantidadGeneros == 1)
        {
                generosDivididos[0] = (char *) malloc (100*sizeof(char));
                for (int i = 0; generos[i] != '\0'; i++)
                        generosDivididos[0][i] = generos[i];
        }
        else //Si existe más de un género, se entra a esta sección
        {
                token = strtok(generos, limite); //el token se convierte en aquello que se encuentra entre el principio de "generos" y el límite
                while (token != NULL)
                {
                        generosDivididos[i] = (char *) malloc (100*sizeof(char));
                        generosDivididos[i] = token;
                        token = strtok(NULL, limite); //el token ahora pasa a ser la siguiente posición luego de la coma.
                        i++; //se aumenta en una unidad con tal de guardar el siguiente token en la siguiente posición del arreglo
                }
        }

        return generosDivididos;
}

int contarGeneros(char *generos)
{
        //Función simple que solo cuenta los géneros. Reutilizada de la función separarGéneros.
        int cantidadGeneros = 1;
        for (int i = 0; generos[i] != '\0'; i++)
        {
                if (generos[i] == ',')
                        cantidadGeneros++;
        }
        return cantidadGeneros;
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
        //Si no, se le informa al usuario que fue encontrado y abierto con éxito
        printf("\nSu archivo fue abierto correctamente!\n");
    }
    
    //Se inicializan variables a utilizar en la funcion get_csv_field
    char linea[1024];
    int i;
    int k = 0;
    //Para este while, se empieza desde la primera línea del archivo, hasta que llegue al final.
    while (fgets(linea, 1023, archivoCanciones) != NULL)
    {
        for (i = 0; i < 1; i++)
        {
                char *nombre = get_csv_field(linea, i);
                char *artista = get_csv_field(linea, i+1);
                char *generos = get_csv_field(linea, i+2);
                char** generosDivididos = separarGeneros(generos);
                int cantidadGeneros = contarGeneros(generos);
                char *anyo = get_csv_field(linea, i+3);
                int anyoAEntero = atoi(anyo); //como la variable "anyo" devuelve un string, es necesario transformarlo a entero
                                              //debido a la naturaleza de la función agregar.
                char *lista = get_csv_field(linea, i+4);
                agregarCancion(nombre, artista, generosDivididos, anyoAEntero, lista, listaGlobal, cantidadGeneros);
        }
        k++;
    }

    fclose(archivoCanciones); //Se importan las canciones y se cierra el archivo.
}

void mostrarListasRep(List* listaDeListas){
        listaCanciones* aux = firstList(listaDeListas); //Auxiliar que ayuda a recorrer la lista.
        if(aux == NULL){ //Si no existe ninguna lista, se le informa al usuario y finaliza la función.
                printf("NO HAY LISTAS CREADAS\n");
                return;
        } else{
                //En cambio, se recorre la lista de listas para enumerar cada lista de reproducción
                while (aux != NULL)
                {
                   //Según cada situación, se imprimirá un mensaje por cada lista.
                   if (aux->cantidad == 1)
                        printf("La lista denominada %s contiene 1 cancion\n", aux->nombre);
                   if (aux->cantidad <= 0)
                        printf("La lista denominada %s no contiene ninguna cancion\n", aux->nombre);
                   if (aux->cantidad > 1)
                        printf("La lista denominada %s contiene %i canciones\n", aux->nombre, aux->cantidad);
                   aux = nextList(listaDeListas);
                }
        }
}

void eliminar_deListaGlobal(List* listaGlobal, char *nombre,char *artista, int anyo)
{
     tipoCancion* datos_cancion = firstList(listaGlobal);
     while (datos_cancion != NULL) //se recorre la lista global canción por canción.
     {
        if(strcmp(datos_cancion->nombreC, nombre)==0 && (strcmp(datos_cancion->artista, artista) == 0) && datos_cancion->year == anyo)
              popCurrent(listaGlobal); //se elimina si se encuentra la canción.
        datos_cancion=nextList(listaGlobal);
     } 
}

void eliminar_cancion(char* nombre, char* artista, int anyo, List* listaGlobal)
{
     listaCanciones* listaDeReproduccion = firstList(listaDeListas);
     while (listaDeReproduccion != NULL)
        {
                //iterar canción por canción y lista por lista.
                tipoCancion* cancion = firstList(listaDeReproduccion->canciones);
                while (cancion != NULL)
                {
                        //Se ve si son iguales los parámetros de artista, nombre y año.
                        if (strcmp(cancion->artista, artista) == 0 && strcmp(cancion->nombreC, nombre) == 0 && cancion->year == anyo)
                        {
                              eliminar_deListaGlobal(listaGlobal, nombre, artista, anyo); //Función que elimina la canción de la lista global, 
                                                                                          //con tal de que no queden rastros de ésta.
                              popCurrent(listaDeReproduccion->canciones); //Se elimina la canción de la lista.
                              listaDeReproduccion->cantidad--; //La cantidad de canciones disminuye en una unidad.
                              printf("Cancion eliminada correctamente\n");
                              return;
                        }
                        cancion = nextList(listaDeReproduccion->canciones);
                }
                listaDeReproduccion = nextList(listaDeListas);
        }

    printf("No existe ninguna cancion que coincida con los datos ingresados.\n");
}

void mostrarCancionesListaRep(char* Lista_reproduccion)
{
     listaCanciones* aux = firstList(listaDeListas); //Auxiliar para recorrer la lista.
     listaCanciones* listaDeReproduccion = NULL; //Inicializada en NULL para comprobar más tarde la existencia de alguna lista 
                                                 //con el mismo nombre requerido

     //Si ya al empezar a recorrer la lista se ve que no hay ningún primer elemento, se ve que no hay ninguna lista creada.
     if (!firstList(listaDeListas))
     {
             printf("No existen listas!\n");
             return;
     }
     
     
     //En cambio, si ya existen listas, se van comprobando para ver si existe la indicada por el usuario.
     while(aux != NULL) //Se usa el auxiliar para buscar lista por lista
     {
            if (strcmp(aux->nombre, Lista_reproduccion) == 0)
            {
                listaDeReproduccion = aux; //si se encuentra, la variable listaDeReproduccion se transforma en aux.
                break;
            }
            aux = nextList(listaDeListas);
     }
     
     //Esto pasa si se ve que el nombre dado por el usuario no corresponde a ninguna lista.
     if (listaDeReproduccion == NULL)
     {
        printf("La lista ingresada no existe\n");
        return;
     }

     if (!firstList(listaDeReproduccion->canciones))
     {
             printf("Esta lista no contiene canciones!\n");
             return;
     }
     
     //Finalmente, se recorre toda la lista indicada y se imprimen todas sus canciones.
     tipoCancion* datos_cancion = firstList(listaDeReproduccion->canciones);
     while (listaDeReproduccion->canciones != NULL)
     {
        printf("Nombre: %s\n", datos_cancion->nombreC);
        printf("Artista: %s\n", datos_cancion->artista);
        printf("Genero(s): ");
        for (int i = 0; i < datos_cancion->cantidadGeneros; i++)
        {
                printf("%s ", datos_cancion->generos[i]);
        }
        printf("\n");
        printf("Año: %i\n", datos_cancion->year);
        printf("Lista de reproduccion: %s\n", datos_cancion->Lista_reproduccion);
        datos_cancion = nextList(listaDeReproduccion->canciones);
        if (!datos_cancion) //Si se ve que el siguiente dato no existe, simplemente finaliza el ciclo.
                break;
     }
}

void mostrarTodasLasCanciones (List* listaGlobal)
{
     tipoCancion* datos_cancion = firstList(listaGlobal); //variable para recorrer la lista global.
     while (datos_cancion != NULL) //ciclo para imprimir cada canción dentro de esta lista global.
     {
        printf("Nombre: %s\n", datos_cancion->nombreC);
        printf("Artista: %s\n", datos_cancion->artista);
        printf("Genero(s): ");
        for (int i = 0; i < datos_cancion->cantidadGeneros; i++)
        {
                printf("%s ", datos_cancion->generos[i]);
        }
        printf("\n");
        printf("Año: %i\n", datos_cancion->year);
        printf("Lista de reproduccion: %s\n", datos_cancion->Lista_reproduccion);
        datos_cancion = nextList(listaGlobal);
        if (!datos_cancion)
                break;
     }
     
     //Si no hay ninguna canción, se imprime este mensaje en pantalla y finaliza la función.
     if (!firstList(listaGlobal))
     {
             printf("No hay canciones!\n");
     }
}

void main()
{
    //Inicialización de variables
    List* listaGlobal = createList();
    char* nombre = (char*) malloc (100*sizeof(char)); 
    char* artista = (char*) malloc (100*sizeof(char));
    char* Lista_reproduccion = (char*) malloc (100*sizeof(char));
    char** generos = NULL;
    int anyo, cantidadGeneros;
    tipoCancion* datos;
    FILE* archivoCanciones;
    int option;
    char archivo[101];
    char generoABuscar[101];
    
    //Creación de menú
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
                    exportarCanciones(archivo, listaGlobal);
                    break;
            case 3: printf("Ingrese el nombre de la cancion: ");
                    getchar();
                    scanf("%100[^\n]s", nombre);
                    getchar();
                    printf("Ingrese el artista de la cancion: ");
                    scanf("%100[^\n]s", artista); 
                    getchar();
                    printf("Cuantos generos tiene su cancion? : ");
                    scanf("%d", &cantidadGeneros);
                    getchar();
                    generos = (char**) malloc (cantidadGeneros * sizeof(char*)); //se reserva memoria para crear el arreglo
                    for (int i = 0; i < cantidadGeneros; i++)
                    {
                        generos[i] = (char *) malloc (100*sizeof(char)); //reserva de memoria para cada string dinámico dentro del arreglo
                        printf("Ingrese el genero de la cancion: "); 
                        scanf("%100[^\n]s", generos[i]);
                        getchar();
                    }
                    printf("Ingrese el año de la cancion: ");
                    scanf("%d", &anyo);
                    getchar();
                    printf("Ingrese la lista de reproduccion en donde quiere agregar la cancion: ");
                    scanf("%100[^\n]s", Lista_reproduccion);
                    getchar();
                    agregarCancion(nombre, artista, generos, anyo, Lista_reproduccion, listaGlobal, cantidadGeneros);
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
                    scanf("%[^\n]s", generoABuscar);
                    getchar();
                    buscarCancionGenero(generoABuscar);
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
                    eliminar_cancion(nombre, artista, anyo, listaGlobal);
                    break;
            case 8: mostrarListasRep(listaDeListas);
                    break;
            case 9: printf("Ingrese el nombre de la lista de reproducción: ");
                    getchar();
                    scanf("%100[^\n]s", Lista_reproduccion);
                    getchar();
                    mostrarCancionesListaRep(Lista_reproduccion);
                    break;
            case 10: mostrarTodasLasCanciones(listaGlobal);
                     break;
            case 0: break;
        }
        printf("\n");
    }
    return;
}