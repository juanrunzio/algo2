#include "./src/lista.c" //re-verr
#include "./src/lista.h"
#include "pa2m.h"

void prueba_simple() {
  int i = 14;
  int j = 16;
  pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}

void prueba_creacion_lista() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista != NULL, "Se puede crear una lista correctamente");
  lista_destruir(lista); // Liberar la memoria después de la prueba
}

void prueba_insercion_final() {
  lista_t *lista = lista_crear();
  int elemento = 10;
  lista_insertar(lista, &elemento);
  pa2m_afirmar(lista->nodo_inicio != NULL,
               "Se insertó un elemento al final de la lista correctamente");
  lista_destruir(lista);
}

void prueba_insercion_posicion() {
  lista_t *lista = lista_crear();
  int elemento = 10;
  lista_insertar_en_posicion(lista, &elemento, 0);
  pa2m_afirmar(
      lista->nodo_inicio != NULL,
      "Se insertó un elemento en la posición especificada correctamente");
  lista_destruir(lista);
}
void prueba_quitar_elemento() {
  lista_t *lista = lista_crear();
  int elemento1 = 10, elemento2 = 20, elemento3 = 30;
  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);
  lista_insertar(lista, &elemento3);

  // Prueba la eliminación de un elemento en medio de la lista
  void *elemento_eliminado = lista_quitar(lista);
  pa2m_afirmar(elemento_eliminado != NULL,
               "Se eliminó un elemento de la lista correctamente");

  // Verifica que el elemento eliminado es el último elemento insertado
  pa2m_afirmar(*(int *)elemento_eliminado == elemento3,
               "El elemento eliminado es el correcto");

  lista_destruir(lista);
}

void prueba_buscar_elemento() {
  lista_t *lista = lista_crear();
  int elemento1 = 10, elemento2 = 20, elemento3 = 30;
  lista_insertar(lista, &elemento1);
  lista_insertar(lista, &elemento2);
  lista_insertar(lista, &elemento3);

  // Prueba la búsqueda de un elemento en la lista
  int elemento_buscado = 20;
  void *elemento_encontrado = lista_buscar_elemento(
      lista, (int (*)(void *, void *))comparar_enteros, &elemento_buscado);
  pa2m_afirmar(elemento_encontrado != NULL,
               "Se encontró un elemento en la lista correctamente");

  // Verifica que el elemento encontrado es el correcto
  pa2m_afirmar(*(int *)elemento_encontrado == elemento2,
               "El elemento encontrado es el correcto");

  lista_destruir(lista);
}

void prueba_verificar_tamanio() {
  lista_t *lista = lista_crear();

  // Insertar elementos en la lista
  int elementos[] = {10, 20, 30, 40};
  for (size_t i = 0; i < sizeof(elementos) / sizeof(elementos[0]); i++) {
    lista_insertar(lista, &elementos[i]);
  }

  // Verificar tamaño de la lista
  size_t tamano = lista_tamanio(lista);
  pa2m_afirmar(tamano == 4, "El tamaño de la lista es el esperado");

  // Destruir lista
  lista_destruir(lista);
}

void prueba_destruir_lista() {
  lista_t *lista = lista_crear();

  // Insertar elementos en la lista
  int elementos[] = {10, 20, 30, 40};
  for (size_t i = 0; i < sizeof(elementos) / sizeof(elementos[0]); i++) {
    lista_insertar(lista, &elementos[i]);
  }

  // Destruir lista
  lista_destruir(lista);

  // Verificar que la lista ha sido destruida correctamente
  pa2m_afirmar(lista_vacia(lista), "La lista ha sido destruida correctamente");
}

int main() {
  pa2m_nuevo_grupo("\n======================== XXX ========================");
  prueba_simple();

  pa2m_nuevo_grupo("Pruebas de creacion de lista");
  prueba_creacion_lista();

  pa2m_nuevo_grupo("Pruebas de lista, insercion y eliminacion");
  prueba_insercion_final();
  prueba_insercion_posicion();
  prueba_quitar_elemento();

  pa2m_nuevo_grupo("Pruebas de listas busqueda de elementos y tamanios");
  prueba_buscar_elemento();
  prueba_verificar_tamanio();

  pa2m_nuevo_grupo("Pruebas de listas, destructor");
  prueba_destruir_lista();

  return pa2m_mostrar_reporte();
}
