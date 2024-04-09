#include "pila.h"
#include <stdlib.h>

#define MAX_NUMEROS 10

struct pila {
  int tope;
  int numeros[MAX_NUMEROS];
};

pila_t* crear() {
  return calloc(1, sizeof(pila_t));
}

int tamanio(pila_t* pila) {
  return pila->tope;
}

void apilar(pila_t* pila, int numero) {
  pila->numeros[pila->tope] = numero;
  pila->tope++;
}

int desapilar(pila_t* pila) {

  if(pila->tope == 0)
    return -1;

  int numero = pila->numeros[pila->tope-1];//caso medio borde , prueba de caja blanca
  pila->tope--;
  return numero;
}

void destruir(pila_t* pila) {
  free(pila);
}
