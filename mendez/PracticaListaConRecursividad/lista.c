#include "lista.h"
#include <stdlib.h>

struct lista {
  void** vector;
  int tamanio;
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

void* lista_obtener_recursivo(void** vector, int tamanio,int posicion) {
  if(tamanio == 0)
    return NULL;

  if(posicion == 0)
    return *vector;

  return lista_obtener_recursivo(vector+1,tamanio-1, posicion-1);//hay una foto en esta carpeta con un mini grafico que muestra que es lo que esta pasando y porq los tamanios del vectore se reducen
}

void* lista_obtener(lista_t* lista, int posicion) {
   return lista_obtener_recursivo(lista->vector, lista->tamanio, posicion);
}
//que es un iterador, un interador es una estructura que me permite ami recorrer el TDA(en este caso la lista)
void* lista_obtener_iterativo(lista_t* lista, int posicion) {
  if(posicion > lista->tamanio-1)
    return NULL;
  return lista->vector[posicion];
}


int lista_tamanio(lista_t* lista) {

  return lista->tamanio;
}

void lista_destruir(lista_t* lista) {
  //este es el orden correcto porque si liberamos primero la lista , despues no podemos acceder a esa referencia apuntada
  free(lista->vector);
  free(lista);
}
