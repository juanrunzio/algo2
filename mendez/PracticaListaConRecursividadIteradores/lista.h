#ifndef LISTA_H_
#define LISTA_H_
#include <stdbool.h>

typedef struct lista lista_t;

lista_t* lista_crear();
lista_t* lista_insertar(lista_t*, void*);
//O(n)
void* lista_obtener(lista_t*, int);
int lista_tamanio(lista_t*);

void lista_iterar_todos_los_elementos(lista_t*, bool(f)(void*,int, void*), void* contexto);
void lista_destruir(lista_t*);
void lista_destruir_todo(lista_t*, void(f)(void*));

typedef struct lista_iterador lista_iterador_t;

lista_iterador_t* lista_iterador_crear(lista_t*);
bool lista_iterador_hay_mas_elementos_por_recorrer(lista_iterador_t*);
void iterador_siguiente_interacion(lista_iterador_t*);
void* lista_iterador_devolveme_un_elemento(lista_iterador_t*);

#endif // LISTA_H_
