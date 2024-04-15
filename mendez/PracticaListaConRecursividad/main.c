#include <stdio.h>
#include "lista.h"

void funcion(void* elemento, int i) {
  printf("Elemento %i: %p\n",i, elemento);
}

int main(int argc, char *argv[]) {

  void *e1=(void*)1, *e2=(void*)2;
  lista_t* lista = lista_crear();
  lista_insertar(lista, e1);
  lista_insertar(lista, e2);

  //esto es O(n²)
  for (int i=0;i<lista_tamanio(lista); i++ ) {
    void* elemento = lista_obtener(lista, i); //O(n)
    printf("Elemento %i: %p\n",i, elemento);
  }
  //hay alguna forma de mejorar esto?

  lista_iterador_t* it;
  //la idea es reducir la complejidad a O(n)
  //iterador externo
  for(it=lista_iterador_crear(lista); lista_iterador_hay_mas_elementos_por_recorrer(it); iterador_siguiente(it)) {
    void* elemento = lista_iterador_obtener_actual(it); //lograr que sea -> O(1)
    printf("Elemento %i: %p\n", i, elemento);

  }
  //la diferencia entre iterador externo y interno , principalmente con los interadores externos, nosotros somos los encargados de hacer la iteracion,
  //iteramos desde afuera, controlamos nostros la iteracion, si hay que corta la iteracion, la cortas
  //en los internos se encarga la lista misma y es con una funcion

  //un ejemplo de como seria con internos es
  lista_con_cada_elemento(lista, funcion);


  lista_destruir(lista);
  return 0;
}
