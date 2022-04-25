#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID;       // Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

struct Nodo ///////////////////////Nodo con el que se trabajará
{
    Tarea tareas;
    struct Nodo *Next;
} typedef Nodo;

Nodo *crearListaVacia();                                                                         ////////Función para crear una lista vacía
void insertarTareas(Nodo **listaDeTareas, int cantidad);                                         ////////Función para insrtar un nodo creado en una lista ¡¡¡¡PUNTERO DOBLE!!!!
Nodo *crearTarea(Nodo *listaDeTareas, int posicion);                                             ////////Función para crear un nodo
void mostrarTareas(Nodo *listaDeTareas);                                                         ////////Función para mostrar la lista entera
void mostrarTareaEspecifica(Tarea tareas);                                                       ////////Función para mostrar una tarea singular
void consultarEstadoTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas);                    ////////Función para saber si una tarea está pendiente o realizada ¡¡¡¡PUNTERO DOBLE!!!!
Nodo *buscarTareaPorID(Nodo *tareasPendientes, Nodo *tareasRealizadas, int ID);                  ////////Funció para buscar una tarea por ID
Nodo *buscarTareaPorPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, char *palabraClave); ////////Función para buscar una tarea por palabra clave
void liberarMemoria(Nodo *lista);                                                                ////////Función para liberar la memoria de una lista

int main()
{
    srand(time(NULL));

    Nodo *tareasPendientes, *tareasRealizadas; ////Declaro los nodos de tarea pendientes y realizadas
    tareasPendientes = crearListaVacia();      ////Los inicializao en null
    tareasRealizadas = crearListaVacia();

    int cantTareas; ////Pido la cantidad de tareas a trabajar
    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cantTareas);
    fflush(stdin);

    insertarTareas(&tareasPendientes, cantTareas); ////Creo las tareas una por una y las inserto en el nodo de tareas pendientes

    printf("\n/----------Listado de tareas pendientes----------/\n"); ////Muestro las tareas ingresadas
    mostrarTareas(tareasPendientes);

    printf("\n(------ Analizando tareas ------)\n"); ////Analizao si las tareas han sido realizadas o no
    consultarEstadoTareas(&tareasPendientes, &tareasRealizadas);

    printf("\n/----------Listado de tareas realizadas----------/\n"); ////Muestro las tareas realizadas
    mostrarTareas(tareasRealizadas);

    printf("\n/----------Listado de tareas que quedaron pendientes----------/\n"); ////Muestro las tareas que quedaron pendientes
    mostrarTareas(tareasPendientes);

    char buscar;
    puts("\n\nDesea buscar una tarea por ID?"); ////Buscar una tarea espec+ifica por ID
    printf("%cb%c para buscar, cualquier otro caracter para no buscar: ", 34, 34);
    scanf("%c", &buscar);
    fflush(stdin);
    Nodo *nodoTareaBuscadaID = (Nodo *)malloc(sizeof(Nodo)); ////Creo y reservo memoria para el nodo de la tarea de cierto ID
    while (buscar == 'b' || buscar == 'B')
    {

        int IDABuscar;
        printf("\nIngrese el ID a buscar: "); ////Solicito el ID en el que se basará la busqueda
        scanf("%d", &IDABuscar);
        fflush(stdin);

        nodoTareaBuscadaID = buscarTareaPorID(tareasPendientes, tareasRealizadas, IDABuscar);
        ////La función me devuelve el nodo de la tarea si la misma existe, devuelve null si no existe tal tarea

        if (nodoTareaBuscadaID != NULL)
        {
            puts("\nTarea encontrada"); ////La tarea existe y la muestro
            printf("Tarea: %d\n", nodoTareaBuscadaID->tareas.TareaID - 1);
            printf("ID de la tarea: %d\n", nodoTareaBuscadaID->tareas.TareaID);
            printf("Descripcion de la tarea: %s\n", nodoTareaBuscadaID->tareas.Descripcion);
            printf("Duracion de la tarea: %d minutos\n", nodoTareaBuscadaID->tareas.Duracion);
        }
        else
        {
            puts("\nNo existe un tarea con tal ID\n"); ////La tarea no existe
        }

        puts("\nDesea buscar otra tarea por ID?"); ////Pregunto si quiero buscar de nuevo por ID
        printf("%cb%c para buscar, cualquier otro caracter para no buscar: ", 34, 34);
        scanf("%c", &buscar);
        fflush(stdin);
    }
    liberarMemoria(nodoTareaBuscadaID); ////Libero la memoria de la lista de la tarea del ID

    puts("\n\nDesea buscar una tarea por palabra clave?"); ////Lo mismo que lo anterior, pero esta vez por palabra clave
    printf("%cb%c para buscar, cualquier otro caracter para no buscar: ", 34, 34);
    scanf("%c", &buscar);
    fflush(stdin);
    Nodo *nodoTareaBuscadaPalabra = (Nodo *)malloc(sizeof(Nodo));
    while (buscar == 'b' || buscar == 'B')
    {

        char palabraClave[20], *p_palabra;
        printf("\nIngrese la palabra clave a buscar: ");
        gets(palabraClave);
        p_palabra = palabraClave;

        nodoTareaBuscadaPalabra = buscarTareaPorPalabra(tareasPendientes, tareasRealizadas, p_palabra);

        if (nodoTareaBuscadaPalabra != NULL)
        {
            puts("\nTarea encontrada");
            printf("Tarea: %d\n", nodoTareaBuscadaPalabra->tareas.TareaID - 1);
            printf("ID de la tarea: %d\n", nodoTareaBuscadaPalabra->tareas.TareaID);
            printf("Descripcion de la tarea: %s\n", nodoTareaBuscadaPalabra->tareas.Descripcion);
            printf("Duracion de la tarea: %d minutos\n", nodoTareaBuscadaPalabra->tareas.Duracion);
        }
        else
        {
            puts("\nNo existe un tarea que incluya tal palabra\n");
        }

        puts("\nDesea buscar otra tarea por palabra clave?");
        printf("%cb%c para buscar, cualquier otro caracter para no buscar: ", 34, 34);
        scanf("%c", &buscar);
        fflush(stdin);
    }
    liberarMemoria(nodoTareaBuscadaPalabra);

    liberarMemoria(tareasPendientes); ////Libero la memoria de la lista de tareas pendientes y realizadas
    liberarMemoria(tareasRealizadas);

    printf("\n\nIngrese un caracter para finalizar el programa: ");
    getchar(); ////Fin del programa
    return 0;
}

////////////Funciones

Nodo *crearListaVacia()
{
    return NULL; ////Devuelve null, para la creación de una lista vacía
}

void insertarTareas(Nodo **listaDeTareas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        *listaDeTareas = crearTarea(*listaDeTareas, i); ////Inserto cada tarea en la lista
    }
}

Nodo *crearTarea(Nodo *listaDeTareas, int posicion)
{
    char *buff;
    buff = (char *)malloc(sizeof(char) * 50);
    printf("Ingrese la descripcion de la tarea %d: ", posicion);
    gets(buff);
    int ID = posicion + 1;
    int duracion = (rand() % (100 - 10 + 1)) + 10; ////Información que llevará cada tarea
    if (listaDeTareas != NULL)
    {
        ////La lista no está vacía, por lo que creo el nodo en el siguiente item de la lista
        Nodo *NodoAux = listaDeTareas;
        while (NodoAux->Next != NULL)
        {
            NodoAux = NodoAux->Next;
        }
        NodoAux->Next = (Nodo *)malloc(sizeof(Nodo));

        NodoAux->Next->tareas.TareaID = ID;

        NodoAux->Next->tareas.Descripcion = (char *)malloc(sizeof(char) * strlen(buff) + 1);
        strcpy(NodoAux->Next->tareas.Descripcion, buff);

        NodoAux->Next->tareas.Duracion = duracion;

        NodoAux->Next->Next = NULL;

        return listaDeTareas;
    }
    else
    {
        ////La lista está vací, por lo que creo el nodo en el primer item de la lista
        listaDeTareas = (Nodo *)malloc(sizeof(Nodo));

        listaDeTareas->tareas.TareaID = ID;

        listaDeTareas->tareas.Descripcion = (char *)malloc(sizeof(char) * strlen(buff) + 1);
        strcpy(listaDeTareas->tareas.Descripcion, buff);

        listaDeTareas->tareas.Duracion = duracion;

        listaDeTareas->Next = NULL;

        return listaDeTareas;
    }

    free(buff);
}

void mostrarTareas(Nodo *listaDeTareas)
{
    while (listaDeTareas != NULL) ////Muestro toda la lista
    {
        mostrarTareaEspecifica(listaDeTareas->tareas);
        listaDeTareas = listaDeTareas->Next;
    }
}

void mostrarTareaEspecifica(Tarea tareas)
{
    printf("\n/=== TAREA %d ===/\n", tareas.TareaID - 1); ////Muestro una tarea específica
    printf("ID de la tarea: %d\n", tareas.TareaID);
    printf("Descripcion de la tarea: %s\n", tareas.Descripcion);
    printf("Duracion de la tarea: %d\n", tareas.Duracion);
}

void consultarEstadoTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas)
{

    char verif;
    Nodo *tareasPendientesAux = NULL;
    Nodo *puntProxNodoAux = NULL;

    while (*tareasPendientes != NULL)
    {

        puntProxNodoAux = (*tareasPendientes)->Next;

        mostrarTareaEspecifica((*tareasPendientes)->tareas);

        puts("Ha sido realizada la tarea");
        printf("%cy%c para %cSi%c, cualquier otro caracter para %cNo%c", 34, 34, 34, 34, 34, 34);
        scanf("%c", &verif);
        fflush(stdin); ////Pregunto si tal tarea ha sido realizada

        if (verif == 'y' || verif == 'Y')
        {
            ////Si se realizó, muevo la tarea a la lista de tareas realizadas
            (*tareasPendientes)->Next = *tareasRealizadas;
            *tareasRealizadas = *tareasPendientes;
        }
        else
        {
            ////Si no se realizó
            (*tareasPendientes)->Next = tareasPendientesAux;
            tareasPendientesAux = *tareasPendientes;
        }

        *tareasPendientes = puntProxNodoAux;
    }

    *tareasPendientes = tareasPendientesAux;
}

Nodo *buscarTareaPorID(Nodo *tareasPendientes, Nodo *tareasRealizadas, int ID)
{
    while (tareasPendientes != NULL)
    {
        if (tareasPendientes->tareas.TareaID == ID)
        {
            return tareasPendientes;
        }

        tareasPendientes = tareasPendientes->Next;
    }
    while (tareasRealizadas != NULL)
    {
        if (tareasRealizadas->tareas.TareaID == ID)
        {
            return tareasRealizadas;
        }

        tareasRealizadas = tareasRealizadas->Next;
    }
    return NULL;
}

Nodo *buscarTareaPorPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, char *palabraClave)
{
    while (tareasPendientes != NULL)
    {
        if (strstr(tareasPendientes->tareas.Descripcion, palabraClave) != NULL)
        {
            return tareasPendientes;
        }

        tareasPendientes = tareasPendientes->Next;
    }
    while (tareasRealizadas != NULL)
    {
        if (strstr(tareasRealizadas->tareas.Descripcion, palabraClave) != NULL)
        {
            return tareasRealizadas;
        }

        tareasRealizadas = tareasRealizadas->Next;
    }
    return NULL;
}

void liberarMemoria(Nodo *lista)
{
    if (lista != NULL)
    {
        free(lista);
    }
}