#include "pa2m.h"
#include "./src/hash.h"
#include <string.h>

void creacion_de_hash()
{
	struct hash *hash_1 = hash_crear(1);
	struct hash *hash_2 = hash_crear(5);
	pa2m_afirmar(hash_1 != NULL, "Creo hash con parametro 1");
	pa2m_afirmar(hash_2 != NULL, "Creo hash con parametro 5");
	pa2m_afirmar(
		hash_cantidad(hash_1) == 0,
		"La cantidad de elementos se inicializo correctamente en 0, con el parametro 1");
	pa2m_afirmar(
		hash_cantidad(hash_2) == 0,
		"La cantidad de elementos se inicializo correctamente en 0, con el parametro 5");
	hash_destruir_todo(hash_1, NULL);
	hash_destruir_todo(hash_2, NULL);
}

void insercion_en_hash()
{
	void *anterior = NULL;
	struct hash *hash_1 = hash_crear(1);
	int numero_7 = 7;
	int numero_9 = 9;
	hash_1 = hash_insertar(hash_1, "Juan", &numero_7, &anterior);
	pa2m_afirmar(hash_cantidad(hash_1) == 1,
		     "Se pudo agregar un elemento correctamente");
	pa2m_afirmar(
		anterior == NULL,
		"Anterior es NULL ya que no existia anteriormente la clave");
	hash_1 = hash_insertar(hash_1, "Carlos", &numero_9, &anterior);
	pa2m_afirmar(hash_cantidad(hash_1) == 2,
		     "Se pudo agregar un segundo elemento correctamente");
	pa2m_afirmar(
		anterior == NULL,
		"Anterior es NULL ya que no existia anteriormente la clave");
	hash_destruir_todo(hash_1, NULL);
}
void reemplazo_en_hash()
{
	void *anterior = NULL;
	struct hash *hash_1 = hash_crear(1);
	int numero_7 = 7;
	int numero_9 = 9;
	hash_1 = hash_insertar(hash_1, "Juan", &numero_7, &anterior);
	pa2m_afirmar(hash_cantidad(hash_1) == 1,
		     "Se pudo agregar un elemento correctamente");
	hash_1 = hash_insertar(hash_1, "Juan", &numero_9, &anterior);
	pa2m_afirmar(hash_cantidad(hash_1) == 1,
		     "Se pudo agregar un elemento con la clave ya existente");
	pa2m_afirmar(
		anterior == &numero_7,
		"Anterior almacena el puntero al elemento que estaba anteriormente");
	hash_1 = hash_insertar(hash_1, "Juan", &numero_9, &anterior);
	pa2m_afirmar(hash_cantidad(hash_1) == 1,
		     "Se pudo agregar de nuevo un elemento con la misma clave");
	pa2m_afirmar(
		anterior == &numero_9,
		"Anterior almacena el puntero al elemento que estaba anteriormente");
	hash_destruir_todo(hash_1, NULL);
}

void insercion_con_clave_anterior_o_hash_null()
{
	struct hash *hash_1 = hash_crear(1);
	void *anterior = NULL;
	int numero_7 = 7;
	pa2m_afirmar(hash_insertar(hash_1, NULL, &numero_7, &anterior) == NULL,
		     "No se puede insertar con una clave NULL");
	pa2m_afirmar(hash_insertar(NULL, "Juan", &numero_7, &anterior) == NULL,
		     "No se puede insertar con un hash NULL");
	pa2m_afirmar(hash_insertar(hash_1, "Juan", &numero_7, NULL) != NULL,
		     "Puedo insertar con anterior NULL");
	hash_destruir_todo(hash_1, NULL);
}

void inserto_10_elementos_10_veces()
{
	struct hash *nuevo_hash = hash_crear(1);
	char claves[10][10];
	strcpy(claves[0], "a");
	strcpy(claves[1], "b");
	strcpy(claves[2], "c");
	strcpy(claves[3], "d");
	strcpy(claves[4], "e");
	strcpy(claves[5], "f");
	strcpy(claves[6], "g");
	strcpy(claves[7], "h");
	strcpy(claves[8], "i");
	strcpy(claves[9], "j");
	char *valor_par = "par";
	char *valor_impar = "impar";
	void *anterior = NULL;
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			if ((i % 2) == 0)
				nuevo_hash = hash_insertar(
					nuevo_hash, claves[i], valor_par, NULL);
			else
				nuevo_hash = hash_insertar(nuevo_hash,
							   claves[i],
							   valor_impar, NULL);
		}
	}

	nuevo_hash = hash_insertar(nuevo_hash, "c", "otro_valor", &anterior);
	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 10,
		"Inserto 10 elementos con claves distintas, 10 veces y se reemplazan correctamente");
	pa2m_afirmar(strcmp(anterior, valor_par) == 0,
		     "Anterior guarda correctamente el valor");
	nuevo_hash = hash_insertar(nuevo_hash, "c", "otro_valor_diferente",
				   &anterior);
	pa2m_afirmar(strcmp(anterior, "otro_valor") == 0,
		     "Anterior guarda correctamente el valor");
	hash_destruir_todo(nuevo_hash, NULL);
}

void elimino_elementos()
{
	struct hash *nuevo_hash = hash_crear(1);
	char claves[10][10];
	strcpy(claves[0], "a");
	strcpy(claves[1], "b");
	strcpy(claves[2], "c");
	strcpy(claves[3], "d");
	strcpy(claves[4], "e");
	strcpy(claves[5], "f");
	strcpy(claves[6], "g");
	strcpy(claves[7], "h");
	strcpy(claves[8], "i");
	strcpy(claves[9], "j");
	char *valor = "valorX";

	for (int i = 0; i < 10; i++)
		nuevo_hash = hash_insertar(nuevo_hash, claves[i], valor, NULL);

	char *resultado = hash_quitar(nuevo_hash, "a");
	pa2m_afirmar(strcmp(resultado, "valorX") == 0,
		     "Devuelve el elemento eliminado");
	pa2m_afirmar(hash_cantidad(nuevo_hash) == 9,
		     "La cantidad de elementos disminuye en 1");
	resultado = hash_quitar(nuevo_hash, "w");
	pa2m_afirmar(resultado == NULL,
		     "No encuentra el elemento, devuelve NULL");
	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 9,
		"La cantidad de elementos no fue modificada, por lo tanto sigue siendo la misma");

	for (int i = 1; i < 10; i++)
		hash_quitar(nuevo_hash, claves[i]);
	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0,
		     "Elimino todos los elementos");
	hash_destruir_todo(nuevo_hash, NULL);
}

void eliminacion_con_hash_vacio_clave_null()
{
	struct hash *nuevo_hash = hash_crear(1);
	pa2m_afirmar(hash_quitar(nuevo_hash, "r") == NULL,
		     "Si el hash esta vacio retorno NULL");
	nuevo_hash = hash_insertar(nuevo_hash, "r", "valor", NULL);
	pa2m_afirmar(hash_quitar(NULL, "r") == NULL,
		     "Si no hay hash retorno NULL");
	pa2m_afirmar(hash_quitar(nuevo_hash, NULL) == NULL,
		     "Si no hay clave retorno NULL");
	hash_destruir_todo(nuevo_hash, NULL);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("1_Pruebas de la creacion y inicializacion de hash");
	creacion_de_hash();
	pa2m_nuevo_grupo(
		"2_Pruebas de insercion de claves que no son repetidas en el hash");
	insercion_con_clave_anterior_o_hash_null();
	pa2m_nuevo_grupo(
		"3_Pruebas de insercion de claves no repetidas en el hash");
	insercion_en_hash();
	pa2m_nuevo_grupo(
		"4_Pruebas de insercion de claves repetidas en el hash");
	reemplazo_en_hash();
	pa2m_nuevo_grupo("5_Pruebas de insercion de varios elementos(100)");
	inserto_10_elementos_10_veces();
	pa2m_nuevo_grupo("6_Pruebas de eliminacion de elementos en el hash");
	elimino_elementos();
	eliminacion_con_hash_vacio_clave_null();

	return pa2m_mostrar_reporte();
}
