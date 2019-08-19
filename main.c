#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "enteirolargo.h"

short tamanoMaiorCadea(char* numero1, char* numero2);

int main(int argc, char** argv) {

    enteiroP enteiro1 = NULL;
    enteiroP enteiro2 = NULL;
    enteiroP enteiro3 = NULL;
    
    clock_t inicio = -1, fin = -1;
    
    short tam = 0;
    if(argc == 4)
    {
        //Devolve o tamaño adecuado para os números a multiplicar
        tam = tamanoMaiorCadea(argv[1],argv[2]);
        
        //Crea e inicializa os factores cos valores pasados por liña de comandos
        inicializarEnteiro(&enteiro1,argv[2], tam);
        inicializarEnteiro(&enteiro2,argv[3], tam);
        
        if((enteiro1 != NULL) && (enteiro2 != NULL))
        {
            //O usuario elixe que método aplicar para realizar a multiplicación
            if(argv[1][0] == 'k')
            {
                printf("Multplicación Karatsuba:\n");
                inicio = clock();
                enteiro3 = multiplicacionKaratsuba(enteiro1, enteiro2);
                fin = clock();
            }
            else if(argv[1][0] == 'd')
            {
                printf("Multplicación Divide e Vencerás:\n");
                inicio = clock();
                enteiro3 = multiplicacionDivideVenceras(enteiro1, enteiro2);
                fin = clock();
            }
            else
            {
                printf("Non se elixiu un método de multiplicación permitido!");
            }
        }
    }
    else
    {
        printf("Non se pasou o número apropiado de parámetros:\n");
        printf("1- Nome do executable, 2- Método de multiplicación (k para karatsuba, d para divide e vencerás), 3,4- Factores,.");
    }
    
    printf("\n");
    if(enteiro1 != NULL)
    {
        printf("Factor 1:\n");
        imprimirEnteiro(enteiro1);
        eliminar(&enteiro1);
    }
    if(enteiro2 != NULL)
    {
        printf("Factor 2:\n");
        imprimirEnteiro(enteiro2);
        eliminar(&enteiro2);
    }
    printf("\n\n");
    if(enteiro3 != NULL)
    {
        printf("Resultado:\n");
        imprimirEnteiro(enteiro3);
        eliminar(&enteiro3);
    }
    printf("\n\n");
    
    //Mostramos o tempo consumido na multplicación
    printf("Inicio:%ld\tFin:%ld\tTempo:%.4lf\n", fin, inicio, (fin-inicio)/(double)CLOCKS_PER_SEC);
    
    return (EXIT_SUCCESS);
}

//Tomamos como tamaño dos números o tamaño da cadea mais larga, tendo en conta o  posible signo
//e axustando o tamaño a potencia de dous máis cercana.
short tamanoMaiorCadea(char* numero1, char* numero2)
{
    short tam1, tam2, tamFinal;
    short i = 0;
    
    while(numero1[i] != '\0')
    {
        i++;
    }
    tam1 = i;
    
    //O signo non se contabiliza no tamaño do enteiro
    if((numero1[0] == '-') || (numero1[0] == '+'))
    {
        tam1--;
    }
    i = 0;
    
    while(numero2[i] != '\0')
    {
        i++;
    }
    tam2 = i;
    
    if((numero2[0] == '-') || (numero2[0] == '+'))
    {
        tam2--;
    }
    
    //Axustamos o tamaño a potencia de dous máis cercana
    if(tam1 < tam2)
    {
        tamFinal = pow(2,ceil(log2((double)tam2)));
    }
    else
    {
        tamFinal = pow(2,ceil(log2((double)tam1)));
    }
    
    return tamFinal;
}
