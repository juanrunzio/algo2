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

int comparador(void *elemento_1, void *elemento_2)
{
	int *e_1 = elemento_1;
	int *e_2 = elemento_2;
	return (int)(*e_1 - *e_2);
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

void prueba_de_insertar_elementos_en_un_arbol_y_chequeo_de_tamanio()
{
	int numero_28 = 28;
	int numero_33 = 33;
	int numero_4 = 4;
	int numero_52 = 52;
	int numero_2 = 2;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_28);
	pa2m_afirmar(nuevo_arbol->tamanio == 1, "Se pudo insertar el primer elemento en un arbol que estaba vacio, aumento su tamanio a 1");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_33);
	pa2m_afirmar(nuevo_arbol->tamanio == 2, "Se pudo insertar el segundo elemento en el arbol, aumento su tamanio a 2");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_4);
	pa2m_afirmar(nuevo_arbol->tamanio == 3, "Se pudo insertar el tercer elemento en el arbol, aumento su tamanio a 3");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_52);
	pa2m_afirmar(nuevo_arbol->tamanio == 4, "Se pudo insertar el cuarto elemento en el arbol, aumento su tamanio a 4");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_2);
	pa2m_afirmar(nuevo_arbol->tamanio == 5, "Se pudo insertar el quinto elemento en el arbol, aumento su tamanio a 5");

	abb_destruir(nuevo_arbol);
}

void prueba_de_insertar_un_elemento_null_en_un_arbol()
{
	abb_t *arbol = abb_crear(comparador);
	abb_t *nuevo_arbol = abb_insertar(arbol, NULL);
	pa2m_afirmar(nuevo_arbol == NULL, "No se puede insertar el elemento , ya que el elemento es NULL");
	abb_destruir(nuevo_arbol);
	abb_destruir(arbol);
}
void prueba_de_insertar_elemento_en_un_arbol_que_es_null()
{
	int numero = 31;
	pa2m_afirmar(abb_insertar(NULL, &numero) == NULL, "El arbol es NULL, por lo tanto no se puede insertar ningun elemento");
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
	pa2m_nuevo_grupo("Pruebas del tipo de insercion al ABB");
	prueba_de_insertar_elementos_en_un_arbol_y_chequeo_de_tamanio();
	prueba_de_insertar_un_elemento_null_en_un_arbol();
	prueba_de_insertar_elemento_en_un_arbol_que_es_null();



	pa2m_nuevo_grupo("\n======================== XXX ========================");
	pa2m_nuevo_grupo("\n======================== XXX ========================");


	pa2m_nuevo_grupo("\n======================== XXX ========================");
	pa2m_nuevo_grupo("\n======================== XXX ========================");
	return pa2m_mostrar_reporte();
}
