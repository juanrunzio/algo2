# TDA ABB

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

El objetivo del presente trabajo práctico es poner en práctica el Tipo de Dato Abstracto ABB (Árbol Binario de Búsqueda) y sus primitivas. Para gestionar las conexiones entre los distintos nodos, la estructura del árbol cuenta con un puntero a la raíz y un contador entero que indica el número de elementos o nodos que contiene. Cada nodo está representado por una estructura que incluye punteros a sus hijos y al elemento que almacena.

El árbol se puede recorrer de tres maneras: INORDEN, PREORDEN y POSTORDEN.

- En el recorrido INORDEN, se visita primero el hijo izquierdo, luego el nodo actual y finalmente el hijo derecho.
- En el recorrido PREORDEN, se visita primero el nodo actual, luego el hijo izquierdo y por último el hijo derecho.
- En cuanto al recorrido POSTORDEN, se visitan primero los hijos izquierdo y derecho, y luego el nodo actual.

En la implementación del ABB, se han considerado ciertos aspectos. Por ejemplo, al eliminar un nodo, se reemplaza con su predecesor inorden. En cuanto a la inserción, si el elemento a insertar es igual al elemento actual, se considera como menor.

Para asegurar la correcta implementación del TDA, se llevaron a cabo pruebas unitarias que cubren una amplia gama de casos, incluidos los casos límite. Cada prueba garantiza que el caso correspondiente esté cubierto y que el sistema no falle en el futuro. Además, se aplicó la metodología TDD, intentando primero escribir las pruebas y luego implementar la solución mínima.

---

## Teoría

### Árbol

Un árbol representa una colección de nodos, donde uno de ellos destaca como el nodo raíz. Este nodo raíz puede o no tener nodos hijos. En caso de tenerlos, cada uno de estos nodos hijos puede considerarse como la raíz de un subárbol independiente. Esta estructura facilita la organización y gestión de grandes conjuntos de datos, ya que el tiempo de búsqueda suele ser de complejidad O(log n).

### Árbol Binario

Los árboles binarios son estructuras en las que cada nodo puede tener 0, 1 o 2 hijos. Estos hijos se denominan comúnmente "izquierdo" y "derecho", lo que proporciona una clara distinción de los subárboles. Sin embargo, este tipo de estructura no ofrece una forma clara de comparar nodos y determinar el camino a seguir durante las operaciones de búsqueda.

### Árbol Binario de Búsqueda

El concepto de árbol binario de búsqueda extiende la idea del árbol binario al introducir la noción de comparación entre los nodos y su padre. En un árbol binario de búsqueda, se establece que el hijo izquierdo es menor que su padre, mientras que el hijo derecho es mayor. Esta relación de ordenamiento permite una búsqueda más eficiente, similar a la búsqueda binaria, lo que resulta en una complejidad de búsqueda logarítmica en el árbol.

---

## Funcionamiento

_Inserción_: Cuando se inserta un nodo en un árbol binario de búsqueda, se inicia comparando el elemento que se desea insertar con el elemento del nodo actual. Comenzando desde el nodo raíz, se pregunta: ¿es menor? En caso afirmativo, se sigue el camino hacia el subárbol izquierdo; ¿es mayor? Entonces se avanza hacia el subárbol derecho. Cuando no hay más nodos disponibles en la dirección seleccionada, se llega al "final" de la rama y es el momento de realizar la inserción. Por ejemplo, al insertar el número 32.

```c
nodo_abb_t *inserto_elemento_y_comparo(abb_t *arbol, nodo_abb_t *nodo_actual, void *elemento)
{
	if (nodo_actual == 0) {
		nodo_abb_t *nuevo_nodo = malloc(sizeof(nodo_abb_t));
		if (nuevo_nodo == 0)
			return NULL;
		nuevo_nodo->elemento = elemento;
		nuevo_nodo->izquierda = NULL;
		nuevo_nodo->derecha = NULL;
		arbol->tamanio++;
		return nuevo_nodo;
	}

	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	if (comparacion > 0)
		nodo_actual->derecha = inserto_elemento_y_comparo(arbol, nodo_actual->derecha, elemento);

	if (comparacion <=0)
		nodo_actual->izquierda = inserto_elemento_y_comparo(arbol, nodo_actual->izquierda, elemento);

	return nodo_actual;
}
```

La función `abb_insertar` se encarga de añadir nuevos elementos al árbol binario de búsqueda. Utiliza una función auxiliar recursiva llamada `inserto_elemento_y_comparo`. En cada llamada recursiva, se verifica si el nodo actual es nulo. En caso afirmativo, se reserva memoria para el nuevo nodo, se establecen los punteros de los hijos como nulos y se asigna el puntero al nuevo elemento. Si el nodo actual no es nulo, se compara el elemento a insertar con el elemento del nodo actual para determinar hacia qué subárbol continuar. Luego, se llama recursivamente a la misma función, modificando el nodo actual por el nodo izquierdo o derecho, según corresponda. Es importante destacar que el valor devuelto por esta función debe asignarse al nodo que se pasa como parámetro. Por ejemplo: `hijo_izquierdo = función(hijo_izquierdo...)`, para así guardar los cambios realizados en los hijos y continuar conectando los nodos.

<div align="center">
<img width="70%" src="img/insertar.jpg">
</div>

### Por ejemplo:

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```

<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---
