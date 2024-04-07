#ifndef PILA_H_
#define PILA_H_

typedef struct pila pila_t;

pila_t* crear();
void apilar(pila_t* pila, int numero);
int desapilar(pila_t* pila);
void destruir(pila_t* pila);



#endif // PILA_H_
