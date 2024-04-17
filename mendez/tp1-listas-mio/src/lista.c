#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
  void *elemento;
  struct nodo *siguiente;
} nodo_t;

struct lista {
  nodo_t *nodo_inicio;
  nodo_t *nodo_fin;
  int longitud;

  // algo mas?
};

struct lista_iterador {
  nodo_t *nodo_actual;

  // y acá?
  int sarasa;
};

lista_t *lista_crear() {
  lista_t *lista = malloc(sizeof(lista_t));
  if (!lista)
    return NULL;
  lista->nodo_inicio = NULL;
  lista->nodo_fin = NULL;
  lista->longitud = 0;

  return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento) {
  nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
  if (nuevo_nodo == NULL)
    return NULL;

  nuevo_nodo->elemento = elemento;
  nuevo_nodo->siguiente = NULL;

  if (lista->nodo_inicio == NULL) {
    lista->nodo_inicio = nuevo_nodo;
  } else {
    nodo_t *nodo_actual = lista->nodo_inicio;
    while (nodo_actual->siguiente != NULL) {
      nodo_actual = nodo_actual->siguiente;
    }

    nodo_actual->siguiente = nuevo_nodo;
  }
  return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
                                    size_t posicion) {
  nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
  if (nuevo_nodo == NULL)
    return NULL;
  nuevo_nodo->elemento = elemento;

  if (posicion == 0 || lista->nodo_inicio == NULL) {
    nuevo_nodo->siguiente = lista->nodo_inicio;
    lista->nodo_inicio = nuevo_nodo;
  } else {
    nodo_t *anterior = lista->nodo_inicio;
    size_t i = 0;
    while (i < posicion - 1 && anterior->siguiente != NULL) {
      anterior = anterior->siguiente;
      i++;
    }
    nuevo_nodo->siguiente = anterior->siguiente;
    anterior->siguiente = nuevo_nodo;
  }
  return lista;
}

void *lista_quitar(lista_t *lista) {
  if (lista->nodo_inicio == NULL)
    return NULL;

  nodo_t *nodo_actual = lista->nodo_inicio;
  nodo_t *nodo_anterior = NULL;

  while (nodo_actual->siguiente != NULL) {
    nodo_anterior = nodo_actual;
    nodo_actual = nodo_actual->siguiente;
  }
  if (nodo_anterior == NULL) {
    lista->nodo_inicio = NULL;
  } else {
    nodo_anterior->siguiente = NULL;
  }

  void *elemento = nodo_actual->elemento;
  free(nodo_actual);

  return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion) {
  if (lista->nodo_inicio == NULL)
    return NULL;

  nodo_t *nodo_actual = lista->nodo_inicio;
  nodo_t *nodo_anterior = NULL;
  size_t i = 0;
  void *elemento = NULL;

  while (i < posicion && nodo_actual->siguiente != NULL) {
    nodo_anterior = nodo_actual;
    nodo_actual = nodo_actual->siguiente;
    i++;
  }

  if (nodo_anterior == NULL) {
    lista->nodo_inicio = nodo_actual->siguiente;
  } else {
    nodo_anterior->siguiente = nodo_actual->siguiente;
  }

  void *elemento_quitado = nodo_actual->elemento;
  free(nodo_actual);

  return elemento_quitado;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion) {
  if (lista->nodo_inicio == NULL)
    return NULL;

  nodo_t *nodo_actual = lista->nodo_inicio;
  size_t i = 0;

  while (i < posicion && nodo_actual->siguiente != NULL) {
    nodo_actual = nodo_actual->siguiente;
    i++;
  }

  if (i != posicion)
    return NULL;

  return nodo_actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
                            void *contexto) {
  if (!lista || lista->longitud == 0 || !comparador)
    return NULL;
  nodo_t *nodo_actual = lista->nodo_inicio;
  while (nodo_actual != NULL) {
    if (comparador(nodo_actual->elemento, contexto) == 0)
      return nodo_actual->elemento;
    nodo_actual = nodo_actual->siguiente;
  }
  return NULL;
}

void *lista_primero(lista_t *lista) {

  if (!lista || lista->longitud == 0)
    return NULL;
  return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista) {
  if (!lista || lista->longitud == 0)
    return NULL;

  return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista) {
  if (!lista)
    return true;
  return lista->longitud == 0;
}

size_t lista_tamanio(lista_t *lista) {
  if (!lista)
    return 0;
  return lista->longitud;
}

void lista_destruir(lista_t *lista) {
  if (!lista)
    return;
  while (lista->nodo_inicio != NULL) {
    nodo_t *nodo_a_eliminar = lista->nodo_inicio;
    lista->nodo_inicio = lista->nodo_inicio->siguiente;
    free(nodo_a_eliminar);
  }
  free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *)) {
  if (!lista)
    return;
  while (lista->nodo_inicio != NULL) {
    nodo_t *nodo_a_eliminar = lista->nodo_inicio;
    lista->nodo_inicio = lista->nodo_inicio->siguiente;
    if (funcion)
      funcion(nodo_a_eliminar->elemento);
    free(nodo_a_eliminar);
  }
  free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista) { return NULL; }

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador) {
  return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador) { return false; }

void *lista_iterador_elemento_actual(lista_iterador_t *iterador) {
  return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador) {}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
                               void *contexto) {
  return 0;
}
