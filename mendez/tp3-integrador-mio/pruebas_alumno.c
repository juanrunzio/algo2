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
	TP *tp = tp_crear(
		"ejemplo/pokemones.txt"); // Asegúrate de tener un archivo "pokemones.txt" con datos correctos

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
	TP *tp = tp_crear(
		"ejemplo/pokemones.txt"); // Asegúrate de tener un archivo "pokemones.txt" con datos correctos

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
	TP *tp = tp_crear(
		"ejemplo/pokemones.txt"); // Asegúrate de tener un archivo "pokemones.txt" con datos correctos

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

	return pa2m_mostrar_reporte();
}
