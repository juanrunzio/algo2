#include "pa2m.h"
#include "./src/lista.h"
//#include "./src/lista.c"

void prueba_simple()
{
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
    pa2m_afirmar(lista->nodo_inicio != NULL, "Se insertó un elemento al final de la lista correctamente");
    lista_destruir(lista);
}

void prueba_insercion_posicion() {
    lista_t *lista = lista_crear();
    int elemento = 10;
    lista_insertar_en_posicion(lista, &elemento, 0);
    pa2m_afirmar(lista->nodo_inicio != NULL, "Se insertó un elemento en la posición especificada correctamente");
    lista_destruir(lista);
}


int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	pa2m_nuevo_grupo("Pruebas de creacion de lista");
	prueba_creacion_lista();

	pa2m_nuevo_grupo("Pruebas de insercion en lista");
	prueba_insercion_final();
	prueba_insercion_posicion();

	return pa2m_mostrar_reporte();
}
