#include "tp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo_abb {
    struct pokemon_info *pokemon;
    struct nodo_abb *izquierda;
    struct nodo_abb *derecha;
} nodo_abb_t;

struct tp {
    nodo_abb_t *raiz;
};

static char *duplicar_cadena(const char *cadena) {
    size_t longitud = strlen(cadena) + 1;
    char *nueva_cadena = (char *)malloc(longitud);
    if (nueva_cadena) {
        memcpy(nueva_cadena, cadena, longitud);
    }
    return nueva_cadena;
}

static char *extraigo_cada_campo_separado(char **str, const char *delim) {
    char *start = *str;
    char *end = strstr(start, delim);
    if (end) {
        *end = '\0';
        *str = end + strlen(delim);
    } else {
        *str = NULL;
    }
    return start;
}

static struct pokemon_info *crear_pokemon(const char *linea) {
    struct pokemon_info *pokemon = (struct pokemon_info *)malloc(sizeof(struct pokemon_info));
    if (!pokemon) {
        return NULL;
    }

    char *resto = duplicar_cadena(linea);
    if (!resto) {
        free(pokemon);
        return NULL;
    }

    char *campo_del_archivo = extraigo_cada_campo_separado(&resto, ",");
    if (!campo_del_archivo) {
        free(resto);
        free(pokemon);
        return NULL;
    }
    pokemon->nombre = duplicar_cadena(campo_del_archivo);

    campo_del_archivo = extraigo_cada_campo_separado(&resto, ",");
    if (!campo_del_archivo) {
        free(pokemon->nombre);
        free(resto);
        free(pokemon);
        return NULL;
    }
    pokemon->fuerza = atoi(campo_del_archivo);

    return pokemon;
}

static nodo_abb_t *insertar_pokemon(nodo_abb_t *raiz, struct pokemon_info *pokemon) {
    if (raiz == NULL) {
        nodo_abb_t *nuevo_nodo = (nodo_abb_t *)malloc(sizeof(nodo_abb_t));
        if (!nuevo_nodo) {
            return NULL;
        }
        nuevo_nodo->pokemon = pokemon;
        nuevo_nodo->izquierda = NULL;
        nuevo_nodo->derecha = NULL;
        return nuevo_nodo;
    }

    if (strcmp(pokemon->nombre, raiz->pokemon->nombre) < 0) {
        raiz->izquierda = insertar_pokemon(raiz->izquierda, pokemon);
    } else if (strcmp(pokemon->nombre, raiz->pokemon->nombre) > 0) {
        raiz->derecha = insertar_pokemon(raiz->derecha, pokemon);
    }

    return raiz;
}


TP *tp_crear(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        return NULL;
    }

    // creo la estructura TP
    TP *tp = (TP *)malloc(sizeof(TP));
    if (!tp) {
        fclose(archivo);
        return NULL;
    }

    // inicializo la raíz del árbol
    tp->raiz = NULL;

    // leo el archivo línea por línea y crear los nodos del árbol
    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {
        // Crear un nuevo Pokémon a partir de la línea
        struct pokemon_info *pokemon = crear_pokemon(linea);
        if (!pokemon) {
            continue; // Saltar al siguiente pokemon si hay un error
        }

        // Insertar el Pokémon en el árbol
        tp->raiz = insertar_pokemon(tp->raiz, pokemon);
    }

    fclose(archivo);

    return tp;
}

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

int tp_cantidad_pokemon(TP *tp)
{
	return 0;
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	return NULL;
}

char *tp_nombres_disponibles(TP *tp)
{
	return NULL;
}

bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
{
	return false;
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp,
						   enum TP_JUGADOR jugador)
{
	return NULL;
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador,
			      enum TP_OBSTACULO obstaculo, unsigned posicion)
{
	return 0;
}

unsigned tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)
{
	return 0;
}

char *tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)
{
	return NULL;
}

void tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)
{
	return;
}

unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
{
	return 0;
}

char *tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)
{
	return NULL;
}

static void liberar_nodo(nodo_abb_t *nodo) {
    if (nodo != NULL) {
        liberar_nodo(nodo->izquierda);
        liberar_nodo(nodo->derecha);
        free(nodo->pokemon->nombre);
        free(nodo->pokemon);
        free(nodo);
    }
}

void tp_destruir(TP *tp) {
    if (tp != NULL) {
        liberar_nodo(tp->raiz);
        free(tp);
    }
}
