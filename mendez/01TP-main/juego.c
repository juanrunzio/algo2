#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "src/tp.h"
#include "src/jugador.h"
#include "src/menu.h"

#define MAX_INTENTOS 5


typedef struct {
    int nivel;
    int longitud_pista;
    int obstaculos_ocultos;
    int intentos_maximos;
} Dificultad;

Dificultad dificultades[] = {
    {1, 3, 0, 5},  // Fácil
    {2, 5, 1, 4},  // Normal
    {3, 7, 2, 3},  // Difícil
    {4, 10, 3, 2}  // Imposible
};

void seleccionar_dificultad(int *dificultad);
void crear_pista_inicial(TP *tp, Dificultad dif);
void crear_pista_rival(TP *tp, Dificultad dif);
void armar_pista_jugador(TP *tp, Dificultad dif);
void mostrar_informacion_pokemones(TP *tp);
void mostrar_pista_rival(TP *tp, Dificultad dif);
double calcular_puntaje(unsigned tiempo_jugador, unsigned tiempo_rival);
bool ejecutar_carrera(TP *tp, Dificultad dif);
char *seleccionar_nombre_azar(TP *tp);
bool pokemon_existe(TP *tp, const char *nombre);
void mostrar_informacion_pokemon(const struct pokemon_info *pokemon);

void seleccionar_dificultad(int *dificultad)
{
    printf("Seleccione la dificultad (1: Fácil, 2: Normal, 3: Difícil, 4: Imposible): ");
    scanf("%d", dificultad);
    if (*dificultad < 1 || *dificultad > 4) {
        printf("Dificultad inválida, seleccionando Normal por defecto\n");
        *dificultad = 2;
    }
}

void crear_pista_inicial(TP *tp, Dificultad dif)
{
    for (int i = 0; i < dif.longitud_pista; ++i) {
        enum TP_OBSTACULO obstaculo = rand() % 3;
        tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo, (unsigned int)i);
    }
}


void crear_pista_rival(TP *tp, Dificultad dif) {
    char *nombre_pokemon_rival = seleccionar_nombre_azar(tp);
    if (!nombre_pokemon_rival || !tp_seleccionar_pokemon(tp, JUGADOR_2, nombre_pokemon_rival)) {
        fprintf(stderr, "Error al seleccionar el Pokemon rival\n");
        free(nombre_pokemon_rival);
        return;
    }
    free(nombre_pokemon_rival);
    crear_pista_inicial(tp, dif);
    const struct pokemon_info *pokemon_rival = tp_pokemon_seleccionado(tp, JUGADOR_2);
    mostrar_informacion_pokemon(pokemon_rival);
    mostrar_pista_rival(tp, dif);
}


void armar_pista_jugador(TP *tp, Dificultad dif) {
    int intentos = 0;
    do {
        tp_limpiar_pista(tp, JUGADOR_1);
        printf("Arme su pista de obstáculos (F: Fuerza, D: Destreza, I: Inteligencia)\n");
        printf("Ingrese los obstáculos uno por uno y presione Enter. Ingrese 'X' para terminar.\n");
        
        char obstaculo;
        int posicion = 0;
        while (posicion < dif.longitud_pista) {
            if (scanf(" %c", &obstaculo) != 1) {
                while (getchar() != '\n'); // Limpiar el buffer de entrada
                printf("Entrada no válida. Intente de nuevo.\n");
                continue;
            }
            if (obstaculo == 'X' || obstaculo == 'x') {
                break;
            }
            enum TP_OBSTACULO tipo_obstaculo;
            switch (obstaculo) {
                case 'F': tipo_obstaculo = OBSTACULO_FUERZA; break;
                case 'D': tipo_obstaculo = OBSTACULO_DESTREZA; break;
                case 'I': tipo_obstaculo = OBSTACULO_INTELIGENCIA; break;
                default: 
                    printf("Obstáculo no válido. Use F, D, o I.\n");
                    continue;
            }
            if (!tp_agregar_obstaculo(tp, JUGADOR_1, tipo_obstaculo, (unsigned int)posicion)) {
                fprintf(stderr, "Error al agregar obstáculo\n");
                break;
            }
            posicion++;
        }

        while (getchar() != '\n'); // Limpiar el buffer de entrada

        intentos++;

        if (intentos < dif.intentos_maximos) {
            char respuesta;
            printf("¿Desea guardar la pista de obstáculos? (S/N): ");
            scanf(" %c", &respuesta);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            if (respuesta != 'N' && respuesta != 'n') break;
        }
    } while (intentos < dif.intentos_maximos);
}

void mostrar_informacion_pokemon(const struct pokemon_info *pokemon)
{
    if (!pokemon) {
        printf("No hay información del Pokemon\n");
        return;
    }
    printf("Pokemon:\n");
    printf("Nombre: %s\n", pokemon->nombre);
    printf("Fuerza: %d\n", pokemon->fuerza);
    printf("Destreza: %d\n", pokemon->destreza);
    printf("Inteligencia: %d\n", pokemon->inteligencia);
}

void mostrar_informacion_pokemones(TP *tp) {
    const struct pokemon_info *pokemon_jugador = tp_pokemon_seleccionado(tp, JUGADOR_1);
    const struct pokemon_info *pokemon_rival = tp_pokemon_seleccionado(tp, JUGADOR_2);

    printf("Pokemon del jugador:\n");
    if (pokemon_jugador) {
        mostrar_informacion_pokemon(pokemon_jugador);
    } else {
        printf("No ha seleccionado un Pokemon aún.\n");
    }

    printf("\nPokemon rival:\n");
    if (pokemon_rival) {
        mostrar_informacion_pokemon(pokemon_rival);
    } else {
        printf("Aún no se ha seleccionado un Pokemon rival.\n");
    }
}

void mostrar_pista_rival(TP *tp, Dificultad dif)
{
    char *pista = tp_obstaculos_pista(tp, JUGADOR_2);
    if (!pista) {
        printf("Error al obtener la pista del rival\n");
        return;
    }

    printf("Pista del rival (longitud: %d):\n", dif.longitud_pista);
    for (int i = 0; i < dif.longitud_pista; i++) {
        if (i < dif.obstaculos_ocultos) {
            printf("?");
        } else {
            printf("%c", pista[i]);
        }
    }
    printf("\n");
    free(pista);
}

double calcular_puntaje(unsigned tiempo_jugador, unsigned tiempo_rival)
{
    double ta = (double)tiempo_jugador;
    double tb = (double)tiempo_rival;
    return 100.0 - 100.0 * fabs(ta - tb) / (ta + tb);
}

bool ejecutar_carrera(TP *tp, Dificultad dif) {
    int intentos = 0;

    do {
        unsigned tiempo_jugador = tp_calcular_tiempo_pista(tp, JUGADOR_1);
        unsigned tiempo_rival = tp_calcular_tiempo_pista(tp, JUGADOR_2);
        printf("Tiempo del jugador: %u\n", tiempo_jugador);
        printf("Tiempo del rival: %u\n", tiempo_rival);
        
        double puntaje = calcular_puntaje(tiempo_jugador, tiempo_rival);
        printf("Puntaje: %.2f\n", puntaje);

        if (tiempo_jugador == tiempo_rival) {
            printf("¡Empate perfecto!\n");
        } else if (puntaje > 90) {
            printf("¡Excelente resultado!\n");
        } else if (puntaje > 70) {
            printf("Buen resultado\n");
        } else {
            printf("Puedes mejorar\n");
        }

        intentos++;

        if (intentos < dif.intentos_maximos) {
            char respuesta;
            printf("¿Desea intentar de nuevo? (S/N): ");
            scanf(" %c", &respuesta);
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            if (respuesta != 'N' && respuesta != 'n') {
                printf("Volviendo al menú principal...\n");
                return true; // Vuelve al menú principal
            }
        } else {
            printf("Has alcanzado el máximo número de intentos.\n");
            printf("Volviendo al menú principal...\n");
            return true; // Vuelve al menú principal
        }
    } while (intentos < dif.intentos_maximos);

    return true; // Vuelve al menú principal
}

char *seleccionar_nombre_azar(TP *tp)
{
    if (!tp) {
        return NULL;
    }

    char *nombres = tp_nombres_disponibles(tp);
    if (!nombres) {
        return NULL;
    }

    size_t num_nombres = 1;
    for (const char *c = nombres; *c; c++) {
        if (*c == ',') {
            num_nombres++;
        }
    }

    size_t indice_azar = (size_t)rand() % num_nombres;

    const char *nombre_actual = nombres;
    for (size_t i = 0; i < indice_azar; i++) {
        nombre_actual = strchr(nombre_actual, ',');
        if (!nombre_actual) {
            free(nombres);
            return NULL;
        }
        nombre_actual++;
    }

    const char *fin_nombre = strchr(nombre_actual, ',');
    size_t longitud = fin_nombre ? (size_t)(fin_nombre - nombre_actual) : strlen(nombre_actual);

    char *resultado = malloc(longitud + 1);
    if (!resultado) {
        free(nombres);
        return NULL;
    }

    memcpy(resultado, nombre_actual, longitud);
    resultado[longitud] = '\0';

    free(nombres);
    return resultado;
}

char* my_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* new_str = malloc(len);
    if (new_str == NULL) return NULL;
    return memcpy(new_str, s, len);
}

int my_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

bool pokemon_existe(TP *tp, const char *nombre) {
    char *nombres = tp_nombres_disponibles(tp);
    if (!nombres) return false;
    
    char *nombre_lower = my_strdup(nombre);
    if (!nombre_lower) {
        free(nombres);
        return false;
    }

    for (int i = 0; nombre_lower[i]; i++) {
        nombre_lower[i] = (char)tolower((unsigned char)nombre_lower[i]);
    }

    char *nombres_lower = my_strdup(nombres);
    if (!nombres_lower) {
        free(nombres);
        free(nombre_lower);
        return false;
    }

    for (int i = 0; nombres_lower[i]; i++) {
        nombres_lower[i] = (char)tolower((unsigned char)nombres_lower[i]);
    }

    bool existe = strstr(nombres_lower, nombre_lower) != NULL;

    free(nombres);
    free(nombres_lower);
    free(nombre_lower);
    return existe;
}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo_pokemon>\n", argv[0]);
        return 1;
    }

    const char *nombre_archivo = argv[1];
    TP *tp = tp_crear(nombre_archivo);
    if (!tp) {
        fprintf(stderr, "Error al crear la estructura TP\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    menu_t *menu = menu_crear();
    if (!menu) {
        fprintf(stderr, "Error al crear el menú\n");
        tp_destruir(tp);
        return 1;
    }

    int nivel_dificultad = 0;
    char nombre_pokemon_jugador[50] = "";
    bool juego_terminado = false;
    bool pista_rival_creada = false;

    while (!juego_terminado) {
        menu_mostrar(menu);
        int opcion = menu_seleccionar_opcion(menu);

        switch (opcion) {
            case 1:
                seleccionar_dificultad(&nivel_dificultad);
                pista_rival_creada = false;
                break;
            case 2:
                printf("Seleccione su Pokemon: ");
				scanf("%49s", nombre_pokemon_jugador);
				if (!pokemon_existe(tp, nombre_pokemon_jugador)) {
					printf("El Pokemon %s no existe.\n", nombre_pokemon_jugador);
					nombre_pokemon_jugador[0] = '\0';
				} else {
					char *nombres = tp_nombres_disponibles(tp);
					if (nombres) {
						char *token = strtok(nombres, ",");
						while (token) {
							if (my_strcasecmp(token, nombre_pokemon_jugador) == 0) {
								if (!tp_seleccionar_pokemon(tp, JUGADOR_1, token)) {
									fprintf(stderr, "Error al seleccionar el Pokemon del jugador\n");
									nombre_pokemon_jugador[0] = '\0';
								} else {
									printf("Pokemon %s seleccionado con éxito.\n", token);
									strcpy(nombre_pokemon_jugador, token);
								}
								break;
							}
							token = strtok(NULL, ",");
						}
						free(nombres);
					}
				}
				pista_rival_creada = false;
				break;
            case 3:
                mostrar_informacion_pokemones(tp);
                break;
            case 4:
                if (nivel_dificultad == 0 || nombre_pokemon_jugador[0] == '\0') {
                    printf("Primero seleccione la dificultad y el Pokemon\n");
                } else {
                    Dificultad dif = dificultades[nivel_dificultad - 1];
                    if (!pista_rival_creada) {
                        crear_pista_rival(tp, dif);
                        pista_rival_creada = true;
                    }
                    armar_pista_jugador(tp, dif);
                }
                break;
            case 5:
				if (nivel_dificultad == 0 || nombre_pokemon_jugador[0] == '\0' || !pista_rival_creada) {
				printf("Primero seleccione la dificultad, el Pokemon y arme la pista\n");
				} else {
					ejecutar_carrera(tp, dificultades[nivel_dificultad - 1]);
					// No necesitas hacer nada más aquí, la función siempre regresa al menú principal
				}
				break;
            case 6:
                juego_terminado = true;
                break;
            default:
                printf("Opción no válida\n");
        }
    }

    menu_destruir(menu);
    tp_destruir(tp);
    return 0;
}