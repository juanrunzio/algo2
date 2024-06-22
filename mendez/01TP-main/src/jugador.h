#ifndef JUGADOR_H
#define JUGADOR_H

#include <stdbool.h>
#include "tp.h"

#define JUGADOR_1 0
#define JUGADOR_2 1

struct player {
	int numero;
	const struct pokemon_info *pokemon;
	enum TP_OBSTACULO *pista;
	unsigned tamanio_pista;
	unsigned capacidad_pista;
};

typedef struct player player_t;

player_t *jugador_crear(int numero_jugador);

void jugador_destructor(player_t *jugador);

bool jugador_agregar_pokemon(player_t *jugador, player_t *otro_jugador,
			     const struct pokemon_info *pokemon);

const struct pokemon_info *jugador_ver_pokemon(player_t *jugador);

unsigned jugador_insertar_pista(player_t *jugador, enum TP_OBSTACULO obstaculo,
				unsigned posicion);

unsigned jugador_eliminar_obstaculo_pista(player_t *jugador, unsigned posicion);

unsigned jugador_tamanio_pista(player_t *jugador);

char *jugador_mostrar_pista(player_t *jugador);

void jugador_limpiar_pista(player_t *jugador);

unsigned jugador_tiempo_pista(player_t *jugador);

char *jugador_tiempo_por_obstaculo(player_t *jugador);

#endif // JUGADOR_H