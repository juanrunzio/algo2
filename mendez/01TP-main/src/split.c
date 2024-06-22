#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contador_de_separadores(const char *string, char separador)
{
	int contador = 0;
	int i;
	for (i = 0; string[i] != '\0'; i++) {
		if (string[i] == separador)
			contador++;
	}
	return contador;
}

char **split(const char *string, char separador)
{
	if (string == NULL) {
		return NULL;
	}

	int cantidad_de_elementos_vec =
		contador_de_separadores(string, separador) + 1;
	char **vec_de_punteros = (char **)malloc(
		(size_t)(cantidad_de_elementos_vec + 1) * sizeof(char *));

	if (vec_de_punteros == NULL) {
		return NULL;
	}
	int posicion_inicial_de_palabra = 0;
	int indice_del_vector = 0;
	int puedo_continuar = 0;
	int i, j;

	for (i = 0; string[i] != '\0' && puedo_continuar != 1; i++) {
		if (string[i] == separador) {
			int longitud_del_char_ptr =
				i - posicion_inicial_de_palabra;
			vec_de_punteros[indice_del_vector] = (char *)malloc(
				(size_t)(longitud_del_char_ptr + 1) *
				sizeof(char));
			if (vec_de_punteros[indice_del_vector] == NULL) {
				puedo_continuar = 1;
			} else {
				strncpy(vec_de_punteros[indice_del_vector],
					string + posicion_inicial_de_palabra,
					(size_t)longitud_del_char_ptr);

				vec_de_punteros[indice_del_vector]
					       [longitud_del_char_ptr] = '\0';
				posicion_inicial_de_palabra = i + 1;
				indice_del_vector++;
			}
		}
	}

	if (!puedo_continuar) {
		size_t longitud_restante =
			strlen(string) - (size_t)posicion_inicial_de_palabra;
		vec_de_punteros[indice_del_vector] =
			(char *)malloc((longitud_restante + 1) * sizeof(char));
		if (vec_de_punteros[indice_del_vector] == NULL) {
			puedo_continuar = 1;
		} else {
			strcpy(vec_de_punteros[indice_del_vector],
			       string + posicion_inicial_de_palabra);
		}
	}

	if (puedo_continuar) {
		for (j = 0; j <= indice_del_vector; j++) {
			free(vec_de_punteros[j]);
		}
		free(vec_de_punteros);
		return NULL;
	}

	vec_de_punteros[cantidad_de_elementos_vec] = NULL;

	return vec_de_punteros;
}
