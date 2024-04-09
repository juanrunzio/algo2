#ifndef PILA_H_
#define PILA_H_
//el .h es un archivo de contrato, define lo que vamos a hacer
//pero no define el ¿como?
//es el ¿que? NO el ¿como?
typedef struct pila pila_t;

pila_t* crear();
int tamanio(pila_t* pila);
void apilar(pila_t* pila, int numero);
int desapilar(pila_t* pila);
void destruir(pila_t* pila);



#endif // PILA_H_
