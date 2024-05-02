#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"
#include <stdio.h>


void prueba_simple()
{
	int i = 14;
	int j = 18;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}
void prueba_de_crear_un_arbol_con_el_comparador_null()
{
	pa2m_afirmar(abb_crear(NULL) == NULL, "No se puede crear el arbol , ya que tiene un comparador NULL");
}


void prueba_para_comprobar_que_el_arbol_fue_creado_correctamente_y_con_las_estructuras_inicializadas()
{
	abb_t *nuevo_arbol = abb_crear(comparador);
	pa2m_afirmar(nuevo_arbol != NULL, "La memoria se reservo para el nuevo arbol");
	pa2m_afirmar(abb_tamanio(nuevo_arbol) == 0, "Como se creo el arbol la cantidad de elementos es 0");
	pa2m_afirmar(nuevo_arbol->nodo_raiz == NULL, "Nodo raiz es igual a NULL");
	abb_destruir(nuevo_arbol);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	pa2m_nuevo_grupo("\n======================== XXX ========================");

	pa2m_nuevo_grupo("Pruebas de la creacion de un ABB");
	prueba_de_crear_un_arbol_con_el_comparador_null();
	prueba_para_comprobar_que_el_arbol_fue_creado_correctamente_y_con_las_estructuras_inicializadas();

	pa2m_nuevo_grupo("\n======================== XXX ========================");
	pa2m_nuevo_grupo("\n======================== XXX ========================");
	pa2m_nuevo_grupo("\n======================== XXX ========================");


	pa2m_nuevo_grupo("\n======================== XXX ========================");
	pa2m_nuevo_grupo("\n======================== XXX ========================");
	return pa2m_mostrar_reporte();
}
