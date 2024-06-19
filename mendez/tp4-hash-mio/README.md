<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de (Juan Bautista Oviedo Runzio) - (110164) - (jbauti9@gmail.com/joviedo@fi.uba.ar)

- Para correr todo:

```bash
make
```

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_alumno.c -o pruebas_alumno
```

- Para ejecutar:

```bash
./pruebas_alumno
```

- Para ejecutar con valgrind:

```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./pruebas_alumno
```

---

## Introducción

El objetivo del trabajo práctico es implementar un diccionario utilizando el TDA HASH y sus primitivas. Existen dos tipos de HASH: abierto y cerrado. El HASH abierto almacena los elementos fuera de la tabla, es decir, guarda los elementos o los punteros a los elementos en una estructura separada, y la tabla contiene el puntero a dicha estructura. Esta estructura puede tener a su vez un puntero a otra estructura que contiene otro elemento. Esto implica que la posición generada por la función HASH es definitiva para encontrar el elemento; si no se encuentra en la primera estructura, se busca en la siguiente. Esto es conocido como direccionamiento cerrado (la dirección es la que proporciona la función).

En contraste, el HASH cerrado almacena el elemento o el puntero al elemento dentro de la tabla. Dado que solo puede haber un elemento por posición, cuando se generan colisiones se busca la siguiente posición libre más cercana, haciendo que la posición dada por la función hash no sea definitiva. A esto se le conoce como direccionamiento abierto.

Para la implementación se utilizó un hash cerrado con direccionamiento abierto, donde la tabla es un vector de punteros a claves y valores. Cada posición de la tabla puede contener una cadena de caracteres como clave y un puntero al valor asociado. La estructura que contiene el vector, llamada hash, incluye además dos variables enteras: una para la cantidad de elementos almacenados y otra para la capacidad del hash.

Para confirmar la correcta implementación del TDA, se realizaron pruebas unitarias que simulan la mayor cantidad de casos posibles. Para la realización de las pruebas, se siguió un enfoque de desarrollo basado en pruebas (TDD), donde primero se escriben las pruebas y luego se implementa la mínima solución que las satisface.

---

## Funcionamiento

Para la implementación se definieron dos estructuras de datos: una para la clave y el valor, y otra para el hash que contiene dos enteros para almacenar la cantidad de pares y la capacidad, además de dos vectores de punteros, uno para las claves y otro para los valores.

El recorrido de las posiciones del vector del hash se hizo de forma iterativa, ya que era simplemente recorrer un vector común. En el caso del `rehash`, se recorrieron las posiciones del vector antiguo de manera iterativa con un bucle `for` para simplificar, utilizando `hash_insertar` con el nuevo vector en cada iteración.

#### Insertar:

Para la inserción, se utiliza la función `hash_insertar`:

```c
{
	size_t capacidad_maxima =
		(size_t)((double)hash->capacidad * FACTOR_CARGA_MAXIMA);
	if ((hash->cantidad + 1) > capacidad_maxima) {
		if (!rehash(hash)) {
			return NULL;
		}
	}

	size_t pos = funcion_de_hash(clave, hash->capacidad);
	size_t original_pos = pos;
	bool encontrado = false;

	while (hash->claves[pos] != NULL &&
	       strcmp(hash->claves[pos], clave) != 0) {
		pos = (pos + 1) % hash->capacidad;
		if (pos == original_pos) {
			return NULL;
		}
	}

	if (hash->claves[pos] != NULL &&
	    strcmp(hash->claves[pos], clave) == 0) {
		encontrado = true;
	}

	if (encontrado) {
		if (anterior) {
			*anterior = hash->valores[pos];
		}
		hash->valores[pos] = elemento;
	} else {
		hash->claves[pos] = funcion_para_duplicar_una_cadena(clave);
		hash->valores[pos] = elemento;
		hash->cantidad++;
		if (anterior) {
			*anterior = NULL;
		}
	}

	return hash;
}
```

Lo primero que realiza, es verificar si la carga del hash requiere un rehashing. Si el número de elementos más uno excede la capacidad máxima, se llama a la función `rehash`. Luego, se calcula la posición utilizando la función hash y se resuelve cualquier colisión utilizando direccionamiento abierto (cuadrático). Si se encuentra una clave existente, se actualiza su valor; de lo contrario, se inserta un nuevo par clave-valor.

Para el `rehash`, se crea un nuevo vector con capacidad ajustada y se redistribuyen los elementos del vector antiguo. Se recorre cada posición del vector antiguo y se inserta cada elemento en la nueva tabla utilizando la función `hash_insertar`. Luego, se libera la memoria del vector antiguo y se asigna el nuevo vector al hash.

#### Eliminar:

Para eliminar un elemento, se utiliza la función `hash_quitar`,:

```c
{
    size_t pos = funcion_de_hash(clave, hash->capacidad);
	size_t original_pos = pos;

	while (hash->claves[pos] != NULL) {
		if (strcmp(hash->claves[pos], clave) == 0) {
			void *valor = hash->valores[pos];
			free(hash->claves[pos]);
			hash->claves[pos] = NULL;
			hash->valores[pos] = NULL;
			hash->cantidad--;

			size_t next_pos = (pos + 1) % hash->capacidad;
			while (hash->claves[next_pos] != NULL) {
				char *temp_clave = hash->claves[next_pos];
				void *temp_valor = hash->valores[next_pos];
				hash->claves[next_pos] = NULL;
				hash->valores[next_pos] = NULL;
				hash->cantidad--;
				hash_insertar(hash, temp_clave, temp_valor,
					      NULL);
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
```

La cual localiza la posición con la clave especificada, libera la memoria asociada y ajusta el vector para mantener la integridad del hash. Si encuentra la clave, elimina la entrada y reubica los elementos colisionados. La función sigue buscando hasta que se encuentre un `NULL`, indicando que la clave no existe.

#### Destruir y Destruir Todo:

La función `hash_destruir_todo` recorre el vector de forma iterativa. Si el destructor no es `NULL`, aplica el destructor al elemento. Luego, libera la memoria reservada para la clave y el elemento. Finalmente, libera la memoria reservada para los vectores de claves y valores, y luego para el hash. La función hash_destruir utiliza la función `hash_destruir_todo` con un destructor `NULL`.

---

## Respuestas a las preguntas teóricas

#### Primitivas de un HASH abierto

- Insertar: Para insertar un par clave-valor, se genera una posición usando la función hash, pasándole como parámetro la clave. La función hash devuelve la posición, y con esta buscamos en el vector, donde pueden ocurrir las siguientes situaciones: si la posición está vacía, se inserta el par clave-valor; si ya hay un par clave-valor, se verifica si la clave es la misma que la del par que queremos insertar. Si la clave es la misma, se reemplaza el valor existente con el nuevo. Si no es la misma clave, se avanza al siguiente nodo (o a la estructura correspondiente) y se repite el proceso hasta lograr insertar o actualizar.

Insertar implica los siguientes pasos: se reserva memoria para la nueva estructura que contendrá el par clave-valor. Si la reserva de memoria es exitosa, se reserva memoria para la clave. Si esta operación también es exitosa, se copia la clave y el valor o su puntero en la nueva estructura creada. En caso de fallo al reservar memoria, se libera la memoria previamente reservada (si falla la reserva de memoria para la clave, se libera la memoria del nodo) y se retorna null (o el valor que indique la convención utilizada). Finalmente, se incrementa en 1 la cantidad de elementos almacenados.

<div align="center">
<img width="90%" src="img/imInsertarHash.jpg">
</div>

- Eliminar: Se obtiene la posición utilizando la clave y la función hash, y se busca en el vector la posición correspondiente. Al igual que en la inserción, pueden ocurrir las siguientes situaciones: si la posición está vacía, no hay nada que eliminar, por lo que se devuelve el valor establecido por convención (en este caso, null); si hay un par clave-valor, se compara la clave buscada con la existente. Si son iguales, se elimina el nodo; si no son iguales, se avanza al siguiente nodo y se repiten los pasos.

Eliminar implica los siguientes pasos: se guarda en un auxiliar el puntero al siguiente nodo, y en otro auxiliar se guarda el elemento o su puntero. Luego, se elimina el nodo (liberando la memoria ocupada por la estructura que contiene la clave y valor buscados) y se retorna el auxiliar que apunta al siguiente nodo para poder conectarlo con el nodo predecesor del eliminado. Finalmente, se disminuye en 1 la cantidad de elementos almacenados.

<div align="center">
<img width="90%" src="img/imEliminarHash.jpg">
</div>

- Buscar: Se obtiene la posición utilizando la clave y la función hash, y se busca en el vector la posición correspondiente. Al igual que en la inserción y eliminación, pueden ocurrir las siguientes situaciones: si la posición está vacía, el valor buscado no existe, por lo que se devuelve el valor establecido por convención (en este caso, null); si hay un par clave-valor, se compara la clave buscada con la existente. Si son iguales, se retorna el puntero al elemento; si no son iguales, se avanza al siguiente nodo y se repiten los pasos hasta encontrar el elemento o llegar al final.

#### Primitivas de un HASH cerrado

- Insertar: Se obtiene la posición utilizando la función hash y se busca la posición en el vector. Pueden ocurrir las mismas tres situaciones, pero se procede de manera diferente debido al direccionamiento abierto: si la posición está vacía, se inserta el par clave-valor; si existe un par clave-valor, se comparan las claves. Si son iguales, se reemplaza el elemento existente con el nuevo; si son distintas, se pasa a la siguiente posición del vector y se verifica nuevamente. Este proceso se repite las veces necesarias hasta poder insertar el par clave-valor.

Insertar implica los siguientes pasos: reservar memoria para la clave, asignar la copia de la clave y el elemento a la estructura del vector. Finalmente, se incrementa en 1 la cantidad de elementos almacenados.

<div align="center">
<img width="90%" src="img/insertarHashCerrado.jpg">
</div>

- Eliminar: Se obtiene la posición utilizando la función hash y se busca en el vector. Se encuentran las mismas tres situaciones, pero es importante mencionar que al eliminar se deja una bandera indicando que algo fue eliminado. Al encontrar la posición, se verifica si es la clave buscada; en caso afirmativo, se elimina y se deja la bandera en true. Si no es la misma clave, se pasa a la siguiente posición, ya que pudo haber una colisión al insertarla. Este proceso se repite hasta encontrar la clave buscada o hasta encontrar una posición vacía en el vector sin la bandera de eliminado. Si se encuentra una posición vacía sin la bandera, significa que el par clave-valor estuvo en el primer lugar con la bandera encontrada o nunca se insertó, ya que en caso de colisión se hubiese buscado la siguiente posición libre. Por lo tanto, no hay posibilidad de que la clave buscada exista si se encuentra un espacio vacío.

 <div align="center">
<img width="90%" src="img/eliminarHashCerrado.jpg">
</div>

- Buscar: El proceso de búsqueda es similar al de eliminación, pero sin "eliminar". Si se encuentra la clave buscada, se retorna el valor; si no, se continúa buscando en las siguientes posiciones hasta encontrarla o encontrar un espacio vacío sin la bandera de eliminado.

Para ambos casos, HASH abierto o cerrado, se debe realizar el rehash, que implica agrandar la tabla o vector. Para esto, se establece un porcentaje de ocupación de la tabla que determina cuándo realizarlo. Antes de insertar un elemento (preferiblemente), se verifica si sumando 1 a la cantidad de pares guardados se sobrepasa el porcentaje establecido. De ser así, se realiza el rehash y luego se inserta; de lo contrario, solo se inserta. El rehash puede hacerse de varias maneras: se puede agrandar solo la tabla o crear un hash nuevo. De cualquier forma, se debe recorrer la tabla anterior y almacenar los pares en la nueva tabla, utilizando la función hash y la capacidad de la nueva tabla. Esto es necesario porque al cambiar la capacidad, la posición generada por la función hash también puede cambiar.

#### Función de hash:

Una función de hash es un algoritmo que toma una entrada (o "clave") y devuelve un valor numérico de longitud fija, llamado "hash". Este valor numérico se utiliza como un índice para almacenar elementos en una estructura de datos llamada "tabla hash". La función de hash tiene como objetivo distribuir las claves de manera uniforme a través de la tabla para minimizar las colisiones.

Características que debe tener una función de hash:

- Para una misma entrada, la función debe siempre producir el mismo hash.
- Debe ser eficiente, la función debe ser capaz de calcular el hash rápidamente, incluso para entradas de gran tamaño.
- Debe distribuir las claves de manera uniforme a lo largo del espacio de hash, evitando agrupamientos para minimizar colisiones.
- Poca sensibilidad a entradas similares, dos entradas similares deben producir valores de hash significativamente diferentes para reducir colisiones.
- Bien distribuida ,cada posición en la tabla debe ser igualmente probable de ser seleccionada por la función de hash.

#### Tabla de Hash:

Una tabla de hash es una estructura de datos que permite la asociación rápida de claves con valores. Utiliza una función de hash para mapear las claves a posiciones (índices) en una tabla, donde se almacenan los pares clave-valor. La principal ventaja de una tabla de hash es que puede proporcionar un acceso muy rápido a los datos, típicamente O(1) en promedio.

#### Métodos de resolución de colisiones:

Las colisiones ocurren cuando la función de hash asigna dos o más claves a la misma posición en la tabla. Para manejar esto, se utilizan varios métodos de resolución de colisiones:

- Encadenamiento (Chaining):
  Cada posición en la tabla contiene un puntero a una lista enlazada (o cualquier otra estructura de datos) que almacena todos los pares clave-valor que comparten la misma posición de hash.
  La ventaja es que es fácil de implementar y manejar.
  La desventaja, puede degradar el rendimiento si muchas claves colisionan, convirtiendo las operaciones en O(n).

- Probing Lineal (Linear Probing):
  En caso de colisión, se busca secuencialmente la siguiente posición libre en la tabla.
  La ventaja, simple de implementar y no requiere estructuras adicionales.
  La desventaja puede causar "clustering", donde grupos de claves colisionan y llenan secuencias contiguas de la tabla.

- Probing Cuadrático (Quadratic Probing):
  Similar al probing lineal, pero en lugar de buscar secuencialmente, se usa una función cuadrática para determinar la siguiente posición.
  La ventaja es que reduce el problema de clustering primario comparado con el probing lineal.
  La desventaja es que puede aún provocar clustering secundario y puede ser complicado encontrar una posición libre si la tabla está bastante llena.

- Double Hashing:
  Usa dos funciones de hash diferentes. Si una clave colisiona, la segunda función de hash se utiliza para encontrar la siguiente posición libre.
  La ventaja es que minimiza el clustering y distribuye las colisiones más uniformemente.
  La desventaja, es más compleja de implementar y requiere que ambas funciones de hash sean eficientes y bien distribuidas.

Estos métodos aseguran que incluso si dos claves producen el mismo hash, aún se puede almacenar y acceder a cada clave-valor de manera eficiente.
