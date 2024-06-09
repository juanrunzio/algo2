#include <stdlib.h>
#include <string.h>

#include "hash.h"

#define FACTOR_CARGA_MAXIMA 0.7

struct hash {
  char **claves;
  void **valores;
  size_t capacidad;
  size_t cantidad;
};

size_t funcion_de_hash(char *clave, size_t capacidad) {
  size_t hash = 0;
  while (*clave) {
    hash = (hash * 31 + *clave) % capacidad;
    clave++;
  }
  return hash;
}

hash_t *hash_crear(size_t capacidad) {
  if (capacidad < 3)
    capacidad = 3;

  hash_t *hash = malloc(sizeof(hash_t));
  if (!hash)
    return NULL;

  hash->claves = calloc(capacidad, sizeof(char *));
  hash->valores = calloc(capacidad, sizeof(void *));
  if (!hash->claves || !hash->valores) {
    free(hash->claves);
    free(hash->valores);
    free(hash);
    return NULL;
  }

  hash->capacidad = capacidad;
  hash->cantidad = 0;
  return hash;
}

static bool rehash(hash_t *hash) {
  size_t nueva_capacidad = hash->capacidad * 2;
  char **nuevas_claves = calloc(nueva_capacidad, sizeof(char *));
  void **nuevos_valores = calloc(nueva_capacidad, sizeof(void *));
  if (!nuevas_claves || !nuevos_valores) {
    free(nuevas_claves);
    free(nuevos_valores);
    return false;
  }

  for (size_t i = 0; i < hash->capacidad; i++) {
    if (hash->claves[i]) {
      size_t nueva_pos = funcion_hash(hash->claves[i], nueva_capacidad);
      while (nuevas_claves[nueva_pos] != NULL) {
        nueva_pos = (nueva_pos + 1) % nueva_capacidad;
      }
      nuevas_claves[nueva_pos] = hash->claves[i];
      nuevos_valores[nueva_pos] = hash->valores[i];
    }
  }

  free(hash->claves);
  free(hash->valores);
  hash->claves = nuevas_claves;
  hash->valores = nuevos_valores;
  hash->capacidad = nueva_capacidad;
  return true;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
                      void **anterior) {
  if (!hash || !clave)
    return NULL;
  if ((hash->cantidad + 1) > (hash->capacidad * FACTOR_CARGA_MAXIMA)) {
    if (!rehash(hash))
      return NULL;
  }

  size_t pos = funcion_hash(clave, hash->capacidad);
  size_t original_pos = pos;
  bool encontrado = false;

  while (hash->claves[pos] != NULL) {
    if (strcmp(hash->claves[pos], clave) == 0) {
      encontrado = true;
      break;
    }
    pos = (pos + 1) % hash->capacidad;
    if (pos == original_pos)
      return NULL;
  }

  if (encontrado) {
    if (anterior)
      *anterior = hash->valores[pos];
    hash->valores[pos] = elemento;
  } else {
    hash->claves[pos] = strdup(clave);
    hash->valores[pos] = elemento;
    hash->cantidad++;
    if (anterior)
      *anterior = NULL;
  }

  return hash;
}

void *hash_quitar(hash_t *hash, const char *clave) {
  if (!hash || !clave)
    return NULL;

  size_t pos = funcion_hash(clave, hash->capacidad);
  size_t original_pos = pos;

  while (hash->claves[pos] != NULL) {
    if (strcmp(hash->claves[pos], clave) == 0) {
      void *valor = hash->valores[pos];
      free(hash->claves[pos]);
      hash->claves[pos] = NULL;
      hash->valores[pos] = NULL;
      hash->cantidad--;

      // Reorganizar la tabla
      size_t next_pos = (pos + 1) % hash->capacidad;
      while (hash->claves[next_pos] != NULL) {
        char *temp_clave = hash->claves[next_pos];
        void *temp_valor = hash->valores[next_pos];
        hash->claves[next_pos] = NULL;
        hash->valores[next_pos] = NULL;
        hash->cantidad--;
        hash_insertar(hash, temp_clave, temp_valor, NULL);
        free(temp_clave);
        next_pos = (next_pos + 1) % hash->capacidad;
      }

      return valor;
    }
    pos = (pos + 1) % hash->capacidad;
    if (pos == original_pos)
      return NULL;
  }

  return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave) {
  if (!hash || !clave)
    return NULL;
  size_t pos = funcion_hash(clave, hash->capacidad);
  size_t original_pos = pos;
  while (hash->claves[pos] != NULL) {
    if (strcmp(hash->claves[pos], clave) == 0)
      return hash->valores[pos];
    pos = (pos + 1) % hash->capacidad;
    if (pos == original_pos)
      return NULL;
  }
  return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave) {
  return hash_obtener(hash, clave) != NULL;
}

size_t hash_cantidad(hash_t *hash) {
  if (!hash)
    return 0;
  return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
  if (!hash)
    return;
  for (size_t i = 0; i < hash->capacidad; i++) {
    if (hash->claves[i])
      free(hash->claves[i]);
  }
  free(hash->claves);
  free(hash->valores);
  free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *)) {
  if (!hash)
    return;
  for (size_t i = 0; i < hash->capacidad; i++) {
    if (hash->claves[i]) {
      if (destructor)
        destructor(hash->valores[i]);
      free(hash->claves[i]);
    }
  }
  free(hash->claves);
  free(hash->valores);
  free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
                           bool (*f)(const char *clave, void *valor, void *aux),
                           void *aux) {
  if (!hash || !f)
    return 0;
  size_t cantidad = 0;
  for (size_t i = 0; i < hash->capacidad; i++) {
    if (hash->claves[i]) {
      if (!f(hash->claves[i], hash->valores[i], aux))
        break;
      cantidad++;
    }
  }
  return cantidad;
}
