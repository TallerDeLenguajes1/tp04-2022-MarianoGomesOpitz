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

struct Nodo
{
    Tarea tareas;
    struct Nodo *Next;
} typedef Nodo;

Nodo *crearListaVacia();
void insertarTareas(Nodo *listaDeTareas, int cantidad);
Nodo *crearTarea(Nodo *listaDeTareas, int posicion);
void mostrarTareas(Nodo *listaDeTareas);
void mostrarTareaEspecifica(Tarea tareas);
void estadoTarea(Nodo *pendiente, Nodo *realizada);
void liberarMemoria(Nodo *lista);

int main()
{
    srand(time(NULL));

    Nodo *tareasPendientes, *tareasRealizadas;
    tareasPendientes = crearListaVacia();
    tareasRealizadas = crearListaVacia();

    int cantTareas;
    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &cantTareas);
    fflush(stdin);

    insertarTareas(tareasPendientes, cantTareas);

    printf("\n/----------Listado de tareas pendientes----------/\n");
    mostrarTareas(tareasPendientes);

    estadoTarea(tareasPendientes, tareasRealizadas);

    printf("\n/----------Listado de tareas realizadas----------/\n");
    mostrarTareas(tareasRealizadas);

    printf("\n/----------Listado de tareas que quedaron pendientes----------/\n");
    mostrarTareas(tareasPendientes);

    liberarMemoria(tareasPendientes);
    liberarMemoria(tareasRealizadas);

    getchar();
    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
}

void insertarTareas(Nodo *listaDeTareas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        listaDeTareas = crearTarea(listaDeTareas, i);
    }
}

Nodo *crearTarea(Nodo *listaDeTareas, int posicion)
{
    char *buff;
    buff = (char *)malloc(sizeof(char));
    printf("Ingrese la descripcion de la tarea %d: ", posicion);
    gets(buff);
    int ID = posicion + 1;
    int duracion = (rand() % (100 - 10 + 1)) + 10;
    if (listaDeTareas != NULL)
    {
        Nodo *NodoAux = listaDeTareas;
        while (NodoAux != NULL)
        {
            NodoAux = NodoAux->Next;
        }
        NodoAux = (Nodo *)malloc(sizeof(Nodo));

        NodoAux->tareas.TareaID = ID;

        NodoAux->tareas.Descripcion = (char *)malloc(sizeof(char) * strlen(buff) + 1);
        strcpy(NodoAux->tareas.Descripcion, buff);

        NodoAux->tareas.Duracion = duracion;

        NodoAux->Next = NULL;

        return listaDeTareas;
    }
    else
    {
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
    while (listaDeTareas != NULL)
    {
        mostrarTareaEspecifica(listaDeTareas->tareas);
        listaDeTareas = listaDeTareas->Next;
    }
}

void mostrarTareaEspecifica(Tarea tareas)
{
    printf("\n/=== TAREA %d ===/\n", tareas.TareaID - 1);
    printf("ID de la tarea: %d\n", tareas.TareaID);
    printf("Descripcion de la tarea: %s\n", tareas.Descripcion);
    printf("Duracion de la tarea: %d\n", tareas.Duracion);
}

void estadoTarea(Nodo *pendiente, Nodo *realizada)
{
    while (pendiente != NULL)
    {
        char verif;
        mostrarTareaEspecifica(pendiente->tareas);
        puts("Ha sido realizada esta tarea");
        printf("%cy%c para Si, cualquier caracter para No", 34, 34);
        scanf("%c", &verif);
        fflush(stdin);

        Nodo *anterior;
        if (verif == 'y' || verif == 'Y')
        {
            while (realizada != NULL)
            {
                realizada = realizada->Next;
            }
            anterior = pendiente;
            anterior->Next = pendiente->Next;
            realizada = pendiente;
            realizada->Next = NULL;
        }

        pendiente = pendiente->Next;
    }
}

void liberarMemoria(Nodo *lista)
{
    if (lista != NULL)
    {
        free(lista);
    }
}