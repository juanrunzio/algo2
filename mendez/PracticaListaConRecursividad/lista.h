#ifndef LISTA_H_
#define LISTA_H_

typedef struct lista lista_t;

lista_t* lista_crear();
lista_t* lista_insertar(lista_t*, void*);
void* lista_obtener(lista_t*, int);
int lista_tamanio(lista_t*);
void lista_destruir(lista_t*);


#endif // LISTA_H_
