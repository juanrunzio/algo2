#include "jugador.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_PISTA 100


player_t* jugador_crear(int numero_jugador)
{
    player_t* jugador = malloc(sizeof(player_t));
    if (!jugador) return NULL;
    
    jugador->numero = numero_jugador;
    jugador->pokemon = NULL;
    jugador->pista = NULL;
    jugador->tamanio_pista = 0;
    jugador->capacidad_pista = 0;
    
    return jugador;
}

void jugador_destructor(player_t* jugador)
{
    if (jugador) {
        free(jugador->pista);
        free(jugador);
    }
}

bool jugador_agregar_pokemon(player_t* jugador, player_t* otro_jugador, const struct pokemon_info* pokemon)
{
    if (!jugador || !pokemon) return false;
    if (otro_jugador && otro_jugador->pokemon == pokemon) return false;
    
    jugador->pokemon = pokemon;
    return true;
}

const struct pokemon_info* jugador_ver_pokemon(player_t* jugador)
{
    return jugador ? jugador->pokemon : NULL;
}

unsigned jugador_insertar_pista(player_t* jugador, enum TP_OBSTACULO obstaculo, unsigned posicion)
{
    if (!jugador) return 0;
    
    if (jugador->tamanio_pista >= jugador->capacidad_pista) {
        jugador->capacidad_pista = jugador->capacidad_pista == 0 ? 1 : jugador->capacidad_pista * 2;
        enum TP_OBSTACULO *nueva_pista = realloc(jugador->pista, jugador->capacidad_pista * sizeof(enum TP_OBSTACULO));
        if (!nueva_pista) return 0;
        jugador->pista = nueva_pista;
    }
    
    if (posicion >= jugador->tamanio_pista) {
        jugador->pista[jugador->tamanio_pista++] = obstaculo;
    } else {
        for (unsigned i = jugador->tamanio_pista; i > posicion; i--) {
            jugador->pista[i] = jugador->pista[i-1];
        }
        jugador->pista[posicion] = obstaculo;
        jugador->tamanio_pista++;
    }
    
    return jugador->tamanio_pista;
}
unsigned jugador_eliminar_obstaculo_pista(player_t* jugador, unsigned posicion)
{
    if (!jugador || posicion >= jugador->tamanio_pista) return 0;
    
    for (unsigned i = posicion; i < jugador->tamanio_pista - 1; i++) {
        jugador->pista[i] = jugador->pista[i+1];
    }
    jugador->tamanio_pista--;
    
    return jugador->tamanio_pista;
}

unsigned jugador_tamanio_pista(player_t* jugador)
{
    return jugador ? jugador->tamanio_pista : 0;
}

char* jugador_mostrar_pista(player_t* jugador)
{
    if (!jugador || jugador->tamanio_pista == 0) return NULL;
    
    char* resultado = malloc(jugador->tamanio_pista + 1);
    if (!resultado) return NULL;
    
    for (unsigned i = 0; i < jugador->tamanio_pista; i++) {
        switch (jugador->pista[i]) {
            case OBSTACULO_FUERZA:
                resultado[i] = 'F';
                break;
            case OBSTACULO_DESTREZA:
                resultado[i] = 'D';
                break;
            case OBSTACULO_INTELIGENCIA:
                resultado[i] = 'I';
                break;
        }
    }
    resultado[jugador->tamanio_pista] = '\0';
    
    return resultado;
}

void jugador_limpiar_pista(player_t* jugador)
{
    if (jugador) jugador->tamanio_pista = 0;
}

unsigned jugador_tiempo_pista(player_t* jugador)
{
    if (!jugador || !jugador->pokemon) return 0;
    
    unsigned tiempo_total = 0;
    int obstaculos_consecutivos[3] = {0};
    
    for (unsigned i = 0; i < jugador->tamanio_pista; i++) {
        int atributo = 0;
        int* consecutivos = NULL;
        
        switch (jugador->pista[i]) {
            case OBSTACULO_FUERZA:
                atributo = jugador->pokemon->fuerza;
                consecutivos = &obstaculos_consecutivos[0];
                break;
            case OBSTACULO_DESTREZA:
                atributo = jugador->pokemon->destreza;
                consecutivos = &obstaculos_consecutivos[1];
                break;
            case OBSTACULO_INTELIGENCIA:
                atributo = jugador->pokemon->inteligencia;
                consecutivos = &obstaculos_consecutivos[2];
                break;
            default:
                continue;
        }
        
        int tiempo = 10 - *consecutivos - atributo;
        if (tiempo < 0) tiempo = 0;
        tiempo_total += (unsigned)tiempo;
        
        (*consecutivos)++;
        obstaculos_consecutivos[0] = (jugador->pista[i] == OBSTACULO_FUERZA) ? obstaculos_consecutivos[0] : 0;
        obstaculos_consecutivos[1] = (jugador->pista[i] == OBSTACULO_DESTREZA) ? obstaculos_consecutivos[1] : 0;
        obstaculos_consecutivos[2] = (jugador->pista[i] == OBSTACULO_INTELIGENCIA) ? obstaculos_consecutivos[2] : 0;
    }
    
    return tiempo_total;
}

char* jugador_tiempo_por_obstaculo(player_t* jugador)
{
    if (!jugador || !jugador->pokemon || jugador->tamanio_pista == 0) return NULL;
    
    char* resultado = malloc(jugador->tamanio_pista * 10);
    if (!resultado) return NULL;
    
    char* ptr = resultado;
    int obstaculos_consecutivos[3] = {0};
    
    for (unsigned i = 0; i < jugador->tamanio_pista; i++) {
        int atributo = 0;
        int* consecutivos = NULL;
        
        switch (jugador->pista[i]) {
            case OBSTACULO_FUERZA:
                atributo = jugador->pokemon->fuerza;
                consecutivos = &obstaculos_consecutivos[0];
                break;
            case OBSTACULO_DESTREZA:
                atributo = jugador->pokemon->destreza;
                consecutivos = &obstaculos_consecutivos[1];
                break;
            case OBSTACULO_INTELIGENCIA:
                atributo = jugador->pokemon->inteligencia;
                consecutivos = &obstaculos_consecutivos[2];
                break;
            default:
                free(resultado);
                return NULL;
        }
        
        int tiempo = 10 - *consecutivos - atributo;
        if (tiempo < 0) tiempo = 0;
        
        ptr += sprintf(ptr, "%d,", tiempo);
        
        (*consecutivos)++;
        obstaculos_consecutivos[0] = (jugador->pista[i] == OBSTACULO_FUERZA) ? obstaculos_consecutivos[0] : 0;
        obstaculos_consecutivos[1] = (jugador->pista[i] == OBSTACULO_DESTREZA) ? obstaculos_consecutivos[1] : 0;
        obstaculos_consecutivos[2] = (jugador->pista[i] == OBSTACULO_INTELIGENCIA) ? obstaculos_consecutivos[2] : 0;
    }
    
    if (ptr > resultado) *(ptr - 1) = '\0';
    
    return resultado;
}