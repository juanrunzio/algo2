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
  lista_destruir(lista, e2);
  pa2m_afirmar(lista_tamanio(lista) == 2, "Al insertar un elemento, la lista crece (tamanio 2)");
  lista_destruir(lista);


}

int main(int argc, char *argv[]) {
  pa2m_nuevo_grupo("Pruebas de creacion");
  lista_crear_crea_una_lista_no_nula();
  lista_crear_crea_una_lista_vacia();
  lista_obtener_devuelve_null_si_la_lista_esta_vacia();


  pa2m_nuevo_grupo("Pruebas de insercion");
  lista_insertar_aumenta_el_tamanio_de_la_lista();

  return 0;
}
