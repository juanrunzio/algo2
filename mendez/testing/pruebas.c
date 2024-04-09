#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#include "pa2m.h"

void alCrearUnaPila_laPilaNoEsNulaYTieneTamanioCero() {
  pila_t* pila = NULL;

  pila = crear();
  pa2m_afirmar(pila != NULL, "La pila se crea correctamente");
  pa2m_afirmar((tamanio(pila)==0), "La pila se crea con tamanio 0");

  /*
  if(pila == NULL) {
    printf("☠ Error, la pila no deberia ser NULL\n");
  } else {
    printf("✅ La pila se puede creear correctamente\n");
  }
  if(tamanio(pila)==0) {
    printf("✅ La pila se crea con tamnio 0\n");
  } else {
    printf("☠ Error, la pila deberia tener tamanio 0\n");
  }
  */
  destruir(pila);
}
void alApilarUnElemento_laPilaCrece() {

  pila_t* pila = NULL;
  int numero = 5;

  pila = crear();

  apilar(pila, numero);

  pa2m_afirmar((tamanio(pila)==1), "Al apilar un elemento , el tamanio de la pila crece");
  /*
  if(tamanio(pila)==1) {
    printf("✅ La pila tiene tamanio 1 luego de apilar un elemento\n");
  } else {
    printf("☠ Error, la pila deberia tener tamanio 1\n");
  }
  */

  destruir(pila);
}
void alDesailarUnElemento_desapiloElUltimoApilado(){
  pila_t* pila = NULL;
  int numero1 = 5;
  int numero2 = 10;
  pila = crear();

  apilar(pila, numero1);
  apilar(pila, numero2);

  pa2m_afirmar(desapilar(pila)==numero2, "Al desapilar un elemento , desapilo el ultimo apilado");

  destruir(pila);

}

void alDesailarDeUnaPilaVacia_desapiloUnMenosUno(){
  pila_t* pila = NULL;
  pila = crear();

  pa2m_afirmar(desapilar(pila)==-1, "Al desapilar un elemento de una pila vacia, obtengo -1");
  pa2m_afirmar(tamanio(pila)==0, "Al desapilar de una pila vacia, el tamanio queda en 0");

  destruir(pila);

}


int main() {
  pa2m_nuevo_grupo("Pruebas de creacion e inicializacion");
  alCrearUnaPila_laPilaNoEsNulaYTieneTamanioCero();

  pa2m_nuevo_grupo("Pruebas de apilar y desapilar");
  alApilarUnElemento_laPilaCrece();
  alDesailarUnElemento_desapiloElUltimoApilado();
  alDesailarDeUnaPilaVacia_desapiloUnMenosUno();

  return pa2m_mostrar_reporte();
}
