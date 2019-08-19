#include <stdio.h>
#include <stdlib.h>

typedef int TELEMENTO;
/*Se vuelve a definir el tipo de datos que contiene el vector*/

typedef struct 
{
    TELEMENTO* datos; /*valores del vector*/
    short tam;        /*tamaño del vector*/
} STVECTOR;           /*definición da estructura*/

typedef STVECTOR* vectorP; /*puntero a estructura*/

/*Función crear: asigna memoria y devuelve la asignación al
 vector*/

void crear(vectorP* v1, short tam1)
{
    short i = 0;
    *v1 = (vectorP)malloc(sizeof(STVECTOR));
    if(*v1 != NULL)
    {
        (*v1)->datos=(TELEMENTO*)malloc(tam1*sizeof(TELEMENTO));
        if((*v1)->datos != NULL)
        {
            (*v1)->tam = tam1;
            for(i = 0; i < tam1; i++)
            {
                *((*v1)->datos + i) = 0; /*Inicialización a 0 de las
                                          * componentes del vector*/
            }
        }
        else
        {
            free(*v1);
            *v1 = NULL;
            printf("Non se puido facer a reserva da memoria!\n");
        }
    }
    else
    {
        printf("Non se puido facer a reserva da memoria!\n");
    }
}

/*Función asignar: Asigna un valor a unha posición do vector*/
void asignar(vectorP* v1, short posicion, TELEMENTO valor)
{
    if(((*v1) != NULL) && ((*v1)->datos != NULL))
    {
        if((posicion < 0) || (posicion >= (*v1)->tam))
        {
            printf("Non se introduciu unha posición válida!\n");
        }
        else
        {
            *((*v1)->datos + posicion) = valor;
        }
    }
    else
    {
        printf("O vector non é válido!\n");
    }
}

/*Función para liberar a memoria asignada ó vector dinámico*/
void liberar(vectorP* v1)
{
    if((*v1) != NULL)
    {
        if((*v1)->datos != NULL)
        {
            free((*v1)->datos);
            (*v1)->datos = NULL;
        }
        free(*v1);
        (*v1) = NULL;
    }
    else
    {
        printf("Non se pode eliminar o vector!\n");
    }
}

/*Función que devolverá o valor almacenado nunha posición determinada do vector*/
TELEMENTO recuperar(vectorP v1, short posicion)
{
    TELEMENTO elemento = 0;
    if((v1 != NULL) && (v1->datos != NULL))
    {
        if((posicion >= 0) && (posicion < v1->tam)) //NÚMEROS NEGATIVOS
        {
            elemento = *(v1->datos + posicion);
        }
    }
    else
    {
        printf("O vector non é válido!\n");
    }
    return elemento;
}

/*Función que devolverá o tamaño do vector*/
short tamano(vectorP v1)
{
    short tamano = 0;
    
    if(v1 != NULL)
    {
        tamano = v1->tam;
    }
    else
    {
        printf("O vector non é válido!\n");
    }
    
    return tamano;
}

