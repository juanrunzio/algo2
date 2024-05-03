#include "abb.h"
#include <stdio.h>
#include <stdlib.h>

struct abb* abb_crear()
{
  return NULL;
}
struct abb* abb_insertar(struct abb* abb, int n)
{
  if(abb == NULL){
    struct abb* nuevo = calloc(1, sizeof(struct abb));
    nuevo->dato = n;
    return nuevo;
  }
  if(n > abb->dato)
     abb->der = abb_insertar(abb->der, n);
  else abb->izq = abb_insertar(abb->izq, n);

  return abb;
}

bool abb_existe(struct abb* abb, int n)
{
  if(abb == NULL)
    return false;
  if(n == abb->dato)
    return true;
  if(n > abb->dato)
    return abb_existe(abb->der, n);
  return abb_existe(abb->izq, n);

}

void abb_recorrido_inorden(struct abb * abb, void (*f)(int, void*), void* aux)
{
  if(abb == NULL)
    return;

  abb_recorrido_inorden(abb->izq, f, aux);

  f(abb->dato, aux);

  abb_recorrido_inorden(abb->der, f, aux);
}

void abb_recorrido_preorden(struct abb * abb, void (*f)(int, void*), void* aux)
{
  if(abb == NULL)
    return;

  f(abb->dato, aux);

  abb_recorrido_preorden(abb->izq, f, aux);

  abb_recorrido_preorden(abb->der, f, aux);
}

void abb_recorrido_postorden(struct abb * abb, void (*f)(int, void*), void* aux)
{
  if(abb == NULL)
    return;

  abb_recorrido_postorden(abb->izq, f, aux);

  abb_recorrido_postorden(abb->der, f, aux);

  f(abb->dato, aux);
}


void abb_con_cada_elemento(struct abb* abb, enum abb_recorrido recorrido, void (*f)(int, void*), void* aux)
{
  if(f == NULL)
    return;

  if(recorrido == ABB_RECORRIDO_INORDEN)
    abb_recorrido_inorden(abb, f, aux);

  if(recorrido == ABB_RECORRIDO_PREORDEN)
    abb_recorrido_preorden(abb, f, aux);

  return;
}

void abb_destruir(struct abb* abb)
{
  if(abb==NULL)
    return;
  abb_destruir(abb->izq);
  abb_destruir(abb->der);
  free(abb);


}

struct abb *abb_quitar(struct abb *abb, int n)
{
  if(abb==NULL)
    return false;
  if(n == abb->dato){
    //encontre el dato, lo elimino
    if(abb->izq == NULL && abb->der == NULL){
      //es hoja
      free(abb);
      return NULL;
    }
    return abb;
  }
  if(n > abb->dato)
    //aca no encontre el dato entonces tengo que hacer
    abb->der = abb_quitar(abb->der, n);
  abb->izq = abb_quitar(abb->izq, n);
  return abb;

}
