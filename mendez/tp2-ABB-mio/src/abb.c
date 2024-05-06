#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> //borrar

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == 0)
		return NULL;
	abb_t *nuevo_arbol = malloc(sizeof(abb_t));
	if (nuevo_arbol == 0)
		return NULL;
	nuevo_arbol->nodo_raiz = NULL;
	nuevo_arbol->comparador = comparador;
	nuevo_arbol->tamanio = 0;
	return nuevo_arbol;
}
nodo_abb_t *inserto_elemento_y_comparo(abb_t *arbol, nodo_abb_t *nodo_actual,
				       void *elemento)
{
	if (nodo_actual == 0) {
		nodo_abb_t *nuevo_nodo = malloc(sizeof(nodo_abb_t));
		if (nuevo_nodo == 0)
			return NULL;
		nuevo_nodo->elemento = elemento;
		nuevo_nodo->izquierda = NULL;
		nuevo_nodo->derecha = NULL;
		arbol->tamanio++;
		return nuevo_nodo;
	}

	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	if (comparacion > 0)
		nodo_actual->derecha = inserto_elemento_y_comparo(
			arbol, nodo_actual->derecha, elemento);

	if (comparacion <=
	    0) //asumo que cuando el elemento es igual, va a la izquierda
		nodo_actual->izquierda = inserto_elemento_y_comparo(
			arbol, nodo_actual->izquierda, elemento);

	return nodo_actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == 0)
		return NULL;
	if (elemento == 0) //re-verrrr  PD:borrar comentarios
		return NULL;
	arbol->nodo_raiz =
		inserto_elemento_y_comparo(arbol, arbol->nodo_raiz, elemento);
	return arbol;
}

nodo_abb_t *buscar_menor_predecesor(nodo_abb_t *raiz)
{
	nodo_abb_t *nodo_menor = NULL;
	if (!raiz->derecha->derecha) {
		nodo_menor = raiz->derecha;
		raiz->derecha = nodo_menor->izquierda;
		return nodo_menor;
	}
	return buscar_menor_predecesor(raiz->derecha);
}

nodo_abb_t *reemplazar_con_menor_predecesor(nodo_abb_t *raiz)
{
	nodo_abb_t *aux = NULL;
	if (!raiz->izquierda->derecha) {
		aux = raiz->izquierda;
		aux->derecha = raiz->derecha;
		return aux;
	}
	aux = buscar_menor_predecesor(raiz->izquierda);
	aux->izquierda = raiz->izquierda;
	aux->derecha = raiz->derecha;
	return aux;
}

nodo_abb_t *saco_al_elemento_comparando(abb_t *arbol, nodo_abb_t *nodo_actual,
					void *elemento,
					void **encontre_al_elemento)
{
	if (!nodo_actual)
		return NULL;
	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	if (comparacion == 0) {
		nodo_abb_t *aux = NULL;
		*encontre_al_elemento = nodo_actual->elemento;
		if (nodo_actual->izquierda && nodo_actual->derecha) {
			aux = reemplazar_con_menor_predecesor(nodo_actual);
			free(nodo_actual);
			arbol->tamanio--;
			return aux;
		}
		if (nodo_actual->izquierda) {
			aux = nodo_actual->izquierda;
			free(nodo_actual);
			arbol->tamanio--;
			return aux;
		}
		aux = nodo_actual->derecha;
		free(nodo_actual);
		arbol->tamanio--;
		return aux;
	}
	if (comparacion > 0)
		nodo_actual->derecha = saco_al_elemento_comparando(
			arbol, nodo_actual->derecha, elemento,
			encontre_al_elemento);
	if (comparacion < 0)
		nodo_actual->izquierda = saco_al_elemento_comparando(
			arbol, nodo_actual->izquierda, elemento,
			encontre_al_elemento);
	return nodo_actual;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == 0 || abb_vacio(arbol))
		return NULL;
	void *encontre_al_elemento = NULL;
	arbol->nodo_raiz = saco_al_elemento_comparando(
		arbol, arbol->nodo_raiz, elemento, &encontre_al_elemento);

	return encontre_al_elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return elemento;
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol || (!arbol->nodo_raiz) || (arbol->tamanio == 0))
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	return 0;
}

void destruir_post_orden(nodo_abb_t *nodo_actual, void (*destructor)(void *))
{
	if (!nodo_actual)
		return;
	destruir_post_orden(nodo_actual->izquierda, destructor);
	destruir_post_orden(nodo_actual->derecha, destructor);
	if (destructor && nodo_actual->elemento)
		destructor(nodo_actual->elemento);
	free(nodo_actual);
	return;
}
void abb_destruir(abb_t *arbol)
{
	if (arbol == 0)
		return;
	destruir_post_orden(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == 0)
		return;
	if (destructor == 0)
		destruir_post_orden(arbol->nodo_raiz, NULL);
	else
		destruir_post_orden(arbol->nodo_raiz, destructor);
	free(arbol);
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
