#include "lista.h"
#include "pa2mm.h"


void lista_crear_crea_una_lista_no_nula() {
  lista_t* lista = lista_crear();
  pa2m_afirmar(lista != NULL, "La lista creada no es nuela");
  lista_destruir(lista);

}

void lista_crear_crea_una_lista_vacia() {
  lista_t* lista = lista_crear();
  pa2m_afirmar(lista_tamanio(lista) == 0, "La lista creada tiene tamanio 0");
  lista_destruir(lista);

}


void lista_obtener_devuelve_null_si_la_lista_esta_vacia() {
  lista_t* lista = lista_crear();
  pa2m_afirmar(lista_obtener(lista, 0) == NULL, "Obtener de una lista recien creada me da null");
  lista_destruir(lista);

}


void lista_insertar_aumenta_el_tamanio_de_la_lista() {
  void *e1, *e2;
  lista_t* lista = lista_crear();
  lista_insertar(lista, e1);
  pa2m_afirmar(lista_tamanio(lista) == 1, "Al insertar un elemento, la lista crece (tamanio 1)");
  lista_insertar(lista, e2);
  pa2m_afirmar(lista_tamanio(lista) == 2, "Al insertar un elemento, la lista crece (tamanio 2)");
  lista_destruir(lista);


}

void lista_obtener_recupera_los_elementos_almacenados() {
  //le asigno cualquier cosa como para que no se queje valgrind , al comparar algo q no esta inicializado
  void *e1=(void*)1, *e2=(void*)2;
  lista_t* lista = lista_crear();
  lista_insertar(lista, e1);
  lista_insertar(lista, e2);
  pa2m_afirmar(lista_obtener(lista, 0) == e1, "Al obtener el primer elemento de la lista , obtengo el primer elemento insertado");
  pa2m_afirmar(lista_obtener(lista, 1) == e2, "Al obtener el primer elemento de la lista, obtengo el segundo elemento insertado");
  lista_destruir(lista);
}

void lista_obtener_de_una_posicion_inexistente_devuelve_null() {
  void *e1=(void*)1, *e2=(void*)2;
  lista_t* lista = lista_crear();
  lista_insertar(lista, e1);
  lista_insertar(lista, e2);
  pa2m_afirmar(lista_obtener(lista, 100) == NULL, "Al obtener el elemento 100 de la lista tamanio 2, obtengo NULL");
  lista_destruir(lista);

}

void destruir(void* el) {
  int* e = el;
  (*e)++;
}

void lista_destruir_todo_destruye_todos_los_elementos() {
  //void *e1=malloc(1), *e2=malloc(1);
  int i1=1, i2=2;
  lista_t* lista = lista_crear();
  lista_insertar(lista, &i1);
  lista_insertar(lista, &i2);
  //lista_destruir_todo(lista, free);
  lista_destruir_todo(lista, destruir);
  pa2m_afirmar(i1==2 && i2==3, "El destructor del usuario fue aplicado a todos los elementos una vez")
}

int main(int argc, char *argv[]) {
  pa2m_nuevo_grupo("Pruebas de creacion");
  lista_crear_crea_una_lista_no_nula();
  lista_crear_crea_una_lista_vacia();
  lista_obtener_devuelve_null_si_la_lista_esta_vacia();


  pa2m_nuevo_grupo("Pruebas de insercion y obtencion");
  lista_insertar_aumenta_el_tamanio_de_la_lista();
  lista_obtener_recupera_los_elementos_almacenados();
  lista_obtener_de_una_posicion_inexistente_devuelve_null();

  pa2m_nuevo_grupo("Pruebas de destruccion");
  lista_destruir_todo_destruye_todos_los_elementos();

  return 0;
}
