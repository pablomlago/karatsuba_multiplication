#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vectordinamico.h"

typedef struct
{
    short signo;
    vectorP cifras;
} STENTEIROLARGO;

typedef STENTEIROLARGO* enteiroP;

void eliminar(enteiroP* enteiro)
{
    if(*enteiro != NULL)
    {
        liberar(&((*enteiro)->cifras));
        free(*enteiro);
        *enteiro = NULL;
    }
}

void crearEnteiro(enteiroP* novoEnteiro, short tamano)
{
    short i = 0;
    
    *novoEnteiro = (enteiroP)malloc(sizeof(STENTEIROLARGO));
    if((*novoEnteiro) != NULL)
    {
        crear(&((*novoEnteiro)->cifras), tamano);
        if((*novoEnteiro)->cifras != NULL)
        {
            for(i = 0; i < tamano; i++)
            {
                asignar(&((*novoEnteiro)->cifras),i,0);
            }
        }
        else
        {
            eliminar(novoEnteiro);
            *novoEnteiro = NULL;
            
            printf("Non foi posible crear o enteiro largo!\n");
        }

    }
    else
    {
        printf("Non foi posible crear o enteiro largo!\n");
    }
}

void asignarEnteiro(enteiroP* enteiro, short posicion, TELEMENTO valor)
{
    asignar(&((*enteiro)->cifras), posicion, valor);
}

void asignarSigno(enteiroP* enteiro, short signo)
{
    if((signo == 1) || (signo == -1))
    {
        (*enteiro)->signo = signo;
    }
    else
    {
        printf("Non se pasou un signo válido!\n");
    }
}

short signoEnteiro(enteiroP enteiro)
{
    return enteiro->signo;
}

short tamanoEnteiro(enteiroP enteiro)
{
    return tamano(enteiro->cifras);
}

TELEMENTO recuperarEnteiro(enteiroP enteiro, short posicion)
{
    return recuperar(enteiro->cifras, posicion);
}

void imprimirEnteiro(enteiroP enteiro)
{
    short i = 0;
    if(signoEnteiro(enteiro) == -1)
    {
        printf("-");
    }
    else
    {
        printf("+");
    }
    for(i = 0; i < tamanoEnteiro(enteiro); i++)
    {
        printf("%d",recuperarEnteiro(enteiro,i));
    }
    printf("\n");
}

void inicializarEnteiro(enteiroP* enteiro, char* numero, short tamanoEnteiro)
{
    short i = 0, j = 0;
    short tam = 0;
    short signo = 0;
    while(numero[i] != '\0')
    {
        i++;
    }
    if(numero[0] == '-')
    {
        signo = -1;
        i--;
    }
    else if(numero[0] == '+')
    {
        signo = 1;
        i--;
    }
    else
    {
        signo = 1;
    }
    tam = i;
    crearEnteiro(enteiro,tamanoEnteiro);
    if((*enteiro) != NULL)
    {
        asignarSigno(enteiro,signo);
        for(i = (tamanoEnteiro-tam),j=1; i < tamanoEnteiro; i++, j++)
        {
            //Pasamos do caracter ao numero
            asignarEnteiro(enteiro,i,numero[j]-48);
        }
    }
    else
    {
        printf("Non se logrou inicializar o enteiro largo!\n");
    }
}

void dividirAMetade(enteiroP* novoEnteiro, enteiroP enteiro, int metade)
{
    short tamano = tamanoEnteiro(enteiro)/2;
    short i = 0, j = 0;
    TELEMENTO temp = 0;
    crearEnteiro(novoEnteiro, tamano);
    if((*novoEnteiro) != NULL)
    {
        asignarSigno(novoEnteiro,signoEnteiro(enteiro));
        if(metade == 1)
        {
            j = tamano;
        }
        for(i = 0; i < tamano; i++, j++)
        {
            temp = recuperarEnteiro(enteiro,j);
            asignarEnteiro(novoEnteiro,i,temp);
        }
    }
}

int compararEnteiros(enteiroP enteiro1,enteiroP enteiro2)
{
    short i = 0;
    short resultado = 0;
    while(i < tamanoEnteiro(enteiro1) && (recuperarEnteiro(enteiro1,i) == recuperarEnteiro(enteiro2,i)))
    {
        i++;
    }
    if(recuperarEnteiro(enteiro1,i) < recuperarEnteiro(enteiro2,i))
    {
        resultado = 1;
    }
    else
    {
        resultado = 0;
    }
    
    return resultado;
}

void OperarKaratsuba(enteiroP* resultado, enteiroP enteiro1, enteiroP enteiro2)
{
    short i = 0;
    TELEMENTO resultadoParcial = 0, acarreo = 0;
    short signoParcial = 0;
    enteiroP temp = NULL;
    
    signoParcial = signoEnteiro(enteiro1)*signoEnteiro(enteiro2);
    
    if(compararEnteiros(enteiro1,enteiro2) == 1)
    {
        temp = enteiro1;
        enteiro1 = enteiro2;
        enteiro2 = temp;
    }
    asignarSigno(resultado,signoEnteiro(enteiro1));
    
    for(i = tamanoEnteiro(enteiro1)-1; i >= 0; i--)
    {
        resultadoParcial = recuperarEnteiro(enteiro1,i)+signoParcial*recuperarEnteiro(enteiro2,i)+acarreo;
        if(resultadoParcial < 0)
        {
            resultadoParcial += 10;
            acarreo = -1;
            
        }
        else if(resultadoParcial < 10)
        {
            acarreo = 0;
        }
        else
        {
            acarreo = resultadoParcial / 10;
            resultadoParcial %= 10;
        }
        
        
        asignarEnteiro(resultado,i,resultadoParcial);
    }
}

void multiplicarPorBase(enteiroP* enteiro, short novoTamano, short adiantar)
{
    enteiroP temp = NULL;
    short i = 0, j = 0;
    
    crearEnteiro(&temp,novoTamano);
    
    if(temp != NULL)
    {
        asignarSigno(&temp,signoEnteiro(*enteiro));
        for(i = adiantar, j = 0; j < tamanoEnteiro(*enteiro); j++, i++)
        {
            asignarEnteiro(&temp,i,recuperarEnteiro(*enteiro,j));
        }
    }
    eliminar(enteiro);
    *enteiro = temp;
}

void duplicarEnteiro(enteiroP* duplicado, enteiroP enteiro)
{
    short i = 0;
    crearEnteiro(duplicado,tamanoEnteiro(enteiro));
    if(*duplicado != NULL)
    {
        asignarSigno(duplicado,signoEnteiro(enteiro));
        for(i = 0; i < tamanoEnteiro(enteiro); i++)
        {
            asignarEnteiro(duplicado,i,recuperarEnteiro(enteiro,i));
        }
    }
}

enteiroP multiplicacionDivideVenceras(enteiroP enteiro1, enteiroP enteiro2)
{
    enteiroP produtoParcial = NULL;
    
    enteiroP a = NULL, b = NULL, c = NULL, d = NULL;
    enteiroP ac = NULL, ad = NULL, bc = NULL, bd = NULL;
    
    TELEMENTO temp;
    
    if(tamanoEnteiro(enteiro1) == 1)
    {
        crearEnteiro(&produtoParcial,2);
        if(produtoParcial != NULL)
        {
            asignarSigno(&produtoParcial,signoEnteiro(enteiro1)*signoEnteiro(enteiro2));
            temp = recuperarEnteiro(enteiro1,0)*recuperarEnteiro(enteiro2,0);
            asignarEnteiro(&produtoParcial,1,temp%10);
            temp /= 10;
            asignarEnteiro(&produtoParcial,0,temp);
        }
        else
        {
            printf("Non foi posible crear o enteiro largo!\n");
        }
    }
    else
    {
        crearEnteiro(&produtoParcial,tamanoEnteiro(enteiro1)*2);
        if(produtoParcial != NULL)
        {
            dividirAMetade(&a,enteiro1,-1);
            dividirAMetade(&b,enteiro1,1);
            dividirAMetade(&c,enteiro2,-1);
            dividirAMetade(&d,enteiro2,1);

            if((a != NULL) && (b != NULL) && (c != NULL) && (d != NULL))
            {
                ac = multiplicacionDivideVenceras(a,c);
                ad = multiplicacionDivideVenceras(a,d);
                bc = multiplicacionDivideVenceras(b,c);
                bd = multiplicacionDivideVenceras(b,d);

                eliminar(&a);
                eliminar(&b);
                eliminar(&c);
                eliminar(&d);
                
                if((ac != NULL) && (ad != NULL) && (bc != NULL) && (bd != NULL))
                {
                    multiplicarPorBase(&ac,tamanoEnteiro(enteiro1)*2,0);
                    multiplicarPorBase(&ad,tamanoEnteiro(enteiro1)*2,tamanoEnteiro(enteiro1)/2);
                    multiplicarPorBase(&bc,tamanoEnteiro(enteiro1)*2,tamanoEnteiro(enteiro1)/2);
                    multiplicarPorBase(&bd,tamanoEnteiro(enteiro1)*2,tamanoEnteiro(enteiro1));

                    if((ac != NULL) && (ad != NULL) && (bc != NULL) && (bd != NULL))
                    {
                        OperarKaratsuba(&produtoParcial, ac, ad);
                        eliminar(&ac);
                        eliminar(&ad);
                        
                        OperarKaratsuba(&produtoParcial, produtoParcial, bc);
                        eliminar(&bc);
                        
                        OperarKaratsuba(&produtoParcial, produtoParcial, bd);
                        eliminar(&bd);
                    }
                    else
                    {
                        eliminar(&ac);
                        eliminar(&ad);
                        eliminar(&bc);
                        eliminar(&bd);
                        
                        eliminar(&produtoParcial);
                        
                        printf("Non se logrou realizar o posicionamento dos sumandos!\n");
                    }
                }
                else
                {
                    eliminar(&ac);
                    eliminar(&ad);
                    eliminar(&bc);
                    eliminar(&bd);
                    
                    eliminar(&produtoParcial);
                    
                    printf("Non se lograron calcular os produtos parciales!\n");
                }
            }
            else
            {
                eliminar(&a);
                eliminar(&b);
                eliminar(&c);
                eliminar(&d);
                
                eliminar(&produtoParcial);
                
                printf("A descomposición do problema fallou!\n");
            }
        }
        else
        {
            printf("Non foi posible crear o enteiro largo!\n");
        }
    }
    
    return produtoParcial;
}

enteiroP multiplicacionKaratsuba(enteiroP enteiro1, enteiroP enteiro2)
{
    enteiroP produtoParcial;
    enteiroP a, b, c, d;
    enteiroP ac, a_b, d_c, bd, abdc;
    enteiroP tac, tbd;
    TELEMENTO temp;
    if(tamanoEnteiro(enteiro1) == 1)
    {
        crearEnteiro(&produtoParcial,2);
        if(produtoParcial != NULL)
        {
            asignarSigno(&produtoParcial,signoEnteiro(enteiro1)*signoEnteiro(enteiro2));
            temp = recuperarEnteiro(enteiro1,0)*recuperarEnteiro(enteiro2,0);
            asignarEnteiro(&produtoParcial,1,temp%10);
            temp /= 10;
            asignarEnteiro(&produtoParcial,0,temp);
        }
        else
        {
            printf("Non foi posible crear o enteiro largo!\n");
        }
    }
    else
    {
        crearEnteiro(&produtoParcial,tamanoEnteiro(enteiro1)*2);
        if(produtoParcial != NULL)
        {
            dividirAMetade(&a,enteiro1,-1);
            dividirAMetade(&b,enteiro1,1);
            dividirAMetade(&c,enteiro2,-1);
            dividirAMetade(&d,enteiro2,1);

            if((a != NULL) && (b != NULL) && (c != NULL) && (d != NULL))
            {
                ac = multiplicacionKaratsuba(a,c);
                bd = multiplicacionKaratsuba(b,d);

                crearEnteiro(&a_b,tamanoEnteiro(a));
                crearEnteiro(&d_c,tamanoEnteiro(d));

                if((ac != NULL) && (bd != NULL) && (a_b != NULL) && (d_c != NULL))
                {
                    asignarSigno(&b,-1*signoEnteiro(b));
                    asignarSigno(&c,-1*signoEnteiro(c));

                    OperarKaratsuba(&a_b,a,b);
                    OperarKaratsuba(&d_c,d,c);

                    abdc = multiplicacionKaratsuba(a_b,d_c);
                    
                    if(abdc != NULL)
                    {
                        eliminar(&a);
                        eliminar(&b);
                        eliminar(&c);
                        eliminar(&d);
                        eliminar(&a_b);
                        eliminar(&d_c);

                        duplicarEnteiro(&tac,ac);
                        duplicarEnteiro(&tbd,bd);

                        if((tac != NULL) && (tbd != NULL))
                        {
                            multiplicarPorBase(&ac,tamanoEnteiro(enteiro1)*2,0);
                            multiplicarPorBase(&bd,tamanoEnteiro(enteiro1)*2,tamanoEnteiro(enteiro1));

                            multiplicarPorBase(&tac,tamanoEnteiro(enteiro1)*2,tamanoEnteiro(enteiro1)/2);
                            multiplicarPorBase(&tbd,tamanoEnteiro(enteiro1)*2,tamanoEnteiro(enteiro1)/2);

                            multiplicarPorBase(&abdc,tamanoEnteiro(enteiro1)*2,tamanoEnteiro(enteiro1)/2);

                            if((tac != NULL) && (tbd != NULL) && (ac != NULL) && (bd != NULL) && (abdc != NULL))
                            {
                                OperarKaratsuba(&produtoParcial, ac, bd);
                                OperarKaratsuba(&produtoParcial, produtoParcial, tac);
                                OperarKaratsuba(&produtoParcial, produtoParcial, tbd);
                                OperarKaratsuba(&produtoParcial, produtoParcial, abdc);

                                eliminar(&ac);
                                eliminar(&bd);
                                eliminar(&abdc);

                                eliminar(&tac);
                                eliminar(&tbd);
                            }
                            else
                            {

                                eliminar(&ac);
                                eliminar(&bd);
                                eliminar(&abdc);

                                eliminar(&tac);
                                eliminar(&tbd);
                                
                                eliminar(&produtoParcial);
                                
                                printf("Non se logrou realizar o posicionamento dos sumandos!\n");
                            }
                        }
                        else
                        {
                            eliminar(&ac);
                            eliminar(&bd);
                            eliminar(&abdc);

                            eliminar(&tac);
                            eliminar(&tbd);
                            
                            eliminar(&produtoParcial);

                            printf("Non se logrou realizar os duplicados dos sumandos!\n");
                        }
                    }
                    else
                    {
                        eliminar(&a);
                        eliminar(&b);
                        eliminar(&c);
                        eliminar(&d);

                        eliminar(&a_b);
                        eliminar(&d_c);

                        eliminar(&ac);
                        eliminar(&bd);
                        
                        eliminar(&produtoParcial);
                        
                        printf("Non se lograron calcular os produtos parciales!\n");
                    }
                }
                else
                {
                    eliminar(&a);
                    eliminar(&b);
                    eliminar(&c);
                    eliminar(&d);
                    
                    eliminar(&a_b);
                    eliminar(&d_c);
                    
                    eliminar(&ac);
                    eliminar(&bd);
                    
                    eliminar(&produtoParcial);
                    
                    printf("Non se lograron calcular os produtos parciales!\n");
                }
            }
            else
            {
                eliminar(&a);
                eliminar(&b);
                eliminar(&c);
                eliminar(&d);
                
                eliminar(&produtoParcial);
                
                printf("A descomposición do problema fallou!\n");
            }
        }
        else
        {
            printf("Non foi posible crear o enteiro largo!\n");
        }
    }
    
    return produtoParcial;
}



