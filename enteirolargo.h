#include "vectordinamico.h"

typedef void* enteiroP;

//Crea un enteiro largo inicializado a 0 do tamaño pasado como parámetro
void crearEnteiro(enteiroP* novoEnteiro, short tamano);

//Libera a memoria asignada a un enteiro largo e asigna o punteiro a NULL
void eliminar(enteiroP* enteiro);

//Permite asignar un signo ao enteiro largo que se lle pasa como parámetro
void asignarSigno(enteiroP* enteiro, short signo);

//Devolve o signo do enteiro largo
short signoEnteiro(enteiroP enteiro);

//Devolve o tamaño do enteiro largo
short tamanoEnteiro(enteiroP enteiro);   

//Imprime en pantalla o enteiro largo pasado como parámetro
void imprimirEnteiro(enteiroP enteiro);

//Realiza a suma ou resta de dous enteiros largos gardando o resultado noutro que se pasa como parámetro
void OperarKaratsuba(enteiroP* resultado, enteiroP enteiro1, enteiroP enteiro2);

//Crea un enteiro largo dun tamaño determinado inicializando con unha cadea de caracteres 
void inicializarEnteiro(enteiroP* enteiro, char* numero, short tamanoEnteiro);

//Realiza a multiplicación de dous enteiros largos polo método de divide e vencerás cuadrático
enteiroP multiplicacionDivideVenceras(enteiroP enteiro1, enteiroP enteiro2);

//Realiza a multiplicación de dous enteiros largos empleando o algoritmo de Karatsuba-Offman    
enteiroP multiplicacionKaratsuba(enteiroP enteiro1, enteiroP enteiro2);