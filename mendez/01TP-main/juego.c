#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "src/tp.h"
#include "src/jugador.h"
#include "src/menu.h"

void seleccionar_dificultad(int *dificultad)
{
	printf("Seleccione la dificultad (1: Fácil, 2: Normal, 3: Difícil, 4: Imposible): ");
	scanf("%d", dificultad);
	if (*dificultad < 1 || *dificultad > 4) {
		printf("Dificultad inválida, seleccionando Normal por defecto\n");
		*dificultad = 2;
	}
}

void crear_pista_inicial(TP *tp, int dificultad)
{
	int longitud_pista;
	if (dificultad == 1) {
		longitud_pista = 3;
	} else if (dificultad == 2) {
		longitud_pista = 5;
	} else if (dificultad == 3) {
		longitud_pista = 7;
	} else if (dificultad == 4) {
		longitud_pista = 10;
	} else {
		longitud_pista = 5;
	}

	// Crear pista de obstáculos para el rival
	for (int i = 0; i < longitud_pista; ++i) {
		int obstaculo = rand() % 3;
		tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo, (unsigned int)i);
	}
}

void mostrar_informacion_pokemon(const struct pokemon_info *pokemon)
{
	if (!pokemon) {
		printf("No hay información del Pokemon\n");
		return;
	}
	printf("Pokemon rival:\n");
	printf("Nombre: %s\n", pokemon->nombre);
	printf("Fuerza: %d\n", pokemon->fuerza);
	printf("Destreza: %d\n", pokemon->destreza);
	printf("Inteligencia: %d\n", pokemon->inteligencia);
}

void ejecutar_carrera(TP *tp, enum TP_JUGADOR rival)
{
	unsigned tiempo_jugador = tp_calcular_tiempo_pista(tp, JUGADOR_1);
	unsigned tiempo_rival = tp_calcular_tiempo_pista(tp, rival);
	printf("Tiempo del jugador: %u\n", tiempo_jugador);
	printf("Tiempo del rival: %u\n", tiempo_rival);
	if (tiempo_jugador == tiempo_rival) {
		printf("Empate!\n");
	} else if (tiempo_jugador < tiempo_rival) {
		printf("¡Ganaste!\n");
	} else {
		printf("Perdiste\n");
	}
}

bool manejar_opcion(TP *tp, int opcion, int *dificultad)
{
	if (opcion == 1) {
		seleccionar_dificultad(dificultad);
	} else if (opcion == 2) {
		char nombre_pokemon[50];
		printf("Ingrese el nombre del Pokemon: ");
		scanf("%s", nombre_pokemon);
		if (tp_seleccionar_pokemon(tp, JUGADOR_1, nombre_pokemon)) {
			printf("Pokemon seleccionado correctamente\n");
		} else {
			printf("Error al seleccionar el Pokemon\n");
		}
	} else if (opcion == 3) {
		int tipo_obstaculo, posicion;
		printf("Ingrese el tipo de obstáculo (0: Fuerza, 1: Destreza, 2: Inteligencia): ");
		scanf("%d", &tipo_obstaculo);
		printf("Ingrese la posición del obstáculo: ");
		scanf("%d", &posicion);
		if (tp_agregar_obstaculo(tp, JUGADOR_1, tipo_obstaculo,
					 (unsigned int)posicion)) {
			printf("Obstáculo agregado correctamente\n");
		} else {
			printf("Error al agregar el obstáculo\n");
		}
	} else if (opcion == 4) {
		int posicion;
		printf("Ingrese la posición del obstáculo a quitar: ");
		scanf("%d", &posicion);
		if (tp_quitar_obstaculo(tp, JUGADOR_1,
					(unsigned int)posicion)) {
			printf("Obstáculo quitado correctamente\n");
		} else {
			printf("Error al quitar el obstáculo\n");
		}
	} else if (opcion == 5) {
		char *pista = tp_obstaculos_pista(tp, JUGADOR_1);
		if (pista) {
			printf("Pista: %s\n", pista);
			free(pista);
		} else {
			printf("Error al mostrar la pista\n");
		}
	} else if (opcion == 6) {
		ejecutar_carrera(tp, JUGADOR_2);
	} else if (opcion == 7) {
		printf("Saliendo...  FINNN DEL JUEGO\n");
	} else {
		printf("Opción inválida :(\n");
	}
	return (opcion != 7);
}

char *seleccionar_nombre_azar(TP *tp)
{
	if (!tp) {
		fprintf(stderr, "Error: TP no válido.\n");
		return NULL;
	}

	int num_pokemon = tp_cantidad_pokemon(tp);
	if (num_pokemon <= 0) {
		fprintf(stderr, "Error: No hay Pokémon disponibles.\n");
		return NULL;
	}

	// Obtener la lista de nombres disponibles
	char *nombres = tp_nombres_disponibles(tp);
	if (!nombres) {
		fprintf(stderr,
			"Error: No se pudo obtener la lista de nombres.\n");
		return NULL;
	}

	// Contar cuántos nombres hay
	int count = 1;
	for (char *c = nombres; *c; c++) {
		if (*c == ',')
			count++;
	}

	// Elegir un índice al azar
	srand((unsigned int)time(NULL));
	int indice_azar = rand() % count;

	// Encontrar el nombre en el índice elegido
	char *nombre_azar = nombres;
	for (int i = 0; i < indice_azar; i++) {
		nombre_azar = strchr(nombre_azar, ',');
		if (!nombre_azar) {
			free(nombres);
			return NULL; // Esto no debería ocurrir
		}
		nombre_azar++; // Saltar la coma
	}

	// Copiar el nombre elegido
	char *fin_nombre = strchr(nombre_azar, ',');
	int longitud = fin_nombre ? (int)(fin_nombre - nombre_azar) :
				    (int)strlen(nombre_azar);
	char *resultado = malloc(longitud + 1);
	if (!resultado) {
		free(nombres);
		return NULL;
	}
	strncpy(resultado, nombre_azar, longitud);
	resultado[longitud] = '\0';

	free(nombres);
	return resultado;
}

// Función principal
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

	// Inicializar rand
	srand((unsigned int)time(NULL));

	// Crear jugadores
	player_t *jugador = jugador_crear(JUGADOR_1);
	player_t *rival = jugador_crear(JUGADOR_2);
	if (!jugador || !rival) {
		fprintf(stderr, "Error al crear jugadores\n");
		tp_destruir(tp);
		return 1;
	}

	// Crear menú
	menu_t *menu = menu_crear();
	if (!menu) {
		fprintf(stderr, "Error al crear el menú\n");
		tp_destruir(tp);
		jugador_destructor(jugador);
		jugador_destructor(rival);
		return 1;
	}

	// Seleccionar dificultad
	int dificultad;
	seleccionar_dificultad(&dificultad);

	// Seleccionar Pokémon rival al azar
	char *nombre_pokemon_rival = seleccionar_nombre_azar(tp);
	if (!nombre_pokemon_rival) {
		fprintf(stderr,
			"Error al seleccionar el nombre del Pokemon rival\n");
		// Liberar recursos y salir
	}
	const struct pokemon_info *pokemon_rival =
		tp_buscar_pokemon(tp, nombre_pokemon_rival);
	if (!pokemon_rival) {
		fprintf(stderr,
			"Error al obtener la información del Pokemon rival\n");
		free(nombre_pokemon_rival);
		// Liberar recursos y salir
	}
	free(nombre_pokemon_rival);

	// Crear pista inicial para el rival
	crear_pista_inicial(tp, dificultad);

	// Información inicial
	mostrar_informacion_pokemon(pokemon_rival);

	// Interacción con el jugador a través del menú
	int opcion = 0;
	while (opcion != 7) {
		menu_mostrar(menu);
		opcion = menu_seleccionar_opcion(menu);
		manejar_opcion(tp, opcion, &dificultad);
	}

	// Limpiar recursos
	menu_destruir(menu);
	jugador_destructor(jugador);
	jugador_destructor(rival);
	tp_destruir(tp);

	return 0;
}
