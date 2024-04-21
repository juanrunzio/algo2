#include "pa2m.h"
#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}
void free_aux(void *elemento)
{
	// aca para liberar memoria;
}

int lista_creada_distinta_de_null_y_estructuras_inicializadas()
{
	lista_t *lista = lista_crear();
	if (!lista)
		return -1;

	pa2m_afirmar((lista != NULL), "La lista fue creada exitosamente");
	pa2m_afirmar((lista_tamanio(lista) == 0),
		     "La lista creada tiene 0 elementos");

	lista_destruir(lista);
	return 0;
}

int no_puedo_insertar_lista_nula()
{
	int numero = 5;
	lista_t *lista = lista_insertar(NULL, &numero);
	pa2m_afirmar(!lista,
		     "Si la lista es nula no se pueda insertar un elemento");
	return 0;
}

int inserto_elemento_ultima_posicion_lista_vacia()
{
	lista_t *lista = lista_crear();
	int numero = 5;
	lista_t *nueva_lista = lista_insertar(lista, &numero);
	if (!nueva_lista) {
		lista_destruir(lista);
		return -1;
	}
	lista = nueva_lista;

	pa2m_afirmar(
		lista_ultimo(lista) == &numero,
		"El elemento se inserto en la ultima posicion con la lista vacia");
	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "Por lo tanto el tamanio de la lista ahora es 1");
	pa2m_afirmar(
		lista_primero(lista) == &numero,
		"El elemento coincide con la primera posicion porque la lista "
		"estaba vacia");
	lista_destruir(lista);
	return 0;
}

int inserto_elemento_ultima_posicion_lista_no_vacia()
{
	lista_t *lista = lista_crear();
	int numero_1 = 5;
	int numero_2 = 10;
	lista_t *lista_aux_1 = lista_insertar(lista, &numero_1);
	if (!lista_aux_1) {
		lista_destruir(lista);
		return -1;
	}

	lista = lista_aux_1;

	lista_t *lista_aux_2 = lista_insertar(lista, &numero_2);
	if (!lista_aux_2) {
		lista_destruir(lista);
		return -1;
	}
	lista = lista_aux_2;

	pa2m_afirmar(
		lista_ultimo(lista) == &numero_2,
		"El elemento se inserto en la ultima posicion con la lista no vacia");
	pa2m_afirmar(lista_tamanio(lista) == 2, "El tamaño de la lista es 2");
	pa2m_afirmar(lista_primero(lista) == &numero_1,
		     "El elemento que estaba primero continua siendo primero");
	lista_destruir(lista);
	return 0;
}

int puedo_insertar_elemento_null_ultima_posicion()
{
	lista_t *lista = lista_crear();
	lista_t *nueva_lista = lista_insertar(lista, NULL);
	if (!nueva_lista) {
		lista_destruir(lista);
		return -1;
	}

	lista = nueva_lista;

	pa2m_afirmar(lista_ultimo(lista) == NULL,
		     "El elemento se inserto en la ultima posicion y es null");
	pa2m_afirmar(
		lista_tamanio(lista) == 1,
		"El tamaño de la lista crecio al insertar el elemento NULL");
	lista_destruir(lista);
	return 0;
}

int inserto_el_elemento_en_ultima_posicion_si_no_es_dada()
{
	int numero = 5;
	lista_t *lista = lista_crear();
	lista_t *nueva_lista = lista_insertar_en_posicion(lista, &numero, 3);
	if (!nueva_lista)
		return -1;
	lista = nueva_lista;
	pa2m_afirmar(
		lista_ultimo(lista) == &numero,
		"El elemento se inserto en la ultima posicion si no existe la "
		"posicion brindada");
	lista_destruir(lista);
	return 0;
}

int inserto_elemento_posicion_dada()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	int numero_4 = 4;
	int numero_5 = 5;
	lista = lista_insertar(lista, &numero_1);
	lista = lista_insertar(lista, &numero_2);
	lista = lista_insertar(lista, &numero_3);
	lista = lista_insertar_en_posicion(lista, &numero_4, 1);
	lista = lista_insertar_en_posicion(lista, &numero_5, 4);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &numero_4,
		     "El elemento se inserto en la posicion brindada");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == &numero_5,
		     "El elemento se inserto en la previa ultima posicion");
	pa2m_afirmar(
		lista_tamanio(lista) == 5,
		"El tamaño de la lista crecio a 5 al insertar el elemento nuevo");
	lista_destruir(lista);
	return 0;
}

int inserto_un_nuevo_elemento_en_la_posicion_cero_de_una_lista_no_vacia()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	int numero_4 = 4;
	lista = lista_insertar(lista, &numero_1);
	lista = lista_insertar(lista, &numero_2);
	lista = lista_insertar(lista, &numero_3);
	lista = lista_insertar_en_posicion(lista, &numero_4, 0);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &numero_4,
		     "Se inserto un nuevo elemento en la posicion 0");
	pa2m_afirmar(
		lista_tamanio(lista) == 4,
		"El tamaño de la lista aumento al insertar el elemento nuevo en "
		"la posicion 0");
	lista_destruir(lista);
	return 0;
}

int elemento_coincide_con_buscado()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	lista = lista_insertar(lista, &numero_1);
	lista = lista_insertar(lista, &numero_2);
	lista = lista_insertar(lista, &numero_3);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &numero_2,
		     "Elemento encontrado en la posicion esperada");
	lista_destruir(lista);
	return 0;
}

int si_la_posicion_no_existe_retorna_null()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	lista = lista_insertar(lista, &numero_1);
	lista = lista_insertar(lista, &numero_2);
	lista = lista_insertar(lista, &numero_3);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == NULL,
		     "La posicion buscada no existe y devuelve NULL");
	lista_destruir(lista);
	return 0;
}

int no_se_puede_quitar_el_ultimo_elemento_de_lista_null_o_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_quitar(NULL) == NULL,
		"No se puedo quitar el ultimo elemento de una lista que no existe");
	pa2m_afirmar(
		lista_quitar(lista) == NULL,
		"No se puedo quitar el ultimo elemento de una lista vacia");
	lista_destruir(lista);
	return 0;
}

int al_quitar_ultimo_elemento_longitud_disminuye_en_uno()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	lista = lista_insertar(lista, &numero_1);
	pa2m_afirmar(
		lista_quitar(lista) == &numero_1,
		"Se removio el ultimo elemento y se retorno dicho elemento");
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "Se disminuyo en uno el tamaño de la lista");
	lista_destruir(lista);
	return 0;
}

int quitar_elemento_en_una_posicion_dada()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	int numero_4 = 4;
	lista = lista_insertar(lista, &numero_1);
	lista = lista_insertar(lista, &numero_2);
	lista = lista_insertar(lista, &numero_3);
	lista = lista_insertar(lista, &numero_4);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 0) == &numero_1,
		"Se removio el elemento de la posicion dada y se retorno dicho elemento");
	pa2m_afirmar(
		lista_tamanio(lista) == 3,
		"Se disminuyo en uno el tamaño total de la lista al remover el "
		"elemento de la posicion dada");
	lista_destruir_todo(lista, free_aux);
	return 0;
}

int no_puedo_quitar_elemento_de_posicion_en_lista_null_o_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_quitar_de_posicion(NULL, 3) == NULL,
		"No puedo quitar un elemento de una posicion dada de una lista NULL");
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 3) == NULL,
		"No puedo quitar un elemento de una posicion dada de una lista vacia");
	lista_destruir_todo(lista, free_aux);
	return 0;
}

int comparador_aux(void *elemento_1, void *elemento_2)
{
	int *ele_1 = (int *)elemento_1;
	int *ele_2 = (int *)elemento_2;
	if (*ele_1 == *ele_2)
		return 0;
	return -1;
}

int no_puedo_buscar_elemento_en_lista_funcion_o_contexto_null()
{
	lista_t *lista = lista_crear();
	int numero = 5;
	pa2m_afirmar(lista_buscar_elemento(NULL, comparador_aux, &numero) ==
			     NULL,
		     "No puedo buscar elemento en una lista NULL");
	pa2m_afirmar(lista_buscar_elemento(lista, NULL, &numero) == NULL,
		     "No puedo buscar elemento con un comparador NULL");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_aux, NULL) == NULL,
		     "No puedo buscar un elemento con un contexto NULL");
	lista_destruir_todo(lista, free_aux);
	return 0;
}

int encuentra_elemento_buscado_y_lo_retorna()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	int numero_4 = 4;
	int numero_5 = 2;
	int numero_6 = 6;
	lista = lista_insertar(lista, &numero_1);
	lista = lista_insertar(lista, &numero_2);
	lista = lista_insertar(lista, &numero_3);
	lista = lista_insertar(lista, &numero_4);
	pa2m_afirmar(lista_buscar_elemento(lista, comparador_aux, &numero_5) ==
			     &numero_2,
		     "El elemento fue encontrado y retornado");
	pa2m_afirmar(
		lista_buscar_elemento(lista, comparador_aux, &numero_6) == NULL,
		"Retorna NULL si no encuentra un elemento igual al contexto");
	lista_destruir_todo(lista, free_aux);
	return 0;
}

int no_se_puede_crear_un_iterador_con_lista_null()
{
	pa2m_afirmar(lista_iterador_crear(NULL) == NULL,
		     "No puedo crear iterador externo con lista NULL");
	return 0;
}

int se_puede_crear_un_iterador_externo_con_una_lista_vacia()
{
	lista_t *nueva_lista = lista_crear();
	lista_iterador_t *nuevo_iterador = lista_iterador_crear(nueva_lista);
	pa2m_afirmar(
		nuevo_iterador != NULL,
		"Se puede crear correctamente un iterador externo con una lista vacia");
	lista_iterador_destruir(nuevo_iterador);
	lista_destruir(nueva_lista);
	return 0;
}

int iterador_tiene_siguiente_por_mas_que_sea_null()
{
	lista_t *nueva_lista = lista_crear();
	int numero = 5;
	lista_insertar(nueva_lista, &numero);
	lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(iterador) == true,
		"Iterador tiene siguiente por mas que apunte a una posicion de "
		"memoria null");
	lista_iterador_destruir(iterador);
	lista_destruir(nueva_lista);
	return 0;
}

int iterador_avanza_si_tiene_siguiente()
{
	lista_t *nueva_lista = lista_crear();
	int numero = 5;
	lista_insertar(nueva_lista, &numero);
	lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
	pa2m_afirmar(lista_iterador_avanzar(iterador) == true,
		     "Iterador avanza si tiene siguiente");
	lista_iterador_destruir(iterador);
	lista_destruir(nueva_lista);
	return 0;
}

int iterador_devuelve_el_elemento_de_la_posicion_actual()
{
	lista_t *nueva_lista = lista_crear();
	int numero = 5;
	lista_insertar(nueva_lista, &numero);
	lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == &numero,
		     "Devuelve el elemento actual correctamente");
	lista_iterador_destruir(iterador);
	lista_destruir(nueva_lista);
	return 0;
}

int iterador_devuelve_null_ultima_posicion()
{
	lista_t *nueva_lista = lista_crear();
	int numero = 5;
	lista_insertar(nueva_lista, &numero);
	lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == NULL,
		"Cuando se encuentra en la ultima posicion devuelve NULL como "
		"elemento actual");
	lista_iterador_destruir(iterador);
	lista_destruir(nueva_lista);
	return 0;
}

bool aux_it_interno(void *elemento_1, void *elemento_2)
{
	if (elemento_1 == elemento_2)
		return false;
	return true;
}

int prueba_de_iterador_interno_recorre_elementos()
{
	lista_t *lista = lista_crear();
	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;
	lista = lista_insertar(lista, &numero_1);
	lista = lista_insertar(lista, &numero_2);
	lista = lista_insertar(lista, &numero_3);
	pa2m_afirmar(
		lista_con_cada_elemento(lista, aux_it_interno, &numero_2) == 2,
		"Prueba con iterador interno, devuelve la cantidad de elementos "
		"recorridos, en este caso es 2");
	pa2m_afirmar(
		lista_con_cada_elemento(lista, aux_it_interno, NULL) == 3,
		"Prueba con iterador interno, devuelve la cantidad de elementos "
		"recorridos, al pasarle NULL recorre hasta el final de la "
		"lista, en este caso es 3");
	lista_destruir(lista);
	return 0;
}

void creacion_de_pila_no_null_y_estructuras_inicializadas()
{
	pila_t *nueva_pila = pila_crear();
	pa2m_afirmar((nueva_pila != NULL), "La pila fue creada exitosamente");
	pa2m_afirmar((pila_tamanio(nueva_pila) == 0),
		     "La pila creada tiene 0 elementos");
	pila_destruir(nueva_pila);
}

void puedo_apilar_un_elemento()
{
	pila_t *nueva_pila = pila_crear();
	char letra_x = 'x';
	pila_apilar(nueva_pila, &letra_x);
	pa2m_afirmar((pila_tope(nueva_pila) == &letra_x),
		     "Se añadio 1 elemento a la pila");
	pa2m_afirmar((pila_tope(nueva_pila) == &letra_x),
		     "Su tope ahora es el elemento añadido");
	pa2m_afirmar((pila_tamanio(nueva_pila) == 1),
		     "La pila ahora tiene un elemento");
	pila_destruir(nueva_pila);
}

void no_puedo_apilar_en_una_pila_null()
{
	char letra_a = 'a';
	pa2m_afirmar(pila_apilar(NULL, &letra_a) == NULL,
		     "No puedo apilar elemento en una pila NULL");
}

void puedo_desapilar_un_elemento()
{
	pila_t *nueva_pila = pila_crear();
	char letra_a = 'a';
	pila_apilar(nueva_pila, &letra_a);
	pa2m_afirmar(pila_desapilar(nueva_pila) == &letra_a,
		     "Se desapilo 1 elemento y se retorno");
	pa2m_afirmar(pila_tamanio(nueva_pila) == 0,
		     "La longitud de la pila se disminuyo en 1");
	pila_destruir(nueva_pila);
}

void cola_creada_distinta_de_null_y_estructuras_inicializadas()
{
	cola_t *nueva_cola = cola_crear();
	pa2m_afirmar(nueva_cola != NULL, "Se creo la cola correctamente");
	cola_destruir(nueva_cola);
}

void puedo_encolar_un_elemento_tamanio_aumenta_en_uno()
{
	cola_t *nueva_cola = cola_crear();
	char letra_z = 'z';
	nueva_cola = cola_encolar(nueva_cola, &letra_z);
	pa2m_afirmar(nueva_cola != NULL, "Puedo encolar un elemento");
	pa2m_afirmar(cola_tamanio(nueva_cola) == 1, "El tamaño aumento en 1");
	cola_destruir(nueva_cola);
}
void puedo_encolar_elemento_null()
{
	cola_t *nueva_cola = cola_crear();
	nueva_cola = cola_encolar(nueva_cola, NULL);
	pa2m_afirmar(nueva_cola != NULL, "Puedo encolar un elemento NULL");
	pa2m_afirmar(cola_tamanio(nueva_cola) == 1, "El tamaño aumento en 1");
	cola_destruir(nueva_cola);
}
void no_puedo_encolar_o_desencolar_cola_null()
{
	char letra_b = 'b';
	pa2m_afirmar(cola_encolar(NULL, &letra_b) == NULL,
		     "No puedo encolar en una cola NULL");
	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "No puedo desencolar en una cola NULL");
}

void se_puede_desencolar_elementos()
{
	cola_t *nueva_cola = cola_crear();
	char letra_a = 'a';
	char letra_b = 'b';
	nueva_cola = cola_encolar(nueva_cola, &letra_a);
	nueva_cola = cola_encolar(nueva_cola, &letra_b);
	pa2m_afirmar(cola_desencolar(nueva_cola) == &letra_a,
		     "Se desencolo el primer elemento encolado");
	pa2m_afirmar(cola_desencolar(nueva_cola) == &letra_b,
		     "Se desencolo el primer elemento encolado");
	pa2m_afirmar(cola_tamanio(nueva_cola) == 0, "El tamaño disminuyo en 1");
	cola_destruir(nueva_cola);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	pa2m_nuevo_grupo("Pruebas de creacion de lista");
	lista_creada_distinta_de_null_y_estructuras_inicializadas();

	pa2m_nuevo_grupo(
		"Pruebas de de insercion de elementos en el TDA lista");
	no_puedo_insertar_lista_nula();
	inserto_elemento_ultima_posicion_lista_vacia();
	inserto_elemento_ultima_posicion_lista_no_vacia();
	puedo_insertar_elemento_null_ultima_posicion();
	inserto_el_elemento_en_ultima_posicion_si_no_es_dada();
	inserto_elemento_posicion_dada();
	inserto_un_nuevo_elemento_en_la_posicion_cero_de_una_lista_no_vacia();
	elemento_coincide_con_buscado();
	si_la_posicion_no_existe_retorna_null();

	pa2m_nuevo_grupo("Pruebas de quitar elementos de la lista");
	no_se_puede_quitar_el_ultimo_elemento_de_lista_null_o_vacia();
	al_quitar_ultimo_elemento_longitud_disminuye_en_uno();
	quitar_elemento_en_una_posicion_dada();
	no_puedo_quitar_elemento_de_posicion_en_lista_null_o_vacia();

	pa2m_nuevo_grupo("Pruebas de buscar elemento en la lista");
	no_puedo_buscar_elemento_en_lista_funcion_o_contexto_null();
	encuentra_elemento_buscado_y_lo_retorna();

	pa2m_nuevo_grupo("Pruebas de iterador externo");
	no_se_puede_crear_un_iterador_con_lista_null();
	se_puede_crear_un_iterador_externo_con_una_lista_vacia();
	iterador_tiene_siguiente_por_mas_que_sea_null();
	// iterador_avanza_si_tiene_siguiente();
	iterador_devuelve_el_elemento_de_la_posicion_actual();
	iterador_devuelve_null_ultima_posicion();

	pa2m_nuevo_grupo("Pruebas de iterador interno");
	prueba_de_iterador_interno_recorre_elementos();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");

	pa2m_nuevo_grupo("Pruebas de TDA pila");
	creacion_de_pila_no_null_y_estructuras_inicializadas();
	puedo_apilar_un_elemento();
	no_puedo_apilar_en_una_pila_null();
	puedo_desapilar_un_elemento();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");

	pa2m_nuevo_grupo("Pruebas de TDA cola");
	cola_creada_distinta_de_null_y_estructuras_inicializadas();
	puedo_encolar_un_elemento_tamanio_aumenta_en_uno();
	puedo_encolar_elemento_null();
	no_puedo_encolar_o_desencolar_cola_null();
	se_puede_desencolar_elementos();

	return pa2m_mostrar_reporte();
}
