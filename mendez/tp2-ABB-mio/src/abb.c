#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(comparador == 0)
		return NULL;
	abb_t *nuevo_arbol = malloc(sizeof(abb_t));
	if(nuevo_arbol == 0)
		return NULL;
	nuevo_arbol->nodo_raiz = NULL;
	nuevo_arbol->comparador = comparador;
	nuevo_arbol->tamanio = 0;
	return nuevo_arbol;

}
nodo_abb_t *inserto_elemento_y_comparo(abb_t *arbol, nodo_abb_t *nodo_actual, void *elemento)
{
	if(nodo_actual == 0) {
		nodo_abb_t *nuevo_nodo = malloc(sizeof(nodo_abb_t));
		if(nuevo_nodo == 0)
			return NULL;
		nuevo_nodo->elemento = elemento;
		nuevo_nodo->izquierda = NULL;
		nuevo_nodo->derecha = NULL;
		arbol->tamanio++;
		return nuevo_nodo;
	}

	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	if (comparacion > 0)
		nodo_actual->derecha = inserto_elemento_y_comparo(arbol, nodo_actual->derecha, elemento);

	if(comparacion <= 0)//asumo que cuando el elemento es igual, va a la izquierda
		nodo_actual->izquierda = inserto_elemento_y_comparo(arbol, nodo_actual->izquierda, elemento);

	return nodo_actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(arbol == 0)
		return NULL;
	if(elemento == 0)//re-verrrr  PD:borrar comentarios
		return NULL;
	arbol->nodo_raiz = inserto_elemento_y_comparo(arbol, arbol->nodo_raiz, elemento);
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{

	return elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return elemento;
}

bool abb_vacio(abb_t *arbol)
{
	return true;
}

size_t abb_tamanio(abb_t *arbol)
{
	return 0;
}

void abb_destruir(abb_t *arbol)
{
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
