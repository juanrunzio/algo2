#include "abb.h"
#include <stdio.h>

void mostrar_nodo(int dato, void* contexto)
{
  bool* es_primero = contexto;
  if(!*es_primero)
    printf("-");
  printf("%i", dato);
  *es_primero = false;
}

int main(int argc, char *argv[]) {

  struct abb* abb = abb_crear();
  abb = abb_insertar(abb, 7);
  abb = abb_insertar(abb, 5);
  abb = abb_insertar(abb, 13);
  abb = abb_insertar(abb, 3);
  abb = abb_insertar(abb, 6);
  abb = abb_insertar(abb, 12);

  printf("¿Existe el numero 13? %s\n", abb_existe(abb, 13)?"SI":"NO");
  printf("¿Existe el numero 10? %s\n", abb_existe(abb, 10)?"SI":"NO");

  bool es_primero = true;
  printf("INORDEN\n");
  abb_con_cada_elemento(abb, ABB_RECORRIDO_INORDEN, mostrar_nodo, &es_primero);
  printf("\n");
  printf("PREORDEN\n");
  abb_con_cada_elemento(abb, ABB_RECORRIDO_PREORDEN, mostrar_nodo, &es_primero);
  abb_destruir(abb);

  return 0;
}
