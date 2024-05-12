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
bool imprimir_numeros(void *elemento_1, void *elemento_2)
{
	int *e_1 = elemento_1;
	int *e_2 = elemento_2;
	printf("%i ", *e_1);
	return (*e_1 != *e_2);
}

void prueba_de_crear_un_arbol_con_el_comparador_null()
{
	pa2m_afirmar(
		abb_crear(NULL) == NULL,
		"No se puede crear el arbol , ya que tiene un comparador NULL");
}

void prueba_para_comprobar_que_el_arbol_fue_creado_correctamente_y_con_las_estructuras_inicializadas()
{
	abb_t *nuevo_arbol = abb_crear(comparador);
	pa2m_afirmar(nuevo_arbol != NULL,
		     "La memoria se reservo para el nuevo arbol");
	pa2m_afirmar(abb_tamanio(nuevo_arbol) == 0,
		     "Como se creo el arbol la cantidad de elementos es 0");
	pa2m_afirmar(nuevo_arbol->nodo_raiz == NULL,
		     "Nodo raiz es igual a NULL");
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
	pa2m_afirmar(
		nuevo_arbol->tamanio == 1,
		"Se pudo insertar el primer elemento en un arbol que estaba vacio, aumento su tamanio a 1");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_33);
	pa2m_afirmar(
		nuevo_arbol->tamanio == 2,
		"Se pudo insertar el segundo elemento en el arbol, aumento su tamanio a 2");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_4);
	pa2m_afirmar(
		nuevo_arbol->tamanio == 3,
		"Se pudo insertar el tercer elemento en el arbol, aumento su tamanio a 3");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_52);
	pa2m_afirmar(
		nuevo_arbol->tamanio == 4,
		"Se pudo insertar el cuarto elemento en el arbol, aumento su tamanio a 4");
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_2);
	pa2m_afirmar(
		nuevo_arbol->tamanio == 5,
		"Se pudo insertar el quinto elemento en el arbol, aumento su tamanio a 5");

	abb_destruir(nuevo_arbol);
}

void prueba_de_insertar_elemento_en_un_arbol_que_es_null()
{
	int numero = 31;
	pa2m_afirmar(
		abb_insertar(NULL, &numero) == NULL,
		"El arbol es NULL, por lo tanto no se puede insertar ningun elemento");
}

void prueba_de_eliminar_un_elemento_del_arbol()
{
	int numero_28 = 28;
	int numero_33 = 33;
	int numero_4 = 4;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_28);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_33);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_4);
	//cambiar mnsj
	pa2m_afirmar(abb_quitar(nuevo_arbol, &numero_4) == &numero_4,
		     "Elimino el ultimo elemento insertado");
	pa2m_afirmar(abb_quitar(nuevo_arbol, &numero_33) == &numero_33,
		     "Elimino el anteultimo elemento insertado");
	pa2m_afirmar(abb_quitar(nuevo_arbol, &numero_28) == &numero_28,
		     "Elimino el primer elemento insertado");

	pa2m_afirmar(
		abb_tamanio(nuevo_arbol) == 0,
		"El tamaño se redujo a 0, ya que al sacarle todos los elementos quedo vacio");
	abb_destruir(nuevo_arbol);
}

void prueba_de_eliminar_un_elemento_que_no_existe_en_el_arbol()
{
	int numero_52 = 52;
	int numero_2 = 2;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_52);
	pa2m_afirmar(
		abb_quitar(nuevo_arbol, &numero_2) == NULL,
		"El elemento no se encuentra en el arbol, por lo tanto no se puede eliminar");
	abb_destruir(nuevo_arbol);
}

void prueba_de_encontrar_un_elemento_en_el_arbol()
{
	int numero_25 = 25;
	int numero_31 = 31;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_31);
	pa2m_afirmar(abb_buscar(nuevo_arbol, &numero_31) == &numero_31,
		     "Se encontro el primer elemento correctamente");
	pa2m_afirmar(abb_buscar(nuevo_arbol, &numero_25) == &numero_25,
		     "Se encontro el segundo elemento correctamente");
	abb_destruir(nuevo_arbol);
}

void prueba_de_encontrar_un_elemento_que_no_existe_en_el_arbol()
{
	int numero_25 = 25;
	int numero_31 = 31;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
	pa2m_afirmar(
		abb_buscar(nuevo_arbol, &numero_31) == NULL,
		"El elemento no existe en el arbol, por lo tanto no se puede encontrar");
	abb_destruir(nuevo_arbol);
}

void puedo_encontrar_elemento()
{
	int numero_10 = 10;
	int numero_20 = 20;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
	pa2m_afirmar(abb_buscar(nuevo_arbol, &numero_20) == &numero_20,
		     "Encontro el primer elemento buscado");
	pa2m_afirmar(abb_buscar(nuevo_arbol, &numero_10) == &numero_10,
		     "Encontro el segundo elemento buscado");
	abb_destruir(nuevo_arbol);
}

void itero_hasta_encontrar_null()
{
	int numero_12 = 12;
	int numero_18 = 18;
	int numero_4 = 4;
	int numero_3 = 3;
	int numero_8 = 8;
	void *null = NULL;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_12);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_18);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_4);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_8);
	nuevo_arbol = abb_insertar(nuevo_arbol, &null);
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN,
					   imprimir_numeros, &null) == 1,
		     "Itero 1 vez hasta encontrar NULL INORDEN");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN,
					   imprimir_numeros, &null) == 4,
		     "Itero 4 veces hasta encontrar NULL PREORDEN");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN,
					   imprimir_numeros, &null) == 1,
		     "Itero 1 vez hasta encontrar NULL POSTORDEN");
	abb_destruir(nuevo_arbol);
}
void no_es_posible_iterar_con_un_arbol_que_es_null()
{
	void *null = NULL;
	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, imprimir_numeros,
					   &null) == 0,
		     "No se puedo iterar un arbol que es NULL");
}
void no_es_posible_iterar_con_una_funcion_null()
{
	abb_t *nuevo_arbol = abb_crear(comparador);
	void *null = NULL;
	nuevo_arbol = abb_insertar(nuevo_arbol, &null);
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN, NULL, &null) ==
			     0,
		     "No se puede iterar arbol con funcion NULL");
	abb_destruir(nuevo_arbol);
}

void itero_hasta_encontrar_numero_inorden()
{
	int numero_10 = 10;
	int numero_20 = 20;
	int numero_5 = 5;
	int numero_3 = 3;
	int numero_7 = 7;
	int numero_15 = 15;
	int numero_25 = 25;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN,
					   imprimir_numeros, &numero_25) == 7,
		     "Itero 7 veces hasta encontrar el 25");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN,
					   imprimir_numeros, &numero_10) == 4,
		     "Itero 4 veces hasta encontrar el 10");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN,
					   imprimir_numeros, &numero_15) == 5,
		     "Itero 5 veces hasta encontrar el 15");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN,
					   imprimir_numeros, &numero_20) == 6,
		     "Itero 6 veces hasta encontrar el 20");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, INORDEN,
					   imprimir_numeros, &numero_5) == 2,
		     "Itero 2 veces hasta encontrar el 5");
	abb_destruir(nuevo_arbol);
}
void itero_hasta_encontrar_numero_preorden()
{
	int numero_10 = 10;
	int numero_20 = 20;
	int numero_5 = 5;
	int numero_3 = 3;
	int numero_7 = 7;
	int numero_15 = 15;
	int numero_25 = 25;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN,
					   imprimir_numeros, &numero_25) == 7,
		     "Itero 7 veces hasta encontrar el 25");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN,
					   imprimir_numeros, &numero_10) == 1,
		     "Itero 1 veces hasta encontrar el 10");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN,
					   imprimir_numeros, &numero_15) == 6,
		     "Itero 6 veces hasta encontrar el 15");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN,
					   imprimir_numeros, &numero_20) == 5,
		     "Itero 5 veces hasta encontrar el 20");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, PREORDEN,
					   imprimir_numeros, &numero_5) == 2,
		     "Itero 2 veces hasta encontrar el 5");
	abb_destruir(nuevo_arbol);
}
void itero_hasta_encontrar_numero_postorden()
{
	int numero_10 = 10;
	int numero_20 = 20;
	int numero_5 = 5;
	int numero_3 = 3;
	int numero_7 = 7;
	int numero_15 = 15;
	int numero_25 = 25;
	abb_t *nuevo_arbol = abb_crear(comparador);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_10);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_20);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_5);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_3);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_7);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_15);
	nuevo_arbol = abb_insertar(nuevo_arbol, &numero_25);
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN,
					   imprimir_numeros, &numero_25) == 5,
		     "Itero 5 veces hasta encontrar el 25");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN,
					   imprimir_numeros, &numero_10) == 7,
		     "Itero 7 veces hasta encontrar el 10");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN,
					   imprimir_numeros, &numero_15) == 4,
		     "Itero 4 veces hasta encontrar el 15");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN,
					   imprimir_numeros, &numero_20) == 6,
		     "Itero 5 veces hasta encontrar el 20");
	pa2m_afirmar(abb_con_cada_elemento(nuevo_arbol, POSTORDEN,
					   imprimir_numeros, &numero_5) == 3,
		     "Itero 2 veces hasta encontrar el 5");
	abb_destruir(nuevo_arbol);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");

	pa2m_nuevo_grupo("Pruebas de la creacion de un ABB");
	prueba_de_crear_un_arbol_con_el_comparador_null();
	prueba_para_comprobar_que_el_arbol_fue_creado_correctamente_y_con_las_estructuras_inicializadas();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("Pruebas del tipo de insercion al ABB");
	prueba_de_insertar_elementos_en_un_arbol_y_chequeo_de_tamanio();
	prueba_de_insertar_elemento_en_un_arbol_que_es_null();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("Pruebas de eliminacion del ABB");
	prueba_de_eliminar_un_elemento_del_arbol();
	prueba_de_eliminar_un_elemento_que_no_existe_en_el_arbol();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("Pruebas de busqueda en el ABB");
	prueba_de_encontrar_un_elemento_en_el_arbol();
	prueba_de_encontrar_un_elemento_que_no_existe_en_el_arbol();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("Pruebas del iterador");
	itero_hasta_encontrar_null();
	no_es_posible_iterar_con_un_arbol_que_es_null();
	no_es_posible_iterar_con_una_funcion_null();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	return pa2m_mostrar_reporte();
}
