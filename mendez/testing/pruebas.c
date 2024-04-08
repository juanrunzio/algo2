#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

void alCrearUnaPila_laPilaNoEsNula() {
  pila_t* pila = NULL;

  pila = crear();

  if(pila == NULL) {
    printf("Error, la pila no deberia ser NULL");
  } else {
    printf("La pila se puede creear correctamente");
  }
  destruir(pila);
}

int main() {

  alCrearUnaPila_laPilaNoEsNula();

  return 0;
}
