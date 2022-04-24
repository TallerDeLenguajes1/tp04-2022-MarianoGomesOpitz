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

Tarea *BuscarTarea(Tarea **pendietes, Tarea **realizadas, char *palabra, int *estado, int cantidad);

int main()
{
    int min = 10, max = 100;
    srand(time(NULL));

    int cantTareas;
    printf("Ingrese la cantidad de tareas: ");
    scanf("%d", &cantTareas);
    fflush(stdin);

    Tarea **tareasPendientes, **tareasRealizadas;
    tareasPendientes = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);
    tareasRealizadas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);

    for (int i = 0; i < cantTareas; i++)
    {
        tareasPendientes[i] = (Tarea *)malloc(sizeof(Tarea));
        tareasRealizadas[i] = (Tarea *)malloc(sizeof(Tarea));
        tareasRealizadas[i] = NULL;
    }
    char *buffer;
    buffer = (char *)malloc(sizeof(char) * 100);
    puts("\n/----------Carga de tareas----------/\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("\nTarea %d\n", i);

        tareasPendientes[i]->TareaID = i + 1;

        printf("Ingrese la descripcion de la tarea: ");
        gets(buffer);
        tareasPendientes[i]->Descripcion = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(tareasPendientes[i]->Descripcion, buffer);

        tareasPendientes[i]->Duracion = (rand() % (100 - 10 + 1)) + 10;
    }
    free(buffer);

    char verif;
    puts("\n/----------Listado de tareas pendientes----------/\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("\nTarea %d\n", i);
        printf("ID de la tareas: %d\n", tareasPendientes[i]->TareaID);
        printf("Descripcion de la tarea: %s\n", tareasPendientes[i]->Descripcion);
        printf("Duracion de la tarea: %d minutos\n", tareasPendientes[i]->Duracion);

        puts("Esta tarea ha sido realizada?");
        printf("%cy%c para Si, cualquiar caracter para No: ", 34, 34);
        scanf("%c", &verif);
        fflush(stdin);
        if (verif == 'y' || verif == 'Y')
        {
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        }
    }

    puts("\n/----------Listado de tareas realizadas----------/\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasRealizadas[i] != NULL)
        {
            printf("\nTarea %d\n", i);
            printf("ID de la tareas: %d\n", tareasRealizadas[i]->TareaID);
            printf("Descripcion de la tarea: %s\n", tareasRealizadas[i]->Descripcion);
            printf("Duracion de la tarea: %d minutos\n", tareasRealizadas[i]->Duracion);
        }
    }

    puts("\n/----------Listado de tareas que quedaron pendientes----------/\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasPendientes[i] != NULL)
        {
            printf("\nTarea %d\n", i);
            printf("ID de la tareas: %d\n", tareasPendientes[i]->TareaID);
            printf("Descripcion de la tarea: %s\n", tareasPendientes[i]->Descripcion);
            printf("Duracion de la tarea: %d minutos\n", tareasPendientes[i]->Duracion);
        }
    }
    char buscar;
    puts("\n/----------Desea buscar una tarea en especifico?----------/");
    printf("%cb%c para Si, cualquier otro caracter para no: ", 34, 34);
    scanf("%c", &buscar);
    fflush(stdin);
    char palabra[20], *p_palabra;
    Tarea *tareaBuscada;
    while (buscar == 'b' || buscar == 'B')
    {
        int estado = 0;
        printf("\nIngrese la palabra de la tarea a buscar: ");
        gets(palabra);
        p_palabra = palabra;

        tareaBuscada = BuscarTarea(tareasPendientes, tareasRealizadas, p_palabra, &estado, cantTareas);
        printf("Palabra en la que se baso la busqueda: %s\n", palabra);
        printf("ID de la tarea: %d\n", tareaBuscada->TareaID);
        printf("Descripcion de la tarea: %s\n", tareaBuscada->Descripcion);
        printf("Duracion de la tarea: %d minutos\n", tareaBuscada->Duracion);
        printf("Estado de la tarea: \n");
        if (estado != 0)
        {
            printf("Realizada\n");
        }
        else
        {
            printf("Pendiente\n");
        }
        tareaBuscada = NULL;

        puts("\nDesea buscar otra tarea?");
        printf("%cb%c para Si, cualquier otro caracter para no: ", 34, 34);
        scanf("%c", &buscar);
        fflush(stdin);
    }

    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasPendientes[i] != NULL)
        {
            free(tareasPendientes[i]);
        }
        else
        {
            free(tareasRealizadas[i]);
        }
    }
    free(tareasPendientes);
    free(tareasRealizadas);

    puts("\n\nIngrese un caracter para finalizar el programa");
    getchar();
    return 0;
}

Tarea *BuscarTarea(Tarea **pendietes, Tarea **realizadas, char *palabra, int *estado, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (realizadas[i] != NULL)
        {
            if (strstr(realizadas[i]->Descripcion, palabra) != NULL)
            {
                *estado = 1;
                return realizadas[i];
            }
        }
        else
        {
            if (strstr(pendietes[i]->Descripcion, palabra) != NULL)
            {
                return pendietes[i];
            }
        }
    }
}