#include "tp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

static nodo_abb *crear_nodo(struct pokemon_info *pokemon)
{
	nodo_abb *nuevo_nodo = (nodo_abb *)malloc(sizeof(nodo_abb));
	if (!nuevo_nodo) {
		return NULL;
	}
	nuevo_nodo->dato = *pokemon;
	nuevo_nodo->izquierda = NULL;
	nuevo_nodo->derecha = NULL;
	return nuevo_nodo;
}

nodo_abb *insertar_pokemon(nodo_abb *raiz, struct pokemon_info *pokemon)
{
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
static char *duplicar_cadena(const char *cadena)
{
	size_t longitud = strlen(cadena) + 1;
	char *nueva_cadena = (char *)malloc(longitud);
	if (nueva_cadena) {
		memcpy(nueva_cadena, cadena, longitud);
	}
	return nueva_cadena;
}

// Función para separar una línea en tokens sin usar strtok
static char *extraer_token(char **str, const char *delim)
{
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
static struct pokemon_info *crear_pokemon(const char *linea)
{
	struct pokemon_info *pokemon =
		(struct pokemon_info *)malloc(sizeof(struct pokemon_info));
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

TP *tp_crear(const char *nombre_archivo)
{
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
		linea[strcspn(linea, "\n")] =
			'\0'; // Eliminar el salto de línea

		struct pokemon_info *pokemon = crear_pokemon(linea);
		if (pokemon) {
			tp->arbol_pokemones =
				insertar_pokemon(tp->arbol_pokemones, pokemon);
		}
	}

	fclose(archivo);
	return tp;
}

static int contar_pokemon(nodo_abb *nodo)
{
	if (nodo == NULL) {
		return 0;
	}
	return 1 + contar_pokemon(nodo->izquierda) +
	       contar_pokemon(nodo->derecha);
}

int tp_cantidad_pokemon(TP *tp)
{
	if (tp == NULL) {
		return 0;
	}
	return contar_pokemon(tp->arbol_pokemones);
}

// Función auxiliar para convertir una cadena a minúsculas
static void convertir_minusculas(char *destino, const char *origen)
{
	while (*origen) {
		*destino = tolower(*origen);
		destino++;
		origen++;
	}
	*destino = '\0';
}

// Función auxiliar para buscar un Pokémon en el ABB
static const struct pokemon_info *buscar_pokemon_en_abb(nodo_abb *raiz,
							const char *nombre)
{
	if (raiz == NULL) {
		return NULL;
	}
	char nombre_actual[100], nombre_buscado[100];
	convertir_minusculas(nombre_actual, raiz->dato.nombre);
	convertir_minusculas(nombre_buscado, nombre);

	int comparacion = strcmp(nombre_buscado, nombre_actual);

	if (comparacion == 0) {
		return &(raiz->dato);
	} else if (comparacion < 0) {
		return buscar_pokemon_en_abb(raiz->izquierda, nombre);
	} else {
		return buscar_pokemon_en_abb(raiz->derecha, nombre);
	}
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	if (tp == NULL || nombre == NULL) {
		return NULL;
	}
	return buscar_pokemon_en_abb(tp->arbol_pokemones, nombre);
}

// Función auxiliar para contar el número de Pokémon en el ABB
static void contar_pokemones(nodo_abb *raiz, int *contador)
{
	if (raiz == NULL) {
		return;
	}
	contar_pokemones(raiz->izquierda, contador);
	(*contador)++;
	contar_pokemones(raiz->derecha, contador);
}

// Función auxiliar para llenar un array con los nombres de los Pokémon
static void llenar_array_nombres(nodo_abb *raiz, char **nombres, int *indice)
{
	if (raiz == NULL) {
		return;
	}
	llenar_array_nombres(raiz->izquierda, nombres, indice);
	nombres[*indice] = raiz->dato.nombre;
	(*indice)++;
	llenar_array_nombres(raiz->derecha, nombres, indice);
}

char *tp_nombres_disponibles(TP *tp)
{
	if (tp == NULL || tp->arbol_pokemones == NULL) {
		return NULL;
	}

	int cantidad_pokemones = 0;
	contar_pokemones(tp->arbol_pokemones, &cantidad_pokemones);

	if (cantidad_pokemones == 0) {
		return NULL;
	}

	char **nombres = malloc(cantidad_pokemones * sizeof(char *));
	if (nombres == NULL) {
		return NULL;
	}

	int indice = 0;
	llenar_array_nombres(tp->arbol_pokemones, nombres, &indice);

	size_t longitud_total = 0;
	for (int i = 0; i < cantidad_pokemones; i++) {
		longitud_total += strlen(nombres[i]) + 1;
	}

	char *resultado = malloc(longitud_total);
	if (resultado == NULL) {
		free(nombres);
		return NULL;
	}

	resultado[0] = '\0';
	for (int i = 0; i < cantidad_pokemones; i++) {
		strcat(resultado, nombres[i]);
		if (i < cantidad_pokemones - 1) {
			strcat(resultado, ",");
		}
	}

	free(nombres);
	return resultado;
}

bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
{
	if (tp == NULL || nombre == NULL) {
		return false;
	}

	const struct pokemon_info *pokemon = tp_buscar_pokemon(tp, nombre);
	if (pokemon == NULL) {
		return false;
	}

	// Verificar que el otro jugador no haya seleccionado el mismo Pokémon
	enum TP_JUGADOR otro_jugador = (jugador == JUGADOR_1) ? JUGADOR_2 :
								JUGADOR_1;
	if (tp->seleccionados[otro_jugador] == pokemon) {
		return false;
	}

	// Seleccionar el Pokémon para el jugador
	tp->seleccionados[jugador] = (struct pokemon_info *)pokemon;
	return true;
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

static void liberar_nodo(nodo_abb *nodo)
{
	if (nodo) {
		// Liberar recursivamente los subárboles izquierdo y derecho
		liberar_nodo(nodo->izquierda);
		liberar_nodo(nodo->derecha);
		// Liberar el nombre del Pokémon
		free(nodo->dato.nombre);
		// Liberar el nodo
		free(nodo);
	}
}

void tp_destruir(TP *tp)
{
	if (!tp)
		return;

	// Liberar todos los nodos del árbol
	liberar_nodo(tp->arbol_pokemones);

	// Liberar los punteros de los jugadores si están asignados
	if (tp->seleccionados[0]) {
		free(tp->seleccionados[0]->nombre); // Liberar el nombre
		free(tp->seleccionados[0]); // Liberar la estructura
	}
	if (tp->seleccionados[1]) {
		free(tp->seleccionados[1]->nombre); // Liberar el nombre
		free(tp->seleccionados[1]); // Liberar la estructura
	}

	// Liberar las pistas y sus obstáculos
	for (int i = 0; i < 2; i++) {
		if (tp->pistas[i]) {
			free(tp->pistas[i]);
		}
	}

	// Liberar la estructura TP
	free(tp);
}
