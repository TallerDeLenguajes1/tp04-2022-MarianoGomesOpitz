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
        else
        {
            tareasRealizadas[i] = NULL;
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