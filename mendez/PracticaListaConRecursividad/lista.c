#include "lista.h"
#include <stdlib.h>

struct lista {
  void* vector;
  int tamanio
};

 lista_t* lista_crear(){
   return calloc(1, sizeof(lista_t));//si falla retorna null y sino inicializa todo en 0
}

lista_t* lista_insertar(lista_t* lista, void* elemento) {
  void* vector_nuevo = realloc(lista->vector, (lista->tamanio+1)*sizeof(void*));
  if(vector_nuevo == NULL)
    return NULL;
  lista->vector = vector_nuevo;
  lista->vector[lista->tamanio] = elemento;
  lista-> tamanio++;
  return lista;
}

void* lista_obtener(lista_t* lista, int posicion) {

  return NULL;
}

int lista_tamanio(lista_t* lista) {

  return 0;
}

void lista_destruir(lista_t* lista) {
  free(lista);
}
