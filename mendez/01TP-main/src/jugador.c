#include "jugador.h"
#include "tp.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h> 

struct player_t {
    enum TP_JUGADOR jugador;
    struct pokemon_info *pokemon;
    struct pista *track;
};

player_t *jugador_crear(enum TP_JUGADOR jugador) {
    player_t *new_player = malloc(sizeof(player_t));
    if (!new_player)
        return NULL;
    new_player->jugador = jugador;
    new_player->pokemon = NULL; // Initialize with no Pokemon
    new_player->track = pista_crear(); // Initialize an empty track
    // Initialize other fields here
    return new_player;
}

void jugador_destruir(player_t *jugador) {
    if (!jugador)
        return;
    // Free other fields here
    pista_destruir(jugador->track);
    free(jugador->pokemon);
    free(jugador);
}

unsigned jugador_insertar_pista(player_t *jugador, enum TP_OBSTACULO obstaculo, unsigned posicion) {
    if (!jugador || !jugador->track)
        return 0;
    return pista_insertar_obstaculo(jugador->track, obstaculo, posicion);
}

unsigned jugador_eliminar_obstaculo_pista(player_t *jugador, unsigned posicion) {
    if (!jugador || !jugador->track)
        return 0;
    return pista_eliminar_obstaculo(jugador->track, posicion);
}

const struct pokemon_info *jugador_ver_pokemon(player_t *jugador) {
    if (!jugador)
        return NULL;
    return jugador->pokemon;
}

char *jugador_mostrar_pista(player_t *jugador) {
    if (!jugador || !jugador->track)
        return NULL;
    return pista_mostrar(jugador->track);
}