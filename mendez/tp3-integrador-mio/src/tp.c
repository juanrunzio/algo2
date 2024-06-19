#include "tp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo_abb {
    struct pokemon_info dato;
    struct nodo_abb *izquierda;
    struct nodo_abb *derecha;
} nodo_abb;

struct tp {
    nodo_abb *arbol_pokemones;
    struct pokemon_info *seleccionados[2];
    enum TP_OBSTACULO *pistas[2];
    unsigned cantidad_obstaculos[2];
};

static nodo_abb *crear_nodo(struct pokemon_info *pokemon) {
    nodo_abb *nuevo_nodo = (nodo_abb *)malloc(sizeof(nodo_abb));
    if (!nuevo_nodo) {
        return NULL;
    }
    nuevo_nodo->dato = *pokemon;
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;
    return nuevo_nodo;
}

nodo_abb *insertar_pokemon(nodo_abb *raiz, struct pokemon_info *pokemon) {
    if (raiz == NULL) {
        return crear_nodo(pokemon);
    }

    if (strcmp(pokemon->nombre, raiz->dato.nombre) < 0) {
        raiz->izquierda = insertar_pokemon(raiz->izquierda, pokemon);
    } else {
        raiz->derecha = insertar_pokemon(raiz->derecha, pokemon);
    }

    return raiz;
}

// Función para duplicar una cadena (reemplazo de strdup)
static char *duplicar_cadena(const char *cadena) {
    size_t longitud = strlen(cadena) + 1;
    char *nueva_cadena = (char *)malloc(longitud);
    if (nueva_cadena) {
        memcpy(nueva_cadena, cadena, longitud);
    }
    return nueva_cadena;
}

// Función para separar una línea en tokens sin usar strtok
static char *extraer_token(char **str, const char *delim) {
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

// Función para crear un nuevo Pokémon a partir de una línea de texto
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

    char *campo_del_archivo = extraer_token(&resto, ",");
    if (!campo_del_archivo) {
        free(resto);
        free(pokemon);
        return NULL;
    }
    pokemon->nombre = duplicar_cadena(campo_del_archivo);

    campo_del_archivo = extraer_token(&resto, ",");
    if (!campo_del_archivo) {
        free(pokemon->nombre);
        free(resto);
        free(pokemon);
        return NULL;
    }
    pokemon->fuerza = atoi(campo_del_archivo);

    campo_del_archivo = extraer_token(&resto, ",");
    if (!campo_del_archivo) {
        free(pokemon->nombre);
        free(resto);
        free(pokemon);
        return NULL;
    }
    pokemon->destreza = atoi(campo_del_archivo);

    campo_del_archivo = extraer_token(&resto, ",");
    if (!campo_del_archivo) {
        free(pokemon->nombre);
        free(resto);
        free(pokemon);
        return NULL;
    }
    pokemon->inteligencia = atoi(campo_del_archivo);

    free(resto);
    return pokemon;
}


TP *tp_crear(const char *nombre_archivo) {
     FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        return NULL;
    }

    TP *tp = (TP *)malloc(sizeof(TP));
    if (!tp) {
        fclose(archivo);
        return NULL;
    }

    tp->arbol_pokemones = NULL;

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';  // Eliminar el salto de línea

        struct pokemon_info *pokemon = crear_pokemon(linea);
        if (pokemon) {
            tp->arbol_pokemones = insertar_pokemon(tp->arbol_pokemones, pokemon);
        }
    }

    fclose(archivo);
    return tp;
}

static int contar_pokemon(nodo_abb *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return 1 + contar_pokemon(nodo->izquierda) + contar_pokemon(nodo->derecha);
}

int tp_cantidad_pokemon(TP *tp)
{
	if (tp == NULL) {
        return 0;
    }
    return contar_pokemon(tp->arbol_pokemones);
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

static void liberar_nodo(nodo_abb *nodo) {
   if (nodo != NULL) {
        liberar_nodo(nodo->izquierda);
        liberar_nodo(nodo->derecha);
        free(nodo->dato.nombre);
        free(nodo);
    }
}

void tp_destruir(TP *tp) {
     if (tp != NULL) {
        // Liberar el árbol de Pokémon
        liberar_nodo(tp->arbol_pokemones);
        
        // Liberar los Pokémon seleccionados
        for (int i = 0; i < 2; ++i) {
            if (tp->seleccionados[i] != NULL) {
                free(tp->seleccionados[i]->nombre);
                free(tp->seleccionados[i]);
            }
        }

        // Liberar las pistas
        free(tp->pistas[0]);
        free(tp->pistas[1]);
        
        // Liberar el TP
        free(tp);
    }
}
