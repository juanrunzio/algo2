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

void lista_iterar_todos_los_elementos(lista_t* lista, bool(f)(void*, int, void*), void* contexto) {

    bool continuar = true;
    for (int i=0;i<lista_tamanio(lista) && continuar; i++ ) {
    //void* elemento = lista_obtener(lista, i); //O(n)
    void* elemento = lista->vector[i];
    continuar = f(elemento, i, contexto); //con esta funcion , puedo influenciar a los elementos que se estan iterando en el for de arriba
  }

}

void lista_destruir(lista_t* lista) {
  //este es el orden correcto porque si liberamos primero la lista , despues no podemos acceder a esa referencia apuntada
  free(lista->vector);
  free(lista);
}

void lista_destruir_todo(lista_t* lista, void(f)(void*)) {
  for (int i=0;i<lista_tamanio(lista); i++ ) {
    if (f)
      f(lista->vector[i]);
  }
  lista_destruir(lista);
}

struct lista_iterador {
  int i;
  lista_t* lista;
};

lista_iterador_t* lista_iterador_crear(lista_t* lista) {
  lista_iterador_t* it = malloc(sizeof(lista_iterador_t));
  if (it != NULL) {
    it->i = 0;
    it->lista= lista;
  }
  return it;

}
bool lista_iterador_hay_mas_elementos_por_recorrer(lista_iterador_t* it) {
  return it->i < lista_tamanio(it->lista);
}
void iterador_siguiente_interacion(lista_iterador_t* it) {
  it->i++;
}
void* lista_iterador_devolveme_un_elemento(lista_iterador_t* it) {
  return it->lista->vector[it->i];
}

void lista_iterador_destruir(lista_iterador_t* it) {
  free(it);
}
