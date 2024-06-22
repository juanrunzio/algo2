#include "pa2m.h"
#include "src/tp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prueba_simple()
{
	int i = 14;
	int j = 18;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}

void prueba_tp_crear_archivo_inexistente()
{
	TP *tp = tp_crear("archivo_inexistente.txt");
	pa2m_afirmar(tp == NULL,
		     "tp_crear devuelve NULL si el archivo no existe");
}

void prueba_tp_crear_archivo_valido()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "tp_crear crea un TP cuando el archivo es válido");
	pa2m_afirmar(
		tp_cantidad_pokemon(tp) > 0,
		"El TP contiene Pokémon después de cargar un archivo válido");
	tp_destruir(tp);
}

void prueba_tp_cantidad_pokemon()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "tp_crear crea un TP cuando el archivo es válido");
	int cantidad = tp_cantidad_pokemon(tp);
	pa2m_afirmar(cantidad == 25,
		     "La cantidad de Pokémon es la esperada (25)");
	tp_destruir(tp);
}
void prueba_tp_buscar_pokemon()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	pa2m_afirmar(tp_buscar_pokemon(tp, "Pikachu") != NULL,
		     "Se encontró a Pikachu.");
	pa2m_afirmar(tp_buscar_pokemon(tp, "pikachu") != NULL,
		     "Se encontró a pikachu (case-insensitive).");
	pa2m_afirmar(tp_buscar_pokemon(tp, "Charizard") != NULL,
		     "Se encontró a Charizard.");
	pa2m_afirmar(tp_buscar_pokemon(tp, "Mewtwo") == NULL,
		     "No se encontró a Mewtwo.");

	tp_destruir(tp);
}

void prueba_tp_nombres_disponibles()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	char *nombres = tp_nombres_disponibles(tp);
	pa2m_afirmar(nombres != NULL,
		     "Se obtuvieron los nombres de los Pokémon.");
	pa2m_afirmar(
		strcmp(nombres,
		       "Articuno,Blastoise,Bulbasaur,Caterpie,Charizard,Diglett,Dragonair,Dragonite,Dratini,Ekans,Geodude,Grimer,Ivysaur,Meowth,Moltres,Pidgey,Pikachu,Raichu,Rattata,Sandshrew,Squirtle,Venusaur,Vulpix,Wartortle,Zapdos") ==
			0,
		"Los nombres están en orden alfabético y separados por comas.");

	free(nombres);
	tp_destruir(tp);
}

void prueba_tp_seleccionar_pokemon()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu"),
		     "Jugador 1 seleccionó a Pikachu.");
	pa2m_afirmar(
		!tp_seleccionar_pokemon(tp, JUGADOR_2, "Pikachu"),
		"Jugador 2 no pudo seleccionar a Pikachu (ya seleccionado por Jugador 1).");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "Bulbasaur"),
		     "Jugador 2 seleccionó a Bulbasaur.");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Charizard"),
		     "Jugador 1 cambió a Charizard.");

	tp_destruir(tp);
}

void prueba_tp_seleccionar_pokemon2()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "tp_crear crea un TP cuando el archivo es válido");

	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu"),
		     "Jugador 1 selecciona a Pikachu");
	pa2m_afirmar(tp_seleccionar_pokemon(tp, JUGADOR_2, "Charizard"),
		     "Jugador 2 selecciona a Charizard");

	pa2m_afirmar(strcmp(tp_pokemon_seleccionado(tp, JUGADOR_1)->nombre,
			    "Pikachu") == 0,
		     "Jugador 1 tiene a Pikachu");
	pa2m_afirmar(strcmp(tp_pokemon_seleccionado(tp, JUGADOR_2)->nombre,
			    "Charizard") == 0,
		     "Jugador 2 tiene a Charizard");

	tp_destruir(tp);
}

void prueba_tp_agregar_y_quitar_obstaculo()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "tp_crear crea un TP cuando el archivo es válido");

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0) >
			     0,
		     "Se agrega un obstáculo de fuerza para el Jugador 1");
	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, 0) > 0,
		     "Se quita el obstáculo de fuerza para el Jugador 1");

	tp_destruir(tp);
}

void prueba_tp_obstaculos_pista()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "tp_crear crea un TP cuando el archivo es válido");

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 1);

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(obstaculos != NULL,
		     "Se obtienen los obstáculos en la pista del Jugador 1");
	free(obstaculos);

	tp_destruir(tp);
}

void prueba_tp_calcular_tiempo_pista()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "tp_crear crea un TP cuando el archivo es válido");

	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0);

	unsigned tiempo = tp_calcular_tiempo_pista(tp, JUGADOR_1);
	pa2m_afirmar(tiempo > 0,
		     "Se calcula el tiempo de la pista para el Jugador 1");

	tp_destruir(tp);
}

void prueba_tp_tiempo_por_obstaculo()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "tp_crear crea un TP cuando el archivo es válido");

	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0);

	char *tiempos = tp_tiempo_por_obstaculo(tp, JUGADOR_1);
	pa2m_afirmar(tiempos != NULL,
		     "Se obtiene el tiempo por obstáculo para el Jugador 1");
	free(tiempos);

	tp_destruir(tp);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	prueba_simple();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("Pruebas de tp_crear");
	prueba_tp_crear_archivo_inexistente();
	prueba_tp_crear_archivo_valido();

	pa2m_nuevo_grupo("Pruebas de tp_cantidad_pokemon");
	prueba_tp_cantidad_pokemon();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");

	pa2m_nuevo_grupo("Pruebas de tp_buscar_pokemon");
	prueba_tp_buscar_pokemon();

	pa2m_nuevo_grupo("Pruebas de tp_nombres_disponibles");
	prueba_tp_nombres_disponibles();

	pa2m_nuevo_grupo("Pruebas de tp_seleccionar_pokemon");
	prueba_tp_seleccionar_pokemon();

	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");

	pa2m_nuevo_grupo("Pruebas de Selección de Pokémon");
	prueba_tp_seleccionar_pokemon2();

	// pa2m_nuevo_grupo("Pruebas de Obstáculos en la Pista");
	// prueba_tp_agregar_y_quitar_obstaculo();
	// prueba_tp_obstaculos_pista();

	// pa2m_nuevo_grupo("Pruebas de Cálculo de Tiempo en la Pista");
	// prueba_tp_calcular_tiempo_pista();
	// prueba_tp_tiempo_por_obstaculo();

	return pa2m_mostrar_reporte();
}
