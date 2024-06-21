#ifndef JUGADOR_H
#define JUGADOR_H

#include "tp.h"

typedef struct player_t player_t;

player_t *jugador_crear(enum TP_JUGADOR jugador);
void jugador_destruir(player_t *jugador);
unsigned jugador_insertar_pista(player_t *jugador, enum TP_OBSTACULO obstaculo, unsigned posicion);
unsigned jugador_eliminar_obstaculo_pista(player_t *jugador, unsigned posicion);
const struct pokemon_info *jugador_ver_pokemon(player_t *jugador);
char *jugador_mostrar_pista(player_t *jugador);

#endif // JUGADOR_H