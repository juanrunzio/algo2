#include "src/tp.h"



#include "src/tp.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	//Se recomienda pasar el archivo de texto con los pokemon como argumento al ejecutar el programa

	//crear el juego
	tp_crear(argv[1]);
	//mostrar menues
	//correr carrera
	//etc


	//-----------------test-----------------------
// Función para imprimir todos los pokémon en orden alfabético
static void imprimir_pokemons_recursivo(nodo_abb_t *raiz) {
    if (raiz != NULL) {
        imprimir_pokemons_recursivo(raiz->izquierda);
        printf("Nombre: %s, Fuerza: %d, Destreza: %d, Inteligencia: %d\n",
               raiz->pokemon->nombre, raiz->pokemon->fuerza,
               raiz->pokemon->destreza, raiz->pokemon->inteligencia);
        imprimir_pokemons_recursivo(raiz->derecha);
    }
}

// Función pública para imprimir todos los pokémon en orden alfabético
void imprimir_pokemons(TP *tp) {
    if (tp == NULL || tp->raiz == NULL) {
        printf("No hay pokémon para imprimir.\n");
    } else {
        imprimir_pokemons_recursivo(tp->raiz);
    }
}

//-----------------test-----------------------

	return 0;
}
