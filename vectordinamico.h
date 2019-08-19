/*Tipo de datos de los elementos del vector*/
typedef int TELEMENTO;

/*Tipo opaco, los detalles de implementación están ocultos al usuario*/
typedef void* vectorP;

/*Función crear:asigna memoria y devuelve la asignación al
 vector. Recibe v1 por referencia para devolver al programa
 principal la dirección de memoria reservada por este
 procedimiento*/
void crear(vectorP* v1, short tam1);

/*Función asignar: Llena una posición de vector con un valor.
 Recibe una copia de la dirección de memoria reservada para el
 vector v1*/
void asignar(vectorP* v1, short posicion, TELEMENTO valor);

/*Función para liberar a memoria asignada ó vector dinámico*/
void liberar(vectorP* v1);

/*Función que devolverá o valor almacenado nunha posición determinada do vector*/
TELEMENTO recuperar(vectorP v1, short posicion);

/*Función que devolverá o tamaño do vector*/
short tamano(vectorP v1);
