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
void insertarTareas(Nodo **listaDeTareas, int cantidad);
Nodo *crearTarea(Nodo *listaDeTareas, int posicion);
void mostrarTareas(Nodo *listaDeTareas);
void mostrarTareaEspecifica(Tarea tareas);
void consultarEstadoTareas(Nodo **listaTareasPendientes, Nodo **listaTareasRealizadas);
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

    insertarTareas(&tareasPendientes, cantTareas);

    printf("\n/----------Listado de tareas pendientes----------/\n");
    mostrarTareas(tareasPendientes);

    consultarEstadoTareas(&tareasPendientes, &tareasRealizadas);

    printf("\n/----------Listado de tareas realizadas----------/\n");
    mostrarTareas(tareasRealizadas);

    printf("\n/----------Listado de tareas que quedaron pendientes----------/\n");
    mostrarTareas(tareasPendientes);

    liberarMemoria(tareasPendientes);
    liberarMemoria(tareasRealizadas);

    printf("Ingrese un caracter para finalizar el programa: ");
    getchar();
    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
}

void insertarTareas(Nodo **listaDeTareas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        *listaDeTareas = crearTarea(*listaDeTareas, i);
    }
}

Nodo *crearTarea(Nodo *listaDeTareas, int posicion)
{
    char *buff;
    buff = (char *)malloc(sizeof(char) * 50);
    printf("Ingrese la descripcion de la tarea %d: ", posicion);
    gets(buff);
    int ID = posicion + 1;
    int duracion = (rand() % (100 - 10 + 1)) + 10;
    if (listaDeTareas != NULL)
    {
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

void consultarEstadoTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas)
{

    char verif;
    Nodo *tareasPendientesAux = NULL;
    Nodo *puntProxNodoAux = NULL;

    printf("\n(------ Analizando tareas ------)\n");

    while (*tareasPendientes != NULL)
    {

        puntProxNodoAux = (*tareasPendientes)->Next;

        mostrarTareaEspecifica((*tareasPendientes)->tareas);

        puts("Ha sido realizada la tarea");
        printf("%cy%c para %cSi%c, cualquier otro caracter para %cNo%c", 34, 34, 34, 34, 34, 34);
        scanf("%c", &verif);
        fflush(stdin);

        if (verif == 'y' || verif == 'Y')
        {
            (*tareasPendientes)->Next = *tareasRealizadas;
            *tareasRealizadas = *tareasPendientes;
        }
        else
        {
            (*tareasPendientes)->Next = tareasPendientesAux;
            tareasPendientesAux = *tareasPendientes;
        }

        *tareasPendientes = puntProxNodoAux;
    }

    *tareasPendientes = tareasPendientesAux;
}

void liberarMemoria(Nodo *lista)
{
    if (lista != NULL)
    {
        free(lista);
    }
}