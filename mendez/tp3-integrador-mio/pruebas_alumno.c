#include "pa2m.h"
#include "src/tp.h"
#include <stdio.h>

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

	return pa2m_mostrar_reporte();
}
